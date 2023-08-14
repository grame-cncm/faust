#ifndef faust_dspfactoryowner_h
#define faust_dspfactoryowner_h

#include <iostream>
#include <map>
#include <assert.h>
#include "faust/dsp/llvm-dsp.h"

class dspFactoryOwner
{
public:
    ~dspFactoryOwner()
    {
        for (auto &factory: fDSPFactories) {
            deleteDSPFactory(factory.second);
        }
    }
    
    dsp *createDSPInstanceFromString(
            const std::string &appName,
            const std::string &dspContent
    )
    {
        auto factory{fDSPFactories.find(appName)};
        
        if (factory == fDSPFactories.end()) {
            std::string errorMessage;
            
            fDSPFactories.insert(std::make_pair(
                    appName,
                    createDSPFactoryFromString(appName, dspContent, 0, nullptr, "", errorMessage)
            ));
            
            factory = fDSPFactories.find(appName);
            
            if (!factory->second) {
                std::cout << errorMessage;
            }
            assert(factory->second);
        }
        
        return factory->second->createDSPInstance();
    }
    
    dsp *createDSPInstanceFromPath(const std::string &path,
                                   int argc = 0,
                                   const char *argv[] = nullptr)
    {
        auto key{path};
        for (int i{0}; i < argc; ++i) {
            key.append(argv[i]);
        }
        auto factory{fDSPFactories.find(key)};
        
        if (factory == fDSPFactories.end()) {
            std::string errorMessage;
            std::cout << "Creating DSP from file with key " << key << "\n";
            
            fDSPFactories.insert(std::make_pair(
                    key,
                    createDSPFactoryFromFile(path, argc, argv, "", errorMessage)
            ));
            
            factory = fDSPFactories.find(key);
            
//            std::cout << "factory: " << factory->second << "\n";
            if (!factory->second) {
                std::cout << "Error: " << errorMessage;
            }
            assert(factory->second);
        }
        
        return factory->second->createDSPInstance();
    }

private:
    std::map<std::string, llvm_dsp_factory *> fDSPFactories;
};

#endif //faust_dspfactoryowner_h
