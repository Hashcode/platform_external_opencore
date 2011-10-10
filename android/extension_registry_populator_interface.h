#ifndef EXTENSION_REGISTRY_POPULATOR_INTERFACE_H_INCLUDED
#define EXTENSION_REGISTRY_POPULATOR_INTERFACE_H_INCLUDED

#include "dispatch.h"
#include "utils/String16.h"

//UUid for the Registry populator Interface which Extension handler looks for in the configuration files while loading the extensions
#define PV_EXTN_REGISTRY_POPULATOR_INTERFACE OsclUuid(0xf5a4c808,0x963b,0x48db,0xbd,0x13,0x2f,0x7a,0x1f,0x2b,0x41,0x2f)

//String UUIDs for extensions
#define PLAYBACKRATE_EXTN_UUID "com.pv.extensions.playbackrate"
#define ASX_EXTN_UUID "com.pv.extensions.asxextension"
#define GETMETADATA_EXTN_UUID "com.pv.extensions.getmetadataextension"
#define DLA_EXTN_UUID "com.pv.extensions.dlaextension"

class PVPlayerExtensionHandler;
class ExtensionRegistryInterface;

/**
 * ExtnRegPopulatorInterface
 * Extension handler looks for Libraries supporting ExtnRegPopulatorInterface as mentioned in the configuration files
 */
class ExtnRegPopulatorInterface
{
public:
    virtual void registerExtensions(ExtensionRegistryInterface* aRegistry) = 0;
};

/**
 * PVPlayerExtnInfo
 * It has the information regarding the creation and deletion of extensions along with its UUID.
 */
class PVPlayerExtnInfo
{
public:
    PVPlayerExtnInfo()
    {
        mExtnCreateFunc = NULL;
        mExtnReleaseFunc = NULL;
        mExtnUID = NULL;
    }

    PVPlayerExtnInfo(const PVPlayerExtnInfo& info)
    {
        mExtnUID = info.mExtnUID;
        mExtnCreateFunc = info.mExtnCreateFunc;
        mExtnReleaseFunc = info.mExtnReleaseFunc;
    }

    ~PVPlayerExtnInfo()
    {
    }
    
    IDispatch*(*mExtnCreateFunc)(PVPlayerExtensionHandler&);
    bool (*mExtnReleaseFunc)(IDispatch *);
    const char* mExtnUID;
};

/**
 * ExtensionRegistryInterface
 * This is the interface for Extension registry.
 */
class ExtensionRegistryInterface
{
public:
/**
     * This function creates the requested Extension, if the specified String UUID is present in the registry
     *
     * @param ifaceName
     *        String UUID of the Extension which needs to be created
     * @param extnHandler
     *        Extension handler reference
     * @return
     *        Handle to the instance of the extension
 */
    virtual IDispatch* createExtension(const String16& ifaceName,PVPlayerExtensionHandler& extnHandler ) = 0;

/**
     * This function is used for registering new extension.
     *
     * @param extnInfo
     *        Infornmation required for creation and deletion of extension
 */
    virtual void registerExtension(const PVPlayerExtnInfo& extnInfo) = 0;
};

#endif // EXTENSION_REGISTRY_POPULATOR_INTERFACE_H_INCLUDED


