//
// Created by dpete on 2/26/2019.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "list"

#include "AssetLoader.h"
#include "src/ShadowMap/ShadowMapChunk.h"
#include "src/ShadowEntity/EntityRegistry.h"

ShadowMapChunk* AssetLoader::LoadMap(std::string name) {

    ShadowMapChunk* map = new ShadowMapChunk();

    Element& root = LoadFile(name);

    auto it = root.properties.find("Map");
    if(it != root.properties.end())
    {
        auto mapElement = it->second;

        map->height = std::stoi(mapElement->properties.find("Height")->second->value);
        map->width = std::stoi(mapElement->properties.find("Width")->second->value);

        map->tileWidth = std::stoi(mapElement->properties.find("TileWidth")->second->value);
        map->tileHeight = std::stoi(mapElement->properties.find("TileHeight")->second->value);


        //map->layers = std::vector<ShadowMapLayer*>(mapElement->properties.find("Layers")->second->properties.size());
        map->layers.reserve(mapElement->properties.find("Layers")->second->properties.size());
        int pos = 0;
        for (auto i : mapElement->properties.find("Layers")->second->properties) {
            auto layerElement = i.second;

            auto layer = new ShadowMapLayer(*map);

            layer->data = new int[map->width*map->height];
            layer->name = layerElement->name;


            std::string parse = layerElement->properties.find("Map")->second->value;
            std::replace( parse.begin(), parse.end(), '.', ' ');
            std::stringstream parser(parse);
            for (int y = 0; y < map->height; ++y) {
                for (int x = 0; x < map->width; ++x) {
                    int a;
                    parser >> a ;
                    layer->SetTile(ShadowMath::Vector2int(x,y),a);
                }
            }

            //map->layers[pos] = layer;
            map->layers.push_back(layer);

            pos++;
        }

        //Get the space for the entities
        auto entities = mapElement->properties.find("Entities")->second->properties;
        map->entities.reserve(entities.size());
        //Load all the entities
        for (auto i : entities) {
            auto entityElement = i.second;

            std::string name = entityElement->name;

            ShadowEntity::Entity* ent;
            ent = ShadowEntity::EntityRegistry::_registry->InstaciateEntity(name);



            map->entities.push_back(ent);

        }

    }

    delete &root;

    std::cout << "END" << std::endl;

    return map;
}

ShadowWorld* AssetLoader::LoadWorld(std::string name) {
    ShadowWorld* world = new ShadowWorld();

    Element& root = LoadFile(name);

    auto it = root.properties.find("Map");
    if(it != root.properties.end()) {
        auto worldElement = it->second;

        world->name = worldElement->properties.find("Name")->second->value;

        std::string parse = worldElement->properties.find("ChunkSize")->second->value;
        std::replace( parse.begin(), parse.end(), 'x', ' ');
        std::stringstream parser(parse);
        parser >> world->chunkSizeX;
        parser >> world->chunkSizeY;

        world->maps.reserve(worldElement->properties.find("Maps")->second->properties.size());
        int pos = 0;
        for (auto i : worldElement->properties.find("Maps")->second->properties) {
            auto layerElement = i.second;

            auto map = new WorldMap(world);

            map->name = layerElement->properties.find("Name")->second->value;
            map->id = layerElement->properties.find("ID")->second->value;


        }

    }
    return world;
}

///Parses a file into DOM
///The caller has to call free on the returned Element tree
Element& AssetLoader::LoadFile(std::string name) {
    //The current node that we are building
    auto *context = new Element;

    //Top level Element
    Element &base = *context;

    //The new node that will be a child of the context
    auto *current = new Element;

    std::ifstream inputFileStream(name+".txt");



    std::string buffer;

    char c;
    while (!inputFileStream.eof()) {
        inputFileStream.get(c);
        if (c == ':') {
            //The stuff in the buffer is a parameter name
            std::cout <<"Name: "<< buffer;
            current->name = buffer;
            buffer = "";
        } else if (c == '{') {
            //Start of a new block
            current->isBlock = true;
            current->parent = context;
            context->properties[current->name]=current;
            context = current;

            current = new Element;

        } else if (c == ',') { // End of a property
            //The stuff is the value
            std::cout<< "Value: " << buffer<<std::endl;
            current->value = buffer;
            current->parent = context;
            current->isBlock = false;
            buffer = "";

            context->properties[current->name]=current;

            current = new Element();
        } else if(c == '}'){ // End of a block
            context = context->parent;
        } else {
            if (std::isspace(c) == 0) {
                buffer += c;
            }
        }
    }

    std::cout << "END" << std::endl;

    return base;

}

Element::~Element() {
    //now onto the recursion
    for (auto const& i : this->properties) {
        delete i.second;
    }

}
