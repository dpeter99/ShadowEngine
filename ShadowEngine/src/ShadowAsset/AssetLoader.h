//
// Created by dpete on 2/26/2019.
//

#ifndef SHADOWENGINE_MAPLOADER_H
#define SHADOWENGINE_MAPLOADER_H

#include <map>
#include "list"
#include "ShadowMap/ShadowMapChunk.h"
#include "ShadowMap/ShadowWorld.h"

class Element{
public:
    Element* parent;

    std::string name;

    bool isBlock;

    std::string value;

    std::list<Element*> properties_old;
    std::map<std::string, Element*> properties;

	std::string GetStringProperty(std::string name);

    ~Element();
};

class AssetLoader {

    static Element* LoadFile(std::string name);

public:
    static ShadowMapChunk* LoadMap(std::string name);

    static ShadowWorld* LoadWorld(std::string name);

	template <class T>
	static T* LoadAsset(std::string name);
};

#endif //SHADOWENGINE_MAPLOADER_H


