# sdl2 cmake project-config input for ./configure scripts

set(SDL_EXEC_FOLDER dependencies/bin/)

set(SDL_TARGETS_FOLDER dependencies/lib/)

set(SDL2_EXEC
        ${SDL_EXEC_FOLDER}libFLAC-8.dll
        ${SDL_EXEC_FOLDER}libfreetype-6.dll
        ${SDL_EXEC_FOLDER}libjpeg-9.dll
        ${SDL_EXEC_FOLDER}libmodplug-1.dll
        ${SDL_EXEC_FOLDER}libmpg123-0.dll
        ${SDL_EXEC_FOLDER}libogg-0.dll
        ${SDL_EXEC_FOLDER}libpng16-16.dll
        ${SDL_EXEC_FOLDER}libtiff-5.dll
        ${SDL_EXEC_FOLDER}libvorbis-0.dll
        ${SDL_EXEC_FOLDER}libvorbisfile-3.dll
        ${SDL_EXEC_FOLDER}libwebp-7.dll
        ${SDL_EXEC_FOLDER}SDL2.dll
        ${SDL_EXEC_FOLDER}SDL2_gfx.dll
        ${SDL_EXEC_FOLDER}SDL2_image.dll
        ${SDL_EXEC_FOLDER}SDL2_mixer.dll
        ${SDL_EXEC_FOLDER}SDL2_net.dll
        ${SDL_EXEC_FOLDER}SDL2_ttf.dll
        ${SDL_EXEC_FOLDER}zlib1.dll
        )

set(SDL2_TARGETS
        ${SDL_TARGETS_FOLDER}libSDL2main.a
        ${SDL_TARGETS_FOLDER}libSDL2.dll.a
        ${SDL_TARGETS_FOLDER}libSDL2_gfx.a
        ${SDL_TARGETS_FOLDER}libSDL2_image.dll.a
        ${SDL_TARGETS_FOLDER}libSDL2_mixer.dll.a
        ${SDL_TARGETS_FOLDER}libSDL2_net.dll.a
        ${SDL_TARGETS_FOLDER}libSDL2_ttf.dll.a
        ${SDL_TARGETS_FOLDER}libSDL2_test.a
        )
