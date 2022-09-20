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
    float nd = normal.punto(rayo.dir);
    if (nd == 0) return false;
    t = (normal*d - rayo.ori).punto(normal) / nd;
    if (t < 0) return false;
    normal_s = nd > 0 ? -normal : normal;
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
        return color * (1-distancia/radio);
    }
    return color;
}


bool Cubo::interseccion(Rayo &rayo, float &t, vec3 &normal) {
    float tmin, tmax, tymin, tymax, tzmin, tzmax; 
    vec3 bounds[2];
    bounds[0] = b0;
    bounds[1] = b1; 
    vec3 invdir;
    invdir.x = 1/rayo.dir.x;
    invdir.y = 1/rayo.dir.y;
    invdir.z = 1/rayo.dir.z;
    int sign[3];
    sign[0] = (invdir.x < 0); 
    sign[1] = (invdir.y < 0); 
    sign[2] = (invdir.z < 0); 

    tmin = (bounds[sign[0]].x - rayo.ori.x) * invdir.x; 
    tmax = (bounds[1-sign[0]].x - rayo.ori.x) * invdir.x; 
    tymin = (bounds[sign[1]].y - rayo.ori.y) * invdir.y; 
    tymax = (bounds[1-sign[1]].y - rayo.ori.y) * invdir.y;

    if ((tmin > tymax) || (tymin > tmax)) 
            return false;

    if (tymin > tmin) 
        tmin = tymin; 
    if (tymax < tmax) 
        tmax = tymax; 
    
    tzmin = (bounds[sign[2]].z - rayo.ori.z) * invdir.z; 
    tzmax = (bounds[1-sign[2]].z - rayo.ori.z) * invdir.z; 

    if ((tmin > tzmax) || (tzmin > tmax)) 
            return false; 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
    if (tzmax < tmax) 
        tmax = tzmax; 
 
    t = tmin; 
 
    if (t < 0) { 
        t = tmax; 
        if (t < 0) return false; 
    } 
 
    return true; 
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