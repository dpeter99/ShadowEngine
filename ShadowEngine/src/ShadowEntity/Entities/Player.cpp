//
// Created by dpete on 2/17/2019.
//

#include "Player.h"

namespace ShadowEntity {

    SHADOW_FUNC_IMPL(Player)

    /*
    Entity* Player::Create() {
        Player* res = new Player();

        return res;
    }
    */

    void Player::Draw() {
        std::cout<<"Player";
    }


    //bool Player::registered = ShadowEntity::EntityRegistry::PreRegisterEntity("Player");

}