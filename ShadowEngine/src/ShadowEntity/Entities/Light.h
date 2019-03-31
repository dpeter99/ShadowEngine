//
// Created by dpete on 3/4/2019.
//

#ifndef SHADOWENGINE_LIGHT_H
#define SHADOWENGINE_LIGHT_H

#include "../Entity.h"

class Light : public ShadowEntity::Entity{
SHADOW_FUNC_DEC(Light)

public:
    void Draw() override;
};


#endif //SHADOWENGINE_LIGHT_H
