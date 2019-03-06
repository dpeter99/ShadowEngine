//
// Created by dpete on 3/4/2019.
//

#ifndef SHADOWENGINE_ENTITYBASE_H
#define SHADOWENGINE_ENTITYBASE_H


#define SHADOW_FUNC_IMPL(Type)          \
ShadowEntity::Entity* Type::Create() {  \
Type* res = new Type();                 \
return res;                             \
}                                       \

#define SHADOW_FUNC_DEC(Type)   \
public:                         \
Entity* Create() override;      \
private:                        \



#endif //SHADOWENGINE_ENTITYBASE_H
