//
// Created by hgallegos on 24/08/2022.
//

#include "Mundo.h"
#include <iostream>
#include <string>
using namespace std;
void Mundo::Fireflies(){

    srand(time(0));

    //CREACION DE CAMARA
    //------------------
    camara.crear(vec3(25,30,25), vec3(0,1,0), vec3(25,40,150), 4, 60, 600, 400);
    camara.inicializar();
    //------------------

    //CREACION DE LA JARRA
    //-------------------
    Cilindro *cil1 = new Cilindro(vec3(25,1,25),vec3(25,50,25),20);
    cil1->set(vec3(0.1,1,1), 0, 0.9, 8, 1.5);
    //IMPORTANTE
    /*
     Creamos un parametro que indica si el objeto debe generar sombra
     (no aplica, por ejemplo, para luz desde el interior de un objeto transparente)
     */
    cil1->sombra = false;

    objetos.emplace_back(cil1);

    Cilindro *cil2 = new Cilindro(vec3(25,3,25),vec3(25,50,25),15);
    cil2->set(vec3(0.1,1,1), 0, 0.9, 8, 1.5);
    cil2->sombra = false;
    objetos.emplace_back(cil2);

    Cilindro *cil3 = new Cilindro(vec3(25,50,25),vec3(25,55,25),20);
    cil3->set(vec3(0.1,1,1), 0, 0.9, 8, 1.5);
    cil3->sombra = false;
    objetos.emplace_back(cil3);

    Esfera *pEsf1 = new Esfera(vec3(25,57,25), 4);
    pEsf1->set(vec3(0.1,1,1), 0, 0.9, 8, 1.5);
    pEsf1->sombra = false;
    objetos.emplace_back(pEsf1);
    //------------------



    //CREACION ESFERAS DECORACION
    //---------------------------
    Esfera *pEsf2 = new Esfera(vec3(0,10,60), 15);
    pEsf2->color = vec3(1,0.1,0.5);
    pEsf2->kd = 1;
    objetos.emplace_back(pEsf2);

    Esfera *pEsf3 = new Esfera(vec3(10,50,-40), 25);
    pEsf3->color = vec3(0.5,0.1,0.5);
    pEsf3->kd = 1;
    objetos.emplace_back(pEsf3);
    //---------------------------


    //CREACION PISO
    //-------------
    Plano *pPlano = new Plano(vec3(0,1,0),2);
    pPlano->color=vec3(0.1,0.1,0.1);
    pPlano->kd = 1;
    objetos.emplace_back(pPlano);
    //-------------

    //CREACION PARED
    //--------------
    Plano *pPlano2 = new Plano(vec3(1,0,0),-10);
    pPlano2->set(vec3(0,1,1), 1);
    objetos.emplace_back(pPlano2);
    //--------------


    //PARAMETROS CUSTOM PARA LA ANIMACION
    //-----------------------------------
    int segundos = 30; //segundos totales
    //int iter = segundos*24; //cantidad de renders, cambiar a iter=1 y toggle_window_wait para renderizar 1 frame y verlo
    int iter = 1;
    // pos_final = (75,70,100) pos_inicial = (25,40,150) => movement = p_i - p_f = (50,30,-50)
    float sum_camara_x = 50.0/iter; //calcula movimiento de la camara en cada frame hacia la pos final
    float sum_camara_y = 30.0/iter;
    float sum_camara_z = -50.0/iter;
    float firefly_movement_speed = 0.2; //cantidad de movimiento de la luciernaga en cada frame (aleatorio en cualquier eje)
    bool toggle_window_wait = true; // cambiar si el programa espera a que cada ventana sea cerrada manualmente (testing)
                                     // o si las cierra automaticamente despues de terminar de renderizar el frame
    int min_x = 14; //rangos minimos y maximos para la las posiciones aleatorias iniciales de las luciernagas
    int max_x = 36;
    int min_y = 1;
    int max_y = 49;
    int min_z = 14;
    int max_z = 36;
    int range_x = max_x - min_x + 1;
    int range_y = max_y - min_y + 1;
    int range_z = max_z - min_z + 1;
     //-----------------------------------


    //LUCIERNAGA 1
    //------------
    //pos inicial random
    int x = rand() % range_x + min_x;
    int y = rand() % range_y + min_y;
    int z = rand() % range_z + min_z;

    Luz *luciernaga_1 = new Luz(vec3(x,y,z), vec3(1,1,0.22));
    luces.emplace_back(luciernaga_1);
    Esfera *pEsfLuciernaga_1 = new Esfera( luciernaga_1->pos, 2);
    pEsfLuciernaga_1->set(luciernaga_1->color, 0);
    pEsfLuciernaga_1->luz = luciernaga_1;
    objetos.emplace_back( pEsfLuciernaga_1 );
    //------------

    //LUCIERNAGA 2
    //------------
    //pos inicial random
    x = rand() % range_x + min_x;
    y = rand() % range_y + min_y;
    z = rand() % range_z + min_z;

    Luz *luciernaga_2 = new Luz(vec3(x,y,z), vec3(1,1,0.22));
    luces.emplace_back(luciernaga_2);
    Esfera *pEsfLuciernaga_2 = new Esfera( luciernaga_2->pos, 2);
    pEsfLuciernaga_2->set(luciernaga_2->color, 0);
    pEsfLuciernaga_2->luz = luciernaga_2;
    objetos.emplace_back( pEsfLuciernaga_2 );
    //------------


    //LUCIERNAGA 3
    //------------
    //pos inicial random
    x = rand() % range_x + min_x;
    y = rand() % range_y + min_y;
    z = rand() % range_z + min_z;

    Luz *luciernaga_3 = new Luz(vec3(x,y,z),vec3(1,1,0.22));
    luces.emplace_back(luciernaga_3);
    Esfera *pEsfLuciernaga_3 = new Esfera( luciernaga_3->pos, 2);
    pEsfLuciernaga_3->set(luciernaga_3->color, 0);
    pEsfLuciernaga_3->luz = luciernaga_3;
    objetos.emplace_back( pEsfLuciernaga_3 );
    //------------


    //VARIABLES QUE ALMACENAN EL MOVIMIENTO DE LAS LUCIERNAGAS EN CADA EJE
    //--------------------------------------------------------------------
    float xx,yy,zz;
    //--------------------------------------------------------------------


    //GENERACION DE FRAMES
    //--------------------
    for(int i=0; i<iter; i++){

        //imprime porcentaje de avance (para saber cuanto falta)
        cout << ((float)i/(float)iter) * 100.0 << "%" << endl;


        //se actualiza la pos de la camara
        camara.eye.x += sum_camara_x;
        camara.eye.y += sum_camara_y;
        camara.eye.z += sum_camara_z;
        camara.inicializar();


        //LUCIERNAGA 1
        //------------
        auto v1 = pEsfLuciernaga_1->luz->pos; //pos actual de la luciernaga
        int range_option = 3 - 1 + 1; //rango que determina en que eje se movera
        int op,op2; //op sera numero random en el rango range_option que determina en que eje se movera
                    //op2 es num random que determina si el movimiento sera positivo o negativo
        int sign; //aqui se almacenara el signo del movimiento

        do{
            op = (rand() % (range_option) + 1); //calculo en que eje se movera
            op2 = (rand() % (1-0+1) + 1); //calculo si el movimiento es +-

            if(op2 == 1){ //elijo el signo dependiendo de op2
                sign = -1;
            }else{
                sign = 1;
            }

            if(op == 1){ //asigno cantidad de movimiento dependiendo de que eje toco y que signo
                xx = firefly_movement_speed*sign;
                yy = 0;
                zz = 0;
            }else if (op == 2){
                xx = 0;
                yy = firefly_movement_speed*sign;
                zz = 0;
            }else{
                xx = 0;
                zz = firefly_movement_speed*sign;
                yy = 0;
            }

            //verifico que el resultado obtenido sea admisible dentro de los rangos de los cilindros
        }while ( (v1.x + xx < 14 || v1.x+xx > 36) || (v1.z+zz < 14 || v1.z+zz > 36) || (v1.y+yy < 1 || v1.y+yy > 49) );

        //actualizo la pos de la luz
        pEsfLuciernaga_1->luz->pos = vec3(v1.x+xx,v1.y+yy,v1.z+zz);
        //actualizo la pos de la luciernaga
        pEsfLuciernaga_1->cen =  pEsfLuciernaga_1->luz->pos;
        //FIN LUCIERNAGA 1
        //------------

        //LUCIERNAGA 2
        //------------
        auto v2 = pEsfLuciernaga_2->luz->pos;
        do{
            op = (rand() % range_option + 1);
            op2 = (rand() % (1-0+1) + 1);
            if(op2 == 1){
                sign = -1;
            }else{
                sign = 1;
            }
            if(op == 1){

                xx = firefly_movement_speed*sign;
                yy = 0;
                zz = 0;
            }else if (op == 2){
                xx = 0;
                yy = firefly_movement_speed*sign;
                zz = 0;
            }else{
                xx = 0;
                zz = firefly_movement_speed*sign;
                yy = 0;
            }


        }while ( (v2.x + xx < 14 || v2.x+xx > 36) || (v2.z+zz < 14 || v2.z+zz > 36) || (v2.y+yy < 1 || v2.y+yy > 49) );

        pEsfLuciernaga_2->luz->pos = vec3(v2.x+xx,v2.y+yy,v2.z+zz);
        pEsfLuciernaga_2->cen =  pEsfLuciernaga_2->luz->pos;
        //FIN LUCIERNAGA 2
        //------------


        //LUCIERNAGA 3
        //------------
        auto v3 = pEsfLuciernaga_3->luz->pos;
        do{
            op = (rand() % range_option + 1);
            op2 = (rand() % (1-0+1) + 1);
            if(op2 == 1){
                sign = -1;
            }else{
                sign = 1;
            }
            if(op == 1){

                xx = firefly_movement_speed*sign;
                yy = 0;
                zz = 0;
            }else if (op == 2){
                xx = 0;
                yy = firefly_movement_speed*sign;
                zz = 0;
            }else{
                xx = 0;
                zz = firefly_movement_speed*sign;
                yy = 0;
            }


        }while ( (v3.x + xx < 14 || v3.x+xx > 36) || (v3.z+zz < 14 || v3.z+zz > 36) || (v3.y+yy < 1 || v3.y+yy > 49) );

        pEsfLuciernaga_3->luz->pos = vec3(v3.x+xx,v3.y+yy,v3.z+zz);
        pEsfLuciernaga_3->cen =  pEsfLuciernaga_3->luz->pos;

        //FIN LUCIERNAGA 3
        //------------


        //creo nombre del nuevo archivo a guardar
        string nombre = "f" + to_string(i);

        // mando renderizar, incluyo nombre y toggle_window_wait
        camara.renderizar(objetos, luces, nombre +".bmp", toggle_window_wait);
    }
    //--------------------


}