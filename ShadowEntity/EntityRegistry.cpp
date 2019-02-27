//
// Created by dpete on 2/15/2019.
//

#include <iostream>
#include "EntityRegistry.h"

namespace ShadowEntity {

    //PreRegistry

    //std::map<std::string, int> EntityRegistry::PreEntityRegistryMap;

    bool EntityRegistry::PreRegisterEntity(std::string id, Entity *entityTemplate) {
        EntityRegistry::PreEntityRegistryMap[id]=entityTemplate;
        return true;
    }

    void EntityRegistry::ListPreRegisteredEntitys() {
        for (auto it=PreEntityRegistryMap.begin(); it != PreEntityRegistryMap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }

    //Registry
    EntityRegistry::EntityRegistry() {
        //Setup
        printf("EntityRegistrySetup \n");
        PreRegisterDefaults();

    }

}