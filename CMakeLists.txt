cmake_minimum_required(VERSION 3.13)
project(ShadowEngine)

set(CMAKE_CXX_STANDARD 14)


include(dependencies/dependencies.cmake)

include_directories(${DEPENDENCIES_INCLUDES})
include_directories(.)
include_directories(dependencies/GLAD/include)

add_executable(ShadowEngine
        src/glad/glad.c


        main.cpp

        src/ShadowMath/Vector2float.h src/ShadowMath/Vector2float.cpp
        src/ShadowMath/Vector2int.h src/ShadowMath/Vector2int.cpp
        src/ShadowEntity/Entity.cpp src/ShadowEntity/Entity.h
        src/ShadowEntity/EntityRegistry.cpp src/ShadowEntity/EntityRegistry.h src/ShadowEntity/DefaultEntities.cpp
        src/ShadowEntity/Entities/Player.cpp src/ShadowEntity/Entities/Player.h
        src/ShadowMap/ShadowMap.cpp src/ShadowMap/ShadowMap.h
        AssetLoader.cpp AssetLoader.h
        src/ShadowMap/ShadowMapRenderer.cpp src/ShadowMap/ShadowMapRenderer.h
        src/ShadowEntity/Entities/Light.cpp src/ShadowEntity/Entities/Light.h
        src/ShadowEntity/EntityBase.h
        )


target_link_libraries(ShadowEngine mingw32)

target_link_libraries(ShadowEngine ${DEPENDENCIES_TARGETS})

target_link_libraries(ShadowEngine user32)
target_link_libraries(ShadowEngine gdi32)
target_link_libraries(ShadowEngine winmm)
target_link_libraries(ShadowEngine dxguid)




ADD_CUSTOM_COMMAND(TARGET ShadowEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/dependencies/SDL2/bin"
        $<TARGET_FILE_DIR:ShadowEngine>
        COMMENT “copying dlls …”
        )