#ifndef PVPLAYER_EXT_HANDLER_H_INCLUDED
#define PVPLAYER_EXT_HANDLER_H_INCLUDED

#include "playerdriver.h"

#include "binder/Parcel.h"
#include "extension_handler_registry.h"
using namespace android;


class PVPlayerExtensionHandler
{
public:
    PVPlayerExtensionHandler(const PlayerDriver& pd);
    virtual ~PVPlayerExtensionHandler();

    /**
     * Extension UUID String is fetched from the data parcel. If the requested Extension is found in the registry,
     * then its instance is created and handle is returned in the reply parcel.
     *
     * @param data
     *        It is a parcel which contains the String UUID of the requested Extension
     * @param reply
     *        It is a parcel which contains the handle to requested Extension
     * @return
     *        Completion status
     */
    virtual status_t queryExtnIface(const Parcel& data, Parcel& reply);
    /**
     * The extension commands are invoked through this function
     *
     * @param cmd
     *        The extension command meant to be executed
     * @param data
     *        It is a parcel which contains Extension handle and data related to Extension Command
     * @param reply
     *        It is a parcel which contains data returned by the Extension API
     * @return
     *        Completion status
    */
    virtual status_t callPlayerExtension(PlayerExtensionCommand* cmd, const Parcel& data, Parcel& reply);

    // access to playerdriver and its fields
    PlayerDriver& getPlayerDriver() { return const_cast<PlayerDriver &>(mPlayerDriver); }
    PVPlayerInterface* getPlayer() { return mPlayerDriver.mPlayer; }
    void FinishSyncCommand(PlayerCommand* cmd){(const_cast<PlayerDriver &> (mPlayerDriver)).FinishSyncCommand(cmd);}
    // returns true if aCmd was handled by an extension or false to request default completion
    virtual bool commandCompleted( PlayerExtensionCommand* cmd, const PVCmdResponse &resp );
    // for sending Info and Error events to the Java App
    void sendEvent(int msg, int ext1=0, int ext2=0) { (mPlayerDriver.mPvPlayer)->sendEvent(msg, ext1, ext2); }
    // We need this for getting Filename from mDataSource
    PVPlayerDataSourceURL* getDataSource() { return mPlayerDriver.mDataSource; }
protected:
    const PlayerDriver& mPlayerDriver;
    PVPlayerExtensionRegistry mPVPlayerExtnIfaceRegistry;
private:
    enum{
        EXTN_HANDLER_CMD_FIRST = 0,
        EXTN_HANDLER_CMD_QUERY_EXTN_IFACE = EXTN_HANDLER_CMD_FIRST,
        EXTN_HANDLER_CMD_EXTN_API_CALL = 1,
        EXTN_HANDLER_CMD_RELEASE_EXTN_IFACE = 2,
        EXTN_HANDLER_CMD_LAST
    };
};


#endif//PVPLAYER_EXT_HANDLER_H_INCLUDED
