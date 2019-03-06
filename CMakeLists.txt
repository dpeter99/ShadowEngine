cmake_minimum_required(VERSION 3.13)
project(ShadowEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)


include(dependencies/dependencies.cmake)

include_directories(${DEPENDENCIES_INCLUDES})
include_directories(.)
include_directories(GLAD/include)

add_executable(ShadowEngine
        GLAD/src/glad.c
        ${DEPENDENCIES_EXEC}


        main.cpp
        ShadowMath/Vector2float.h ShadowMath/Vector2float.cpp
        ShadowMath/Vector2int.h ShadowMath/Vector2int.cpp
        ShadowEntity/Entity.cpp ShadowEntity/Entity.h
        ShadowEntity/EntityRegistry.cpp ShadowEntity/EntityRegistry.h ShadowEntity/DefaultEntities.cpp
        ShadowEntity/Entities/Player.cpp ShadowEntity/Entities/Player.h
        ShadowMap/ShadowMap.cpp ShadowMap/ShadowMap.h
        AssetLoader.cpp AssetLoader.h
        ShadowMap/ShadowMapRenderer.cpp ShadowMap/ShadowMapRenderer.h
        ShadowEntity/Entities/Light.cpp ShadowEntity/Entities/Light.h
        ShadowEntity/EntityBase.h)


target_link_libraries(ShadowEngine mingw32)



#add_subdirectory(dependencies/GLAD/)
#target_link_libraries(ShadowEngine glad)

target_link_libraries(ShadowEngine ${DEPENDENCIES_TARGETS})



#target_link_libraries(ShadowEngine user32)
#target_link_libraries(ShadowEngine gdi32)
#target_link_libraries(ShadowEngine winmm)
#target_link_libraries(ShadowEngine dxguid)




ADD_CUSTOM_COMMAND(TARGET ShadowEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/dependencies/SDL2/bin"
        $<TARGET_FILE_DIR:ShadowEngine>
        COMMENT “copying dlls …”
        )