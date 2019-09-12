#pragma once


#define Entity_Base(Type, BaseType)		\
public:											\
Type(ShadowScene* scene) : BaseType(scene) {}	\
Type() : BaseType() {}	\
ShadowEntity::Entity* Type::Create(ShadowScene* scene) {			\
Type* res = new Type(scene);							\
return res;									    \
}												\
private:

#define Entity_Base_NoCtor(Type, BaseType)		\
public:											\
ShadowEntity::Entity* Type::Create(ShadowScene* scene) {			\
Type* res = new Type(scene);							\
return res;									    \
}												\
private:
