//
// Created by dpete on 2/15/2019.
//

#ifndef SHADOWENGINE_ENTITYMANAGER_H
#define SHADOWENGINE_ENTITYMANAGER_H


#include <list>
#include <map>


#include "Entity.h"
//#include "Entities/Player.h"


namespace ShadowEntity {

    class EntityRegistry {
    private:


    public:
        EntityRegistry();

        void PreRegisterDefaults();

        std::map<std::string,ShadowEntity::Entity*> PreEntityRegistryMap;

        bool PreRegisterEntity(std::string, Entity *entityTemplate);

        void ListPreRegisteredEntitys();
    };

    class ReflectionReference{
    public:
        std::string name;
        ShadowEntity::Entity entityTemplateInstance;
    };
}

#endif //SHADOWENGINE_ENTITYMANAGER_H
