//
// Created by dpete on 2/26/2019.
//

#ifndef SHADOWENGINE_SHADOWMAP_H
#define SHADOWENGINE_SHADOWMAP_H


#include <string>
#include <vector>


class ShadowMapLayer
{
    int(*map); //a row mayor flat 2d array

    std::string name;

    bool visible;
};

class ShadowMap {
public:
    std::string name;

    int height;
    int width;

    int tileHeight;
    int tileWidth;

    std::vector<ShadowMapLayer*>* layers;
};


#endif //SHADOWENGINE_SHADOWMAP_H
