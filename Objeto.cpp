//
// Created by hgallegos on 18/08/2022.
//

#include <cmath>
#include "Objeto.h"

using namespace std;

bool Esfera::interseccion(Rayo &rayo, float &t, vec3 &normal) {
    vec3 d = rayo.dir;
    vec3 o_c = rayo.ori - cen;
    float a = d.punto(d);
    float b = 2 * d.punto(o_c);
    float c = o_c.punto(o_c) - radio*radio;

    float det = b*b - 4*a*c;
    if ( det > 0) {
        float t1 = (-b - sqrt(det)) / (2*a);
        float t2 = (-b + sqrt(det)) / (2*a);
        t = std::fmin(t1, t2);
        if ( t <= 0 ) { return false;}
        vec3 pi = rayo.ori + t * rayo.dir;
        normal = pi - cen;
        normal.normalize();
        return true;
    }
    return false;
}

bool Plano::interseccion(Rayo &rayo, float &t, vec3 &normal_s) {
    /*t = -(normal.punto(rayo.ori) + d) / (normal.punto(rayo.dir));
    if (t > 0) {
        normal_s = normal;
        return true;
    }
    return false;*/
    float nd = normal.punto(rayo.dir);
    if (nd == 0) return false;
    t = (normal*d - rayo.ori).punto(normal) / nd;
    if (t < 0) return false;
    normal_s = nd > 0 ? -normal : normal;
    //normal_s = normal;
    return true;
}

vec3 Esfera::getColor(Rayo &rayo) {
    vec3 d = rayo.dir;
    vec3 o_c = rayo.ori - cen;
    float a = d.punto(d);
    float b = 2 * d.punto(o_c);
    float c = o_c.punto(o_c) - radio*radio;

    float det = b*b - 4*a*c;
    if ( det > 0) {
        float t1 = (-b - sqrt(det)) / (2*a);
        float t2 = (-b + sqrt(det)) / (2*a);
        vec3 p1 = rayo.ori + rayo.dir * t1;
        vec3 p2 = rayo.ori + rayo.dir * t2;
        float distancia = (p2-p1).modulo();
        float sigma_a = 0.1;
        //float transmision = exp(-distancia * sigma_a);
        return color * (1-distancia/radio);
    }
    return color;
}

bool Cilindro::interseccion(Rayo &rayo, float &t, vec3 &normal) {
    vec3 ro = rayo.ori;
    vec3 rd = rayo.dir;
    vec3 ca = pb-pa;
    vec3 oc = ro-pa;
    float caca = ca.punto(ca);
    float card = ca.punto(rd);
    float caoc = ca.punto(oc);
    float a = caca - card*card;
    float b = caca * oc.punto(rd) - caoc*card;
    float c = caca * oc.punto(oc) - caoc*caoc - ra*ra*caca;
    float h = b*b - a*c;
    if( h < 0.0 ) return false; //no intersection
    h = sqrt(h);
    t = (-b-h)/a;
    //if (t <= 0) return false;
    // body
    float y = caoc + t*card;
    if ( y > 0.0 && y < caca && t > 0) {
        normal = (oc + t*rd - ca*y/caca)/ra;
        normal.normalize();
        return true;
    }
    // caps
    t = (((y<0.0)?0.0:caca) - caoc)/card;
    if (t <= 0) return false;
    if( abs(b+a*t)<h ) {
        normal =  ca * sgn(y) / caca;
        normal.normalize();
        return true;
    }
    return false; //no intersection
}