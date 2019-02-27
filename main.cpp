#include <iostream>
#include "ShadowEntity/EntityRegistry.h"
#include "AssetLoader.h"


int main() {

    //ShadowEntity::EntityRegistry registry;

    //registry.ListPreRegisteredEntitys();

    AssetLoader loader;
    loader.LoadMap();

    return 0;
}