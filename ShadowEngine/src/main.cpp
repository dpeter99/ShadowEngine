#include <iostream>
#include "ShadowAsset/AssetLoader.h"

// OpenGL headers
#include "glad/glad.h"
#include "GL/gl.h"

#include <SDL2/SDL.h>
#include <ShadowEntity/EntityRegistry.h>
#include <ShadowMap/ShadowMapRenderer.h>
#include "ShadowApplication.h"


int main(int argc, char *argv[]) {


    ShadowEntity::EntityRegistry registry;

    //registry.ListPreRegisteredEntitys();

    //AssetLoader loader;
	//ShadowWorld* w = loader.LoadWorld("Resources/Worlds/Default/overworld.txt");
	//w->SetActiveMap("default");
	//w->Update(ShadowMath::Vector2float(0, 0));
    //ShadowMapRenderer::RenderMap(*map);

	ShadowApplication app;
	app.Init();
	app.Start();
	


    //GL test

    bool quit;

    


	

    quit = false;



    




	/*
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
	*/
    char s;
    std::cin >> s;

    return 0;
}
