//
// Created by dpete on 2/12/2019.
//

#ifndef SHADOWENGINE_ENTITY_H
#define SHADOWENGINE_ENTITY_H

#include <string>
#include <iostream>

#include "EntityBase.h"

namespace ShadowEntity {


    class Entity {
    public:

        static std::string id;

        //static std::string Register();
    public:
        virtual Entity* Create();


        Entity();

        ~Entity();

        virtual void Start();

        virtual void Update();

        virtual void LateUpdate();

        virtual void Draw();

        friend std::ostream& operator<<(std::ostream& os, const Entity& dt);

    };

}
#endif //SHADOWENGINE_ENTITY_H
