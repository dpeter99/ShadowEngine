# sdl2 cmake project-config input for ./configure scripts


set(SDL2_EXEC_FOLDER ${DEPENDENCIES_FOLDER}/SDL2/bin/)

set(SDL2_EXEC
        ${SDL2_EXEC_FOLDER}SDL2.dll
        ${SDL2_EXEC_FOLDER}zlib1.dll
        )


set(SDL2_TARGETS_FOLDER ${DEPENDENCIES_FOLDER}/SDL2/lib/)

set(SDL2_TARGETS
        ${SDL2_TARGETS_FOLDER}libSDL2.dll.a
        ${SDL2_TARGETS_FOLDER}libSDL2_test.a
        ${SDL2_TARGETS_FOLDER}libSDL2main.a
        )

set(SDL2_INCLUDES
        ${DEPENDENCIES_FOLDER}/SDL2/include)


