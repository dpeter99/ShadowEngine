#include <iostream>
#include "ShadowEntity/EntityRegistry.h"
#include "AssetLoader.h"
#include "ShadowMap/ShadowMapRenderer.h"


int main() {

    //ShadowEntity::EntityRegistry registry;

    //registry.ListPreRegisteredEntitys();

    AssetLoader loader;
    ShadowMap* map = loader.LoadMap();

    ShadowMapRenderer::RenderMap(*map);

    return 0;
}