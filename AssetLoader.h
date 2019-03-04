//
// Created by dpete on 2/26/2019.
//

#ifndef SHADOWENGINE_MAPLOADER_H
#define SHADOWENGINE_MAPLOADER_H

#include <map>
#include "ShadowMap/ShadowMap.h"

class Element{
public:
    Element* parent;

    std::string name;

    bool isBlock;

    std::string value;

    std::list<Element*> properties_old;
    std::map<std::string, Element*> properties;

    ~Element();
};

class AssetLoader {

    Element& LoadFile();

public:
    ShadowMap* LoadMap();

};

#endif //SHADOWENGINE_MAPLOADER_H
