//#define LOG_NDEBUG 0
#define LOG_TAG "RegistryLoader"
#include <utils/Log.h>

#include "extension_handler_registry.h"
#include "PVPlayerExtHandler.h"

#include "oscl_shared_library.h"
#include "oscl_library_list.h"
#include "oscl_configfile_list.h"
#include "osclconfig_lib.h"
#include "oscl_shared_lib_interface.h"


PVPlayerExtensionRegistry::PVPlayerExtensionRegistry()
{
    // The default value reserved is 4
    mType.reserve(4);
    LOGV("PVPlayerExtensionRegistry::PVPlayerExtensionRegistry OUT");
}

PVPlayerExtensionRegistry::~PVPlayerExtensionRegistry()
{
    mType.clear();
    LOGV("PVPlayerExtensionRegistry::~PVPlayerExtensionRegistry OUT");
}

void PVPlayerExtensionRegistry::loadPVPlayerExtensions(const OSCL_String& configFilePath)
{
    LOGV("PVPlayerExtensionRegistry::loadPVPlayerExtensions() IN");
    OsclLibraryList libList;
    libList.Populate(PV_EXTN_REGISTRY_POPULATOR_INTERFACE, configFilePath);

    for (unsigned int i = 0; i < libList.Size(); i++)
    {
        OsclSharedLibrary* lib = OSCL_NEW(OsclSharedLibrary, ());
        if (lib->LoadLib(libList.GetLibraryPathAt(i)) == OsclLibSuccess) {
            OsclAny* interfacePtr = NULL;
            OsclLibStatus result = lib->QueryInterface(PV_EXTN_REGISTRY_POPULATOR_INTERFACE, (OsclAny*&)interfacePtr);
            if (result == OsclLibSuccess && interfacePtr != NULL) {
                PVPlayerExtnSharedLibInfo *libInfo = (PVPlayerExtnSharedLibInfo *)oscl_malloc(sizeof(PVPlayerExtnSharedLibInfo));
                if (NULL != libInfo) {
                    libInfo->mLib = lib;
                    ExtnRegPopulatorInterface* extnIntPtr = OSCL_DYNAMIC_CAST(ExtnRegPopulatorInterface*, interfacePtr);
                    libInfo->mExtnLibIfacePtr = extnIntPtr;
                    extnIntPtr->registerExtensions(this);
                    // save for depopulation later
                    mExtnIfaceInfoList.push_front(libInfo);
                    continue;
                }
            } else {
                LOGV("PVPlayerExtensionRegistry::loadPVPlayerExtensions() QueryInterface() of PV_EXTNIFACE_REGISTRY_POPULATOR_INTERFACE for library %s failed.", libList.GetLibraryPathAt(i).get_cstr());
            }
        } else {
            LOGV("PVPlayerExtensionRegistry::loadPVPlayerExtensions() LoadLib() of library %s failed.", libList.GetLibraryPathAt(i).get_cstr());
        }
        lib->Close();
        OSCL_DELETE(lib);
    }
    LOGV("PVPlayerExtensionRegistry::loadPVPlayerExtensions() OUT");
}

void PVPlayerExtensionRegistry::removePVPlayerExtensions()
{
    LOGV("PVPlayerExtensionRegistry::removePVPlayerExtensions() IN");

    while (!mExtnIfaceInfoList.empty())
    {
        PVPlayerExtnSharedLibInfo *libInfo = mExtnIfaceInfoList.front();
        mExtnIfaceInfoList.erase(mExtnIfaceInfoList.begin());

        OsclSharedLibrary* lib = libInfo->mLib;
        oscl_free(libInfo);
        lib->Close();
        OSCL_DELETE(lib);
    }
    LOGV("PVPlayerExtensionRegistry::removePVPlayerExtensions() OUT");
}

IDispatch* PVPlayerExtensionRegistry::createExtension(const String16& extnIfaceUID,PVPlayerExtensionHandler& extnHandler )
{
    LOGV("PVPlayerExtensionRegistry::createExtension() IN");
    bool foundFlag = false;
    uint32 extnSearchCount = 0;

    while (extnSearchCount < mType.size())
    {
        //Search if the UUID's will match
        if (extnIfaceUID == (String16(mType[extnSearchCount].mExtnUID))) {
            //Since the UUID's match set the flag to true
            foundFlag = true;
            break;
        }
        extnSearchCount++;
    }
    
    if (foundFlag) {
        PVPlayerExtnInfo* extnInfo = &mType[extnSearchCount];
        IDispatch* extInterface = NULL;

        if (NULL != extnInfo->mExtnCreateFunc) {
            extInterface = (*(mType[extnSearchCount].mExtnCreateFunc))(extnHandler);
        }
        LOGV("PVPlayerExtensionRegistry::createExtension OUT extInterface = %d", (int32_t)extInterface);
        return extInterface;
    } else {
        LOGV("PVPlayerExtensionRegistry::createExtension OUT");
        return NULL;
    }
}

void PVPlayerExtnPopulator::populate(PVPlayerExtensionRegistry& extnIfaceRegistry)
{
    LOGV("PVPlayerExtnPopulator::populate IN");
    OsclConfigFileList aCfgList;
    // collects all config files from the project specified directory
    if (NULL != PV_DYNAMIC_LOADING_CONFIG_FILE_PATH) {
        OSCL_HeapString<OsclMemAllocator> configFilePath = PV_DYNAMIC_LOADING_CONFIG_FILE_PATH;
        aCfgList.Populate(configFilePath);
    }
    // populate libraries from all config files
    for (uint k = 0; k < aCfgList.Size(); k++)
    {
        extnIfaceRegistry.loadPVPlayerExtensions(aCfgList.GetConfigfileAt(k));
    }
    LOGV("PVPlayerExtnPopulator::populate OUT");
}
void PVPlayerExtnPopulator::depopulate(PVPlayerExtensionRegistry& extnIfaceRegistry)
{
    extnIfaceRegistry.removePVPlayerExtensions();
    LOGV("PVPlayerExtnPopulator::depopulate OUT");
}
