#include <iostream>
#include "ShadowEntity/EntityRegistry.h"
#include "AssetLoader.h"
#include "ShadowMap/ShadowMapRenderer.h"

// OpenGL headers
#define GLEW_STATIC
//#include "GL/glew.h"
//#include "GL/glu.h"
//#include "GL/gl.h"

#include "SDL2/SDL.h"

int main() {

    ShadowEntity::EntityRegistry registry;

    //registry.ListPreRegisteredEntitys();

    AssetLoader loader;
    ShadowMap* map = loader.LoadMap();

    ShadowMapRenderer::RenderMap(*map);

    return 0;
}