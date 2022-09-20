//
// Created by hgallegos on 17/08/2022.
//

#ifndef INC_20222_RAYTRACING_CAMARA_H
#define INC_20222_RAYTRACING_CAMARA_H

#include <cmath>
#include <vector>
#include <string>
#include "vector.h"
#include "CImg.h"
#include "Objeto.h"
#include "Luz.h"
using namespace std;
using namespace cimg_library;
typedef unsigned char BYTE;

class Camara {
public:
    float fov, w, h, _near;
    vec3 eye, center, up;
    float f, a, b;
    vec3 xe, ye, ze;
    CImg<BYTE> *pImg;

    void crear(vec3 _center, vec3 _up, vec3 _eye, float _near_, float _fov, float _w, float _h) {
        center = _center;
        up = _up;
        eye = _eye;
        _near = _near_;
        fov = _fov;
        w = _w;
        h = _h;
    }

    void inicializar() {
        f = _near;
        a = 2 * f * tan(fov*M_PI/180/2);
        b = w / h * a;
        ze = eye-center;
        ze.normalize();
        xe = up.cruz(ze);
        xe.normalize();
        ye = ze.cruz(xe);
    }
    void renderizar() ;
    void renderizar(vector<Objeto*> &objetos, vector<Luz*> &luces, string nombre, bool toggle);

    vec3 calcularColor(Rayo rayo, vector<Objeto*> &objetos, vector<Luz*> &luces, int prof);
    vec3 refract(vec3 I, vec3 N, float ior);
    void fresnel(vec3 I, vec3 N, float &ior, float &kr);
};


#endif //INC_20222_RAYTRACING_CAMARA_H
