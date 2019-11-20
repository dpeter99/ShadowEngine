#pragma once


namespace ShadowEngine::ShadowEntity {

#define Entity_Base(Type, BaseType)		\
public:											\
Type(ShadowEngine::EntitySystem::Scene* scene) : BaseType(scene) {}	\
Type() : BaseType() {}	\
ShadowEngine::EntitySystem::Entity* Type::Create(ShadowEngine::EntitySystem::Scene* scene) override {			\
Type* res = new Type(scene);							\
return res;									    \
}												\
private:

#define Entity_Base_NoCtor(Type, BaseType)		\
public:											\
ShadowEngine::EntitySystem::Entity* Type::Create(ShadowEngine::EntitySystem::Scene* scene) override {			\
Type* res = new Type(scene);							\
return res;									    \
}												\
private:

}