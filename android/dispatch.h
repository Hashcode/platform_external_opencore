#ifndef DISPATCH_H_INCLUDED
#define DISPATCH_H_INCLUDED

#include "binder/Parcel.h"
using namespace android;

class PlayerExtensionCommand;
class PVCmdResponse;
/**
 * IDispatch Class
 */
class IDispatch {
public:
/**
     * Every Extension needs to implement this interface. This function is used
     * to execute different commands based on the function index.
     *
     * @param data
     *        It is a parcel which contains the information like index
     *        of the function to be executed along with its arguments
     * @param reply
     *        It is a parcel which contains the information which needs to be
     *        returned to the Application
     * @param cmd
     *        The extension command meant to be executed
     * @return
     *        Completion status
 */
    virtual status_t invoke(const Parcel& data, Parcel& reply, PlayerExtensionCommand* cmd)=0;
/**
     * If any engine commands were scheduled by this extension, this function will be
     * called upon completion.
     *
     * @param cmd
     *        It is the command which has completed
     * @param resp
     *        It is the respose to the completed command.
     * @return
     *        false= let playerdriver handle standard command completion
     *        true = command was handled (e.g. FinishSyncCommand, commandFailed) and aCmd deleted
*/
    virtual bool commandCompleted(PlayerExtensionCommand* cmd, const PVCmdResponse &resp) {
        return false;
    }
/**
     * Destructor
*/    
    virtual ~IDispatch() {}
};


#endif//DISPATCH_H_INCLUDED
