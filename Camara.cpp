//
// Created by hgallegos on 17/08/2022.
//

#include <string>
#include <iostream>
#include "Camara.h"
using namespace std;
void Camara::renderizar(vector<Objeto*> &objetos, vector<Luz*> &luces, string nombre, bool toggle) {

    pImg = new CImg<BYTE>(w, h, 1, 3);
    CImgDisplay dis_img((*pImg), "Imagen RayCasting en Perspectiva ");
    vec3 color;
    Rayo rayo;
    rayo.ori = eye;
    float t_tmp, t;
    Objeto *pObj;
    vec3 normal, N, L;
    bool hay_interseccion;
    // Para cada pixel lanzar un rayo
    for (int x=0; x < w; x++){
        for (int y=0; y < h; y++){
            rayo.dir = -f*ze + a*(y/h -0.5)*ye + b*(x/w-0.5)*xe;
            rayo.dir.normalize();
            if (x == 512 and y==300){
                float tmp = 6;
                color = vec3(1,0,0);
            }
            color = calcularColor(rayo, objetos, luces, 1);

            (*pImg)(x,h-1-y,0) = (BYTE)(color.x * 255);
            (*pImg)(x,h-1-y,1) = (BYTE)(color.y * 255);
            (*pImg)(x,h-1-y,2) = (BYTE)(color.z * 255);
        }
        dis_img.render((*pImg));
         dis_img.paint();
    }


    //toggle_window_wait
    if(toggle){
        while (!dis_img.is_closed()) {
            dis_img.wait();
        }
    }else{
        while (!dis_img.is_closed()) {
            dis_img.close();
        }
    }



    //GUARDADO DE IMAGENES
    //--------------------
    int n = nombre.length();
    nombre = "C:\\Users\\Rodrigo\\Desktop\\Luciernagas\\images\\" + nombre;
    char char_array[n + 1];
    strcpy(char_array, nombre.c_str());
    pImg->save(char_array);
    //--------------------
}

vec3 Camara::calcularColor(Rayo rayo, vector<Objeto*> &objetos, vector<Luz*> &luces, int prof){
    vec3 colores(0,0,0);
    for(auto luz : luces){
        vec3 color(0,0,0);
        float t_tmp, t;
        Objeto *pObj;
        //Luz luz = *(luces[0]);
        vec3 normal, N, L;
        bool hay_interseccion;
        if ( prof > 7) {
            return color;
        }
        hay_interseccion = false;
        t = 100000;
        for(auto pObjeto : objetos){
            if (pObjeto->interseccion(rayo, t_tmp, normal)) {
                if (t_tmp < t) {
                    hay_interseccion = true;
                    t = t_tmp;
                    N = normal;
                    pObj = pObjeto;
                }
            }
        }
        if (hay_interseccion and pObj->luz != nullptr) {
            //color = pObj->getColor(rayo);
            color = pObj->color;

        } else if (hay_interseccion) {
            vec3 pi = rayo.ori + t * rayo.dir;
            //N = normal;
            L = luz->pos - pi;
            float longitud = L.modulo();
            L.normalize();

            // componente ambiente
            vec3 ambiente = vec3(0.1,0.1,0.1) * pObj->kd;
            vec3 difusa(0, 0, 0);
            vec3 especular(0,0,0);
            // calcular si hay sombra
            // lanzar rayo hacia la luz
            Rayo rayo_sombra;
            rayo_sombra.ori = pi + N*0.01;
            rayo_sombra.dir = L;
            bool sombra = false;
            vec3 v = -rayo.dir;
            v.normalize();

            for(auto pObjeto : objetos){
                if (pObjeto->luz == nullptr and pObjeto->interseccion(rayo_sombra, t_tmp, normal)) {
                    if (t_tmp <= longitud and pObjeto->sombra == true) {
                        sombra = true;
                        break;
                    }
                }
            }
            if (sombra){
                //color = pObj->color * (ambiente);
            } else {
                // componente difusa
                float factor_difuso = N.punto(L);
                if (factor_difuso > 0) {
                    difusa = luz->color * pObj->kd * factor_difuso;
                }
                // componente especular
                vec3 r = 2*(L.punto(N))*N - L;
                r.normalize();
                float factor_especular = r.punto(v);
                if (factor_especular > 0) {
                    especular = luz->color * pObj->ks * pow(factor_especular , pObj->n);
                }
            }

            float kr = pObj->ks;
            float kt = 0;
            bool outside = rayo.dir.punto(N) < 0;
            vec3 bias = 0.001 * N;
            vec3 color_reflexivo(0,0,0);
            vec3 color_refractivo(0,0,0);

            if(pObj->idr > 0) {
                fresnel(rayo.dir, N, pObj->idr, kr);
                if (kr < 1) {
                    kt = 1- kr;
                    Rayo rayo_refractivo;
                    rayo_refractivo.ori = outside ? pi - bias : pi + bias;
                    rayo_refractivo.dir = refract(rayo.dir, N, pObj->idr);
                    rayo_refractivo.dir.normalize();
                    color_refractivo = calcularColor(rayo_refractivo, objetos, luces, prof+1);
                }
            }
            if (kr > 0) {
                Rayo rayo_reflexivo;
                rayo_reflexivo.ori = outside ? pi + bias : pi - bias;
                rayo_reflexivo.dir = 2 * (v.punto(N)) * N - v;
                rayo_reflexivo.dir.normalize();
                color_reflexivo = calcularColor(rayo_reflexivo, objetos, luces, prof + 1);
            }
            color = pObj->color * (ambiente + difusa + especular);
            color = color + color_reflexivo* kr + color_refractivo*kt;
            //color.max_to_one()
        }
            colores.x += color.x;
            colores.y += color.y;
            colores.z += color.z;
    }
    colores.x/luces.size();
    colores.y/luces.size();
    colores.z/luces.size();
    colores.max_to_one();
    return colores;
}

vec3 Camara::refract(vec3 I, vec3 N, float ior)
{
    float cosi = clamp(-1, 1, I.punto(N));
    float etai = 1, etat = ior;
    vec3 n = N;
    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -N; }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? vec3(0,0,0) : eta * I + (eta * cosi - sqrtf(k)) * n;
}

void Camara::fresnel(vec3 I, vec3 N, float &ior, float &kr)
{
    float cosi = clamp(-1, 1, I.punto(N));
    float etai = 1, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        kr = 1;
    }
    else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
}