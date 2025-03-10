#include <stdio.h>
#include <stdbool.h>
#include "dia_en_la_uni.h"

//CONSTANTES

const char TRINEO='T';
const char NAVE_ESPACIAL ='N';
const char CAMION ='C';
const char ALFOMBRA ='A';

const char BOLAS_DE_NIEVE = 'B';
const char PIUM_PIUM = 'P';
const char KUCHAU = 'K';
const char GENIO = 'G';


//Pre: -
//Pos:Dar la bienvendia al juego.
void dar_bienvenida(){
    printf("Bienvenido al juego de personalidades de Disney\n");
    printf("Comenzemos con las preguntas:\n");
}
//Pre: -
//Pos:Devuelve true si transporte es diferente a las opciones mencionadas y false si no lo cumplen.
bool es_transporte_valido(char transporte){
    return ((transporte!=TRINEO) && (transporte!=NAVE_ESPACIAL) && (transporte!=CAMION) && (transporte!=ALFOMBRA));
}
//Pre:-
//Pos:Devuelve true si ataque es diferente a las opciones mencionadas y false si no lo cumple.
bool es_ataque_valido(char ataque){
    return (ataque!=BOLAS_DE_NIEVE && ataque!=PIUM_PIUM && ataque!=KUCHAU && ataque!=GENIO);
}
//Pre: -
//Post:Devuelve true si nota es negativo o nota es mayor a 10, sino retorna false.
bool es_nota_valida(int nota){
    return (nota> 10 || nota<1);
}
//Pre: -
//Pos:Devuelve true si la hora es negativa o mayor a 24, sino retorna false.
bool es_hora_valida(int hora){
    
    return(hora<0 || hora>24);
}
//Pre: -
//Pos:Devuelve true si los minutos son negativos o mayores a 59, sino retorna false.
bool es_minuto_valido(float minutos){
    
    return(minutos<0 || minutos>0.59);
}
//Pre: -
//Pos condiciones:Te devuelve la parte decimal del numero ingresado.
float horario_parte_decimal(float numero){
    
    int parte_entera = (int)numero;
    float parte_decimal = numero - (float)parte_entera; 
    return parte_decimal;
}
//Pre: -
//Pos: Te devuelve la parte entera de el numero ingresado.
int horario_parte_entera(float numero){

    int parte_entera = (int)numero;
    return parte_entera;
}

//Pre: -
//Pos:Pide el tranporte y lo guarda en ref_transporte.El dato ingresado es valido.
void preguntar_transporte(char* ref_transporte){
    
    printf("\n");
    printf("Estas saliendo de tu casa, y te enteras que hay paro de trenes, que otro transporte elegis? \n");
    printf("Sus opciones son las siguientes:Trineo(T), Nave espacial(N), Camion(C) y Alfombra(A) \n");
    scanf(" %c",ref_transporte);

    while (es_transporte_valido(*ref_transporte)){
        printf("Este personaje no existe,ingrese uno de los nombrados \n");
        printf("Sus opciones son las siguientes:Trineo(T), Nave espacial(N), Camion(C) y Alfombra(A) \n");
        scanf(" %c",ref_transporte);
    }
}

//Pre: -
//Pos:Pide el ataque y lo guarda en ref_ataque.El dato ingresado es valido. 
void preguntar_ataque(char* ref_ataque){
    
    printf("\n");
    printf("En medio del camino te encontras con una manifestacion, que medio utilizas para deshacerte de la manifestacion?\n");
    printf("Sus opciones son las siguientes: Bolas_de_nieve(B), Pium_pium(P), Kuchau(K), GENIO(G),\n");
    scanf(" %c",ref_ataque);

    while(es_ataque_valido(*ref_ataque)){
        printf("Este ataque no esta disponible\n");
        printf("Sus opciones son las siguientes: Bolas_de_nieve(B), Pium_pium(P), Kuchau(K), GENIO(G),\n");
        scanf(" %c",ref_ataque);
    }
}

//Pre: -
//Pos:Pide la hora y la guarda en ref_hora.El dato ingresado es valido. 
void preguntar_hora(float*ref_hora){
    
    printf("Lograste superar la manifestacion,A que hora conseguiste llegar a la universidad?\n");
    printf("Ingrese la hora:");
    scanf("%f",ref_hora);

    while(es_hora_valida(horario_parte_entera(*ref_hora)) || es_minuto_valido(horario_parte_decimal(*ref_hora))){
        printf("No es valido, ingrese nuevamente.\n");
        printf("La hora tiene que estar entre 1 y 24\n");
        printf("Los minutos tienen que estar entre 0 y 59\n");
        scanf("%f",ref_hora);
    }
}

//Pre:-
//Pos:Pide la nota y la guarda en ref_nota. El dato ingresado es valido.
void preguntar_nota(int* ref_nota){
    printf("Por fin llego la nota del parcial!, que nota lograste sacarte ?\n");
    printf("La respuesta puede estar enetre 1 y 10\n");
    scanf("%i",ref_nota);

    while(es_nota_valida(*ref_nota)){
        printf("No valido, la respuesta puede estar enetre 1 y 10\n");
        scanf("%i",ref_nota);
    }
}
//Pre:El valor de la variable transporte tiene que ser igual a TRINEO, NAVE_ESPACIAL, CAMION O ALFOMBRA
//Pos:Determina el valor de puntos_transporte segun el transporte selccionado.
int puntaje_transporte(char transporte, int puntos_transporte){
   
    if (transporte==TRINEO || transporte==NAVE_ESPACIAL){
        puntos_transporte=10;
    }else{
        puntos_transporte=20;
    }
    return puntos_transporte;
}

