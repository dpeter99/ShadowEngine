//
// Created by dpete on 2/17/2019.
//

#ifndef SHADOWENGINE_PLAYER_H
#define SHADOWENGINE_PLAYER_H

#include "../EntityRegistry.h"
#include "../Entity.h"

namespace ShadowEntity {
    class Player : public Entity {
    public:
        static std::string id;

        Entity& Create();

    protected:

        static bool registered;
    };
}

#endif //SHADOWENGINE_PLAYER_H
