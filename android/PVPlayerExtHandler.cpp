//#define LOG_NDEBUG 0
#define LOG_TAG "ExtensionHandler"
#include <utils/Log.h>

#include <sys/prctl.h>
#include <sys/resource.h>
#include "PVPlayerExtHandler.h"
#include "dispatch.h"

//For loading Extension Interfaces
#include "oscl_shared_library.h"
#include "oscl_library_list.h"
#include "oscl_configfile_list.h"
#include "osclconfig_lib.h"

using namespace android;

PVPlayerExtensionHandler::PVPlayerExtensionHandler(const PlayerDriver& pd)
                        :mPlayerDriver(pd)
{
    LOGV("PVPlayerExtensionHandler::PVPlayerExtensionHandler");
    // Parse the configuration files for the Extension Interface and populate the registry
    PVPlayerExtnPopulator::populate(mPVPlayerExtnIfaceRegistry);
}

PVPlayerExtensionHandler::~PVPlayerExtensionHandler()
{
    LOGV("PVPlayerExtensionHandler::~PVPlayerExtensionHandler");
    PVPlayerExtnPopulator::depopulate(mPVPlayerExtnIfaceRegistry);
}

status_t PVPlayerExtensionHandler::queryExtnIface(const Parcel& data, Parcel& reply)
{
    String16 iface= data.readString16();
    IDispatch* extPtr = NULL;
    extPtr = mPVPlayerExtnIfaceRegistry.createExtension(iface,*this);
    if(extPtr){
        LOGV("PVPlayerExtensionHandler::queryExtnIface extIface=%d",(int32_t)extPtr);
        status_t status = reply.writeInt32(NO_ERROR);
        if(NO_ERROR != status){
            return INVALID_OPERATION;
        }
        return reply.writeInt32((int32_t)extPtr);
    } else {
        return reply.writeInt32(NAME_NOT_FOUND);
    }
}

status_t PVPlayerExtensionHandler::callPlayerExtension(PlayerExtensionCommand* cmd, const Parcel& request, Parcel& reply)
{
    status_t status;
    int32_t opcode = -1;
    status = request.readInt32(&opcode);
    switch(opcode) {
        case EXTN_HANDLER_CMD_QUERY_EXTN_IFACE: {
            LOGV("callPlayerExtension EXTN_HANDLER_CMD_QUERY_EXTN_IFACE ");
            status = queryExtnIface(request , reply);
            if(NO_ERROR != status) {
                getPlayerDriver().commandFailed((PlayerCommand*)cmd);
            } else {
                FinishSyncCommand((PlayerCommand*)cmd);
            }
            return status;
        }
        case EXTN_HANDLER_CMD_EXTN_API_CALL: {  
            LOGV("callPlayerExtension EXTN_HANDLER_CMD_EXTN_API_CALL");
            //Extract the handle
            IDispatch* extIface = (IDispatch*)request.readInt32();
            if(extIface){
                LOGV("callPlayerExtension extIface=%d",(int)extIface);
                //invoke the requested API
                return extIface->invoke(request,reply,cmd);
            }else{
                status = reply.writeInt32(INVALID_OPERATION);
                getPlayerDriver().commandFailed((PlayerCommand*)cmd);
                return status;
            }
        }
        case EXTN_HANDLER_CMD_RELEASE_EXTN_IFACE: {  
            LOGV("callPlayerExtension EXTN_HANDLER_CMD_RELEASE_EXTN_IFACE");
            //Extract the handle
            IDispatch* extIface = (IDispatch*)request.readInt32();
            if(extIface) {
                LOGV("callPlayerExtension extIface=%d",(int)extIface);
                //Release Extension
                delete extIface; 
                status = reply.writeInt32(NO_ERROR);
                FinishSyncCommand((PlayerCommand*)cmd);
                return status;
            } else {
                status = reply.writeInt32(INVALID_OPERATION);
                getPlayerDriver().commandFailed((PlayerCommand*)cmd);
                return status;
            }
        }
        default:
            LOGE("Unknown opcode %d", opcode);
            status = reply.writeInt32(INVALID_OPERATION);
            getPlayerDriver().commandFailed((PlayerCommand*)cmd);
            return status;
    }

}

// return true if extension handled this notification or false for default processing inside
// playerdriver
bool PVPlayerExtensionHandler::commandCompleted( PlayerExtensionCommand* cmd, const PVCmdResponse &resp )
{
    IDispatch* extIface = (IDispatch*)cmd->getCompletionHandle();
    LOGD("PVPlayerExtensionHandler::commandCompleted- extIface=%d",(int) extIface);
    if (NULL == extIface) {
        // unusual, but possible- let's warn users about it
        LOGD("PVPlayerExtensionHandler::commandCompleted- no valid extension specified for command completion");
        return false;
    }
    return (extIface->commandCompleted(cmd, resp));
}



