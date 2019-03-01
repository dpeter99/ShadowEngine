//
// Created by dpete on 2/26/2019.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "list"

#include "AssetLoader.h"
#include "ShadowMap.h"

void AssetLoader::LoadMap() {

    ShadowMap* map = new ShadowMap();

    Element& root = LoadFile();

    auto it = root.properties.find("Map");
    if(it != root.properties.end())
    {
        auto mapElement = it->second;

        map->height = std::stoi(mapElement->properties.find("Height")->second->value);
        map->width = std::stoi(mapElement->properties.find("Width")->second->value);

        map->tileWidth = std::stoi(mapElement->properties.find("TileWidth")->second->value);
        map->tileHeight = std::stoi(mapElement->properties.find("TileHeight")->second->value);


        map->layers = new std::vector<ShadowMapLayer*>(mapElement->properties.find("Layers")->second->properties.size());
        int pos = 0;
        for (auto i : mapElement->properties.find("Layers")->second->properties) {
            auto layerElement = i.second;

            auto layer = new ShadowMapLayer(*map);

            layer->data = new int[map->width*map->height];
            layer->name = layerElement->name;

            std::stringstream parser(layerElement->properties.find("Map")->second->value);
            for (int y = 0; y < map->height; ++y) {
                for (int x = 0; x < map->width; ++x) {
                    int a;
                    parser >> a ;
                    parser >> '.';
                    layer->SetTile(Vector2int(x,y),0);
                }
            }

            (*map->layers)[pos] = layer;

            pos++;
        }
    }

    delete &root;

    std::cout << "END" << std::endl;
}

//Property Name: Value

//Name : {stuff in the block}

///Parses a file into DOM
///The caller has to call free on the returned Element tree
Element& AssetLoader::LoadFile() {
    //The current node that we are building
    auto *context = new Element;

    //Top level Element
    Element &base = *context;

    //The new node that will be a child of the context
    auto *current = new Element;

    std::ifstream inputFileStream("Test.txt");



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
