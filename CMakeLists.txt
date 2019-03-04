cmake_minimum_required(VERSION 3.13)
project(ShadowEngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(ShadowEngine main.cpp
        ShadowMath/Vector2float.h ShadowMath/Vector2float.cpp
        ShadowMath/Vector2int.h ShadowMath/Vector2int.cpp
        ShadowEntity/Entity.cpp ShadowEntity/Entity.h
        ShadowEntity/EntityRegistry.cpp ShadowEntity/EntityRegistry.h ShadowEntity/DefaultEntities.cpp
        ShadowEntity/Entities/Player.cpp ShadowEntity/Entities/Player.h ShadowMap/ShadowMap.cpp ShadowMap/ShadowMap.h AssetLoader.cpp AssetLoader.h ShadowMap/ShadowMapRenderer.cpp ShadowMap/ShadowMapRenderer.h ShadowEntity/Entities/Light.cpp ShadowEntity/Entities/Light.h ShadowEntity/EntityBase.h)