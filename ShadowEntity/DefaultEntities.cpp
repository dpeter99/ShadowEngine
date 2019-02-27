//
// Created by dpete on 2/22/2019.
//

#include "EntityRegistry.h"
#include "Entity.h"

#include "Entities/Player.h"

namespace ShadowEntity {

    void ShadowEntity::EntityRegistry::PreRegisterDefaults() {
        this->PreRegisterEntity("Player",new Player());
    }
}
