#include <stdio.h>
#include <stdbool.h>
#include "dia_en_la_uni.h"
#include "utiles.h"
#include "papeleo.h"
#include <stdlib.h> 
#include <time.h>



int main(){
    srand (( unsigned)time(NULL));
    dar_bienvenida();

    juego_t juego;
    char personaje_tp1=JASMIN;

    asignar_personaje(&personaje_tp1);

    inicializar_juego(&juego,personaje_tp1);
    imprimir_terreno(juego);    
    
    while(estado_juego(juego)!=-1 && 
          estado_nivel(juego.niveles[juego.nivel_actual-1].papeleos,juego.niveles[juego.nivel_actual-1].tope_papeleos)==0){
        realizar_jugada(&juego);
        imprimir_terreno(juego);
    }
    return 0;
}