//Pre:El valor de la varible ataque tiene que ser igual a BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO.
//Pos:Determina el valor de puntos_ataque segun el ataque seleccionado.
int puntaje_ataque(char ataque,int puntos_ataque){ 
    
    if (ataque==BOLAS_DE_NIEVE){
        puntos_ataque=3;
    }else if (ataque==PIUM_PIUM){
        puntos_ataque=6;
    }else if (ataque==KUCHAU){
        puntos_ataque=9;
    }else if (ataque==GENIO){
        puntos_ataque=12;
    }
    return puntos_ataque;
}

//Pre:El valor de la variable nota tiene que ser mayor igual a 1 y menor igual a 10.
//Pos:Determiana un puntaje segun la nota obtenida.
int nota_examen(int nota,int multiplicador){
    
    if (nota>=1 && nota<=3){
        multiplicador=1;
    }else if(nota>=4 && nota<=6){
        multiplicador=2;
    }else if(nota>=7 && nota<=8){
        multiplicador=3;
    }else if(nota>=9 && nota<=10){
        multiplicador=4;
    }
    return multiplicador;
}

//Pre:Las variables tienen que ser positivas.
//Pos:Calcula el puntaje total
int calculo_de_disney(int puntos_ataque,int puntos_transporte,int multiplicador){

    int puntaje= puntos_transporte + (puntos_ataque*multiplicador);
    return puntaje;
}

//Pre:El valor de la variable puntos_finales tiene que ser mayor igual a 13 y menor igual a 68.
//Pos:Guarda dos posibles personajes segun los puntos obtenidos.
void posibles_personajes(int puntos_finales,char* ref_personaje_1,char* ref_personaje_2){
    
    if(puntos_finales>=13 && puntos_finales<=41){   
        *ref_personaje_1= OLAF;
        *ref_personaje_2=STITCH;

    }else if(puntos_finales>=42 && puntos_finales<=68){
        *ref_personaje_1=JASMIN;
        *ref_personaje_2=RAYO_MCQUEEN;
    }
}

//Pre:El valor de las variables personaje_1 y personaje_2 tienen que ser igual a OLAF, STITCH, RAYO_MCQUEEN o JASMIN y 
//    el valor de la variable hora_de_llegada tiene que ser mayor igual a 00.00 y menor igual a 23.59.
//Pos:Segun la hora de llegada te determina el persoanje final.
char personaje_final(char personaje_1,char personaje_2,float hora_de_llegada){

    char personaje_final;
    if (personaje_1==OLAF && personaje_2==STITCH && hora_de_llegada<=15.30){
        personaje_final=STITCH;

    }else if (personaje_1==OLAF && personaje_2==STITCH && hora_de_llegada>15.30){
        personaje_final=OLAF;

    }else if (personaje_1==JASMIN && personaje_2==RAYO_MCQUEEN && hora_de_llegada<=15.30){
        personaje_final=JASMIN;

    }else{
        personaje_final=RAYO_MCQUEEN;
    }
    return personaje_final;
}

//Pre:El valor de las variable el personaje_final tiene que ser igual OLAF, STITCH, RAYO_MCQUEEN o JASMIN.
//Pos:Imprime por pantalla el personaje final.
void mostrar_personaje_final(char personaje_final){
    
    if (personaje_final==OLAF){
        printf("-Olaf-. \n");

    }else if (personaje_final==STITCH){
        printf("-Stitch-.\n");

    }else if (personaje_final==JASMIN){
        printf("-Jasmín-.\n");

    }else if(personaje_final==RAYO_MCQUEEN){
        printf("-Rayo McQueen-.\n");
    }
}

void asignar_personaje(char* ref_personaje_disney){
  
    char transporte;
    char ataque;
    int nota;
    float hora;
    
    preguntar_transporte(&transporte);
    preguntar_ataque(&ataque);
    preguntar_hora(&hora);
    preguntar_nota(&nota);
    
    int puntos_transporte=0;
    int puntos_ataque=0;
    int multiplicador=0;
    char posible_personaje_1='a';
    char posible_personaje_2='a';

    int resultado_puntaje_transporte = puntaje_transporte(transporte,puntos_transporte);
    int resultado_puntaje_ataque=puntaje_ataque(ataque,puntos_ataque); 
    int resultado_examen= nota_examen(nota,multiplicador);
    int calculo_personaje=calculo_de_disney(resultado_puntaje_ataque,resultado_puntaje_transporte,resultado_examen);

    posibles_personajes(calculo_personaje,&posible_personaje_1,&posible_personaje_2);
    char personaje_elegido=personaje_final(posible_personaje_1,posible_personaje_2,hora);

    mostrar_personaje_final(personaje_elegido);

    *ref_personaje_disney=personaje_elegido;
    }

