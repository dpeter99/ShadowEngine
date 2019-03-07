# sdl2 cmake project-config input for ./configure scripts

set(DEPENDENCIES_FOLDER ${PROJECT_SOURCE_DIR}/dependencies)

include(${DEPENDENCIES_FOLDER}/SDL2/SDL2.cmake)



set(DEPENDENCIES_EXEC
        ${SDL2_EXEC}
        ${DEPENDENCIES_FOLDER}/SDL2/bin/SDL2.dll
        )

set(DEPENDENCIES_TARGETS
        ${SDL2_TARGETS}
        ${DEPENDENCIES_FOLDER}/SDL2/lib/libSDL2.dll.a
        ${DEPENDENCIES_FOLDER}/SDL2/lib/libSDL2_test.a
        ${DEPENDENCIES_FOLDER}/SDL2/lib/libSDL2main.a
        )

set(DEPENDENCIES_INCLUDES
        ${SDL2_INCLUDES}
        )

