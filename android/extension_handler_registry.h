#ifndef EXTENSION_HANDLER_REGISTRY_H_INCLUDED
#define EXTENSION_HANDLER_REGISTRY_H_INCLUDED

#ifndef OSCL_VECTOR_H_INCLUDED
#include "oscl_vector.h"
#endif

#ifndef OSCL_MEM_H_INCLUDED
#include "oscl_mem.h"
#endif

#include "oscl_string.h"
#include "dispatch.h"
#include "extension_registry_populator_interface.h"

class OsclSharedLibrary;

class PVPlayerExtensionRegistry : public ExtensionRegistryInterface
{
public:

    PVPlayerExtensionRegistry(); 
    /**
     * Function for parsing the configuration file and load the Extension libraries
     *
     * @param configFile
     *        Configuration file to be parsed for extension libraries which support registry populator interface
    */
    void loadPVPlayerExtensions(const OSCL_String& configFile);
    /**
     * Function for unloading the Extension libraries
    */
    void removePVPlayerExtensions();
    /**
    * Function for Creating Extension specified by the String UUID
    */
    virtual IDispatch* createExtension(const String16& extnIfaceUID,PVPlayerExtensionHandler& extnHandler );
    
    /**
    * Function for Populating the registry
    */
    virtual void registerExtension(const PVPlayerExtnInfo& extnInfo){
        mType.push_back(extnInfo);
    }
    virtual ~PVPlayerExtensionRegistry();

private:
    Oscl_Vector<PVPlayerExtnInfo, OsclMemAllocator> mType;
    typedef struct
    {
        OsclSharedLibrary* mLib;
        ExtnRegPopulatorInterface* mExtnLibIfacePtr;
    } PVPlayerExtnSharedLibInfo;
    Oscl_Vector<PVPlayerExtnSharedLibInfo*, OsclMemAllocator> mExtnIfaceInfoList;
};

//Class used by Extension Handler for populating the registry
class PVPlayerExtnPopulator
{
public:
    static void populate(PVPlayerExtensionRegistry&);
    static void depopulate(PVPlayerExtensionRegistry&);
private:
    PVPlayerExtnPopulator();
};


#endif // EXTENSION_HANDLER_REGISTRY_H_INCLUDED


