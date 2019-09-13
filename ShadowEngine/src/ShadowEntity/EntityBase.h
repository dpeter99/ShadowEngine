#pragma once


namespace ShadowEngine::ShadowEntity {

#define Entity_Base(Type, BaseType)		\
public:											\
Type(ShadowEngine::Scene::ShadowScene* scene) : BaseType(scene) {}	\
Type() : BaseType() {}	\
ShadowEngine::ShadowEntity::Entity* Type::Create(ShadowEngine::Scene::ShadowScene* scene) override {			\
Type* res = new Type(scene);							\
return res;									    \
}												\
private:

#define Entity_Base_NoCtor(Type, BaseType)		\
public:											\
ShadowEngine::ShadowEntity::Entity* Type::Create(ShadowEngine::Scene::ShadowScene* scene) override {			\
Type* res = new Type(scene);							\
return res;									    \
}												\
private:

}