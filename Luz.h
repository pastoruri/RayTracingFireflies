//
// Created by hgallegos on 23/08/2022.
//

#ifndef INC_20222_RAYTRACING_LUZ_H
#define INC_20222_RAYTRACING_LUZ_H

#include "vector.h"

class Luz {
public:
    Luz() {}
    Luz(vec3 _pos, vec3 _color) {
        pos = _pos;
        color = _color;
    }
    vec3 pos;
    vec3 color;
};


#endif //INC_20222_RAYTRACING_LUZ_H
