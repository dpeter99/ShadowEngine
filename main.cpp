#include <iostream>
#include "ShadowEntity/EntityRegistry.h"
#include "AssetLoader.h"
#include "ShadowMap/ShadowMapRenderer.h"

// OpenGL headers
#define GLEW_STATIC

#include "glad/glad.h"
#include "GL/glu.h"
#include "GL/gl.h"

#include <SDL2/SDL.h>


int main(int argc, char *argv[]) {

    ShadowEntity::EntityRegistry registry;

    //registry.ListPreRegisteredEntitys();

    AssetLoader loader;
    ShadowMap *map = loader.LoadMap();

    ShadowMapRenderer::RenderMap(*map);


    //GL test

    bool quit;

    SDL_Window *window;
    SDL_GLContext glContext;
    SDL_Event sdlEvent;


    quit = false;

    //Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Initialize video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        // Display error message
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }


    // Create window
    window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL) {
        // Display error message
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create OpenGL context
    glContext = SDL_GL_CreateContext(window);

    if (glContext == NULL) {
        // Display error message
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    } else {
        // Initialize glew
        //glewInit();
    }




    // Game loop
    while (!quit) {
        while (SDL_PollEvent(&sdlEvent) != 0) {
            // Esc button is pressed
            if (sdlEvent.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Set background color as cornflower blue
        glClearColor(0.39f, 0.58f, 0.93f, 1.f);
        // Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Update window with OpenGL rendering
        SDL_GL_SwapWindow(window);
    }

    char s;
    std::cin >> s;

    return 0;
}