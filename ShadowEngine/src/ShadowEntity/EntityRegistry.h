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
        static EntityRegistry* _registry;

        EntityRegistry();


        //Pre registry
        std::map<std::string,ShadowEntity::Entity*> EntityRegistryMap;



        bool RegisterEntity(std::string, Entity *entityTemplate);

        void ListPreRegisteredEntitys();


        //Create a instance of the specified Entity
        Entity* InstaciateEntity(std::string);


        //Will be generated at compile time
        //For now manually made
        void PreRegisterDefaults();
    };

}

#endif //SHADOWENGINE_ENTITYMANAGER_H
