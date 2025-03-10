#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <time.h>
#include "dia_en_la_uni.h"
#include "papeleo.h"
#include "utiles.h"


#define MAX_FILAS_NIVEL_1 22
#define MAX_COLUMNAS_NIVEL_1 22
#define MAX_FILAS_NIVEL_2 17
#define MAX_COLUMNAS_NIVEL_2 17
#define MAX_FILAS_NIVEL_3 12
#define MAX_COLUMNAS_NIVEL_3 12

#define MAX_OBJETOS 100


const int PRIMER_NIVEL= 1;
const int SEGUNDO_NIVEL= 2;
const int TERCER_NIVEL= 3;

const int LIMITE_COL_NIVEL_1=22;
const int LIMITE_FIL_NIVEL_1=22;
const int LIMITE_COL_NIVEL_2=17;
const int LIMITE_FIL_NIVEL_2=17;
const int LIMITE_COL_NIVEL_3=12;
const int LIMITE_FIL_NIVEL_3=12;

const char FUEGOS = 'F';
const char MEDIAS = 'M';
const char BOTELLA_DE_GRITOS = 'G';
const char INTERRUPTORES = 'I';
const char MIKE = 'W';

const int CANT_FUEGOS_NIVEL_1 = 10;
const int CANT_FUEGOS_NIVEL_2 = 5;
const int CANT_FUEGOS_NIVEL_3 = 3;

const int CANT_MEDIAS_NIVEL_1 = 5;
const int CANT_MEDIAS_NIVEL_2 = 4;
const int CANT_MEDIAS_NIVEL_3 = 3;

const int CANT_BOTELLAS_DE_GRITO_NIVEL_1 = 4;
const int CANT_BOTELLAS_DE_GRITO_NIVEL_2 = 3;
const int CANT_BOTELLAS_DE_GRITO_NIVEL_3 = 2;

const int MOVIMIENTOS_NIVEL_1=40;
const int MOVIMIENTOS_NIVEL_2=30;
const int MOVIMIENTOS_NIVEL_3=20;

const int CANT_MARTILLOS_NIVEL_1=4;
const int CANT_MARTILLOS_NIVEL_2=5;
const int CANT_MARTILLOS_NIVEL_3=6;

const int CANT_EXTINTORES_NIVEL_1=4;
const int CANT_EXTINTORES_NIVEL_2=2;
const int CANT_EXTINTORES_NIVEL_3=2;

const int CANT_PAPELEOS_NIVEL_1=2;
const int CANT_PAPELEOS_NIVEL_2=3;
const int CANT_PAPELEOS_NIVEL_3=4;

const int OBSEQUIO_RAYO=10;
const int OBSEQUIO_OLAF_NIVEL_1=2;
const int OBSEQUIO_OLAF_NIVEL_2=1;
const int OBSEQUIO_STITCH=1;

const int AHUYENTA_RANDALL_NIVEL_1=1;
const int AHUYENTA_RANDALL_NIVEL_2=1;
const int AHUYENTA_RANDALL_NIVEL_3=0;

const char MOV_ROTACIONAL_HORARIO = 'E';
const char MOV_ROTACIONAL_ANTIHORARIO = 'Q';
const char MOV_DERECHA = 'D';
const char MOV_IZQUIERDA = 'A';
const char MOV_ARRIBA = 'W';
const char MOV_ABAJO = 'S';

const char MARTILLO = 'Z';
const char EXTINTOR = 'C';

const int NO_EXISTE=-1;

const int POSICION_AUMENTADA=1;
const int POSICION_DISMINUIDA=-1;

const int MOVIMIENTOS_RESTADOS=10;
const int MOVIMIENTOS_SUMADOS=7;

const int NUEVAS_PAREDES_NIVEL_1=40;
const int NUEVAS_PAREDES_NIVEL_2=30;
const int NUEVAS_PAREDES_NIVEL_3=20;

const int DIVISOR_NIVEL_1=7;
const int DIVISOR_NIVEL_2=5;
const int DIVISOR_NIVEL_3=3;

const int GANADO=1;
const int JUGANDO=0;
const int PERDIDO=-1;

/*
*Pre:El nivel tiene que ser 1,2 o 3.
*Pos:Genera una coordenada random segun el nivel elegido.
*/
void generar_coordenada_random(coordenada_t* posicion,int nivel){
    
    if(nivel==PRIMER_NIVEL){
        posicion->col=rand () % LIMITE_COL_NIVEL_1;
        posicion->fil=rand () % LIMITE_FIL_NIVEL_1;

    }else if(nivel==SEGUNDO_NIVEL){
        posicion->col=rand () % LIMITE_COL_NIVEL_2;
        posicion->fil=rand () % LIMITE_FIL_NIVEL_2;

    }else if(nivel==TERCER_NIVEL){
        posicion->col=rand () % LIMITE_COL_NIVEL_3;
        posicion->fil=rand () % LIMITE_FIL_NIVEL_3;
    }
}     
/*
*Pre:
*Pos:Calcula la distacia que hay entre dos puntos.
*/
int distancia_manhattan(coordenada_t objeto, coordenada_t pared){
    return abs(objeto.fil-pared.fil)+ abs(objeto.col-pared.col);
}
/*
*Pre:
*Pos:Te devuelve true en el caso de que un fuego sea adyacente a una pared.
*/
bool esta_adyacente_a_pared(coordenada_t objeto, coordenada_t pared){
    return distancia_manhattan(objeto,pared)==1;
}
/*
*Pre:
*Pos: Te retorna true si la coordenada ingresada esta no se superpone con el posicion inicial del jugador, la de las paredes,
la de los obtauclos y si la coordenada ingresada es adyacente a las paredes, sino retorna false.
*/
bool esta_coordenada_fuegos_disponible(coordenada_t objeto,nivel_t nivel){
    bool posicion_valida=true;
    bool es_fuego_adyacente_a_una_pared=false;
    bool fuego_esta_sobre_una_pared=false;

    if(objeto.col== nivel.pos_inicial_jugador.col && objeto.fil== nivel.pos_inicial_jugador.fil){
        posicion_valida=false;
    }

    int cont_paredes=0;
    while(cont_paredes<nivel.tope_paredes && fuego_esta_sobre_una_pared==false){
        if(objeto.col==nivel.paredes[cont_paredes].col && objeto.fil==nivel.paredes[cont_paredes].fil){
            fuego_esta_sobre_una_pared=true;
        }
        if(esta_adyacente_a_pared(objeto,nivel.paredes[cont_paredes])==true){
            es_fuego_adyacente_a_una_pared=true;
        }     
        cont_paredes++;
    }
    posicion_valida= (fuego_esta_sobre_una_pared==false) && (es_fuego_adyacente_a_una_pared==true);

    int cont_obstaculos=0;
    while(cont_obstaculos<nivel.tope_obstaculos && posicion_valida==true){
        if (objeto.col==nivel.obstaculos[cont_obstaculos].posicion.col && 
            objeto.fil==nivel.obstaculos[cont_obstaculos].posicion.fil){
            posicion_valida=false;
        }
        cont_obstaculos++;
    }
    return posicion_valida;   
}
/*
Pre:El nivel tiene que ser 1,2 o 3.
Pos:Genera una coordenada_t que no se superpoga con los elementos previamente cargados y que sea adyacente a las paredes.
*/
void generar_posicion_valida_fuegos(int numero_nivel,coordenada_t* posicion,nivel_t nivel){
    
    generar_coordenada_random(posicion,numero_nivel); 
    bool superposicion=true;
    while(superposicion==true){

        if (esta_coordenada_fuegos_disponible(*posicion,nivel)==false){
            
            generar_coordenada_random(posicion,numero_nivel);
            superposicion=true;
        
        }else if(esta_coordenada_fuegos_disponible(*posicion,nivel)==true){
            superposicion=false;
        }        
    }
}
/*
*Pre:
*Pos: Te retorna true si la coordenada ingresada esta no se superpone con ningun otro elemento, sino retorna false.
*/
bool esta_coordenada_disponible(coordenada_t objeto,nivel_t nivel){
    bool posicion_valida=true;
    if(objeto.col== nivel.pos_inicial_jugador.col && objeto.fil== nivel.pos_inicial_jugador.fil){
        posicion_valida=false;
    }
    int cont_paredes=0;
    while(cont_paredes<nivel.tope_paredes && posicion_valida==true){
        if (objeto.col==nivel.paredes[cont_paredes].col && objeto.fil==nivel.paredes[cont_paredes].fil){
            posicion_valida=false; 
        } 
        cont_paredes++;
    }
    int cont_obstaculos=0;
    while(cont_obstaculos<nivel.tope_obstaculos && posicion_valida==true){
        if (objeto.col==nivel.obstaculos[cont_obstaculos].posicion.col && 
            objeto.fil==nivel.obstaculos[cont_obstaculos].posicion.fil){
            posicion_valida=false;
        }
        cont_obstaculos++;

    }
    int cont_herramientas=0;
    while(cont_herramientas<nivel.tope_herramientas && posicion_valida==true){
        if (objeto.col==nivel.herramientas[cont_herramientas].posicion.col && 
            objeto.fil==nivel.herramientas[cont_herramientas].posicion.fil){
            posicion_valida=false;
        }
        cont_herramientas++;
    }
    int cont_papeleos=0;
    while(cont_papeleos<nivel.tope_papeleos && posicion_valida==true){
        if (objeto.col==nivel.papeleos[cont_papeleos].posicion.col && 
            objeto.fil==nivel.papeleos[cont_papeleos].posicion.fil){
            posicion_valida=false;
        }
        cont_papeleos++;
    }
    return posicion_valida;
}
/*
Pre:El nivel tiene que ser 1,2 o 3.
Pos:Genera una coordenada_t que no se superpoga con los elementos previamente cargados.
*/
void generar_posicion_valida(int numero_nivel,coordenada_t* posicion,nivel_t nivel){
    
    generar_coordenada_random(posicion,numero_nivel); 
    bool superposicion=true;
    while(superposicion==true){

        if (esta_coordenada_disponible(*posicion,nivel)==false){
            
            generar_coordenada_random(posicion,numero_nivel);
            superposicion=true;
        
        }else if(esta_coordenada_disponible(*posicion,nivel)==true){
            superposicion=false;
        }        
    }
}
/*
*Pre: La cantidad  cantidad_medias + cantidad_fuegos no puede exceder el maximo del vector de  
      obstaculos.
*Pos: Segun la cantidad de catidad_fuego y cantidad_medias devuelvo el vector
      objeto_t obstaculos cargado junto con su tope.
*/   
void agregar_obstaculos(int numero_nivel,nivel_t* nivel,int cantidad_fuegos,int cantidad_medias){
        
    coordenada_t posicion_generada;

    for(int i=0;i<cantidad_fuegos;i++){
        
        generar_posicion_valida_fuegos(numero_nivel,&posicion_generada,*nivel);
        nivel->obstaculos[(nivel->tope_obstaculos)].posicion=posicion_generada;
        nivel->obstaculos[(nivel->tope_obstaculos)].tipo=FUEGOS;
        nivel->tope_obstaculos++;
    }

    for(int i=0; i<cantidad_medias;i++){
        generar_posicion_valida(numero_nivel,&posicion_generada,*nivel);
        nivel->obstaculos[(nivel->tope_obstaculos)].posicion=posicion_generada;
        nivel->obstaculos[(nivel->tope_obstaculos)].tipo=MEDIAS;
        nivel->tope_obstaculos++;
    }
}
/*
*Pre: El número_nivel tiene que ser 1,2 o 3 y es personaje tiene que ser Stitch,Rayo_McQueen,Olaf
      o Jasmín.
*Pos: Segun el nivel y el personaje_tp1 carga toda la información de los obstaculos.   
*/
void obtener_obstaculos(nivel_t* nivel,int numero_nivel,char personaje_tp1){
    int cantidad_fuegos=0;
    int cantidad_medias=0;

    if(numero_nivel==PRIMER_NIVEL){
        if(personaje_tp1==OLAF){
            
            cantidad_fuegos=CANT_FUEGOS_NIVEL_1-OBSEQUIO_OLAF_NIVEL_1;
        }else{
            cantidad_fuegos=CANT_FUEGOS_NIVEL_1;   
        } 
        cantidad_medias=CANT_MEDIAS_NIVEL_1;

    }else if(numero_nivel==SEGUNDO_NIVEL){
        
        if(personaje_tp1==OLAF){
            cantidad_fuegos=CANT_FUEGOS_NIVEL_2-OBSEQUIO_OLAF_NIVEL_2; 
        }else{
            cantidad_fuegos=CANT_FUEGOS_NIVEL_2;
        }
        cantidad_medias=CANT_MEDIAS_NIVEL_2;
        
    }else if(numero_nivel==TERCER_NIVEL){
       cantidad_fuegos=CANT_FUEGOS_NIVEL_3;
       cantidad_medias=CANT_MEDIAS_NIVEL_3; 
    }
    agregar_obstaculos(numero_nivel,nivel,cantidad_fuegos,cantidad_medias);
}
/*
*Pre: La cantidad de catidad_botellas_de_grito + cantidad_extintores no puede exceder el maximo del 
      vector de herramientas.
*Pos: Segun la cantidad de catidad_botellas_de_grito y cantidad_extintores
      devuelvo el vector objeto_t herramientas cargado junto con su tope.
*/
void agregar_herramientas(int numero_nivel,nivel_t* nivel,int cantidad_botellas_de_grito,int cantidad_interruptores){
    
    coordenada_t posicion_generada;

    for (int i = 0; i <cantidad_botellas_de_grito; i++){ 
        
        generar_posicion_valida(numero_nivel,&posicion_generada,*nivel);
        nivel->herramientas[nivel->tope_herramientas].posicion=posicion_generada;
        nivel->herramientas[nivel->tope_herramientas].tipo=BOTELLA_DE_GRITOS;
        nivel->tope_herramientas++;
    }
    for (int i=0; i<(cantidad_interruptores);i++){

        generar_posicion_valida(numero_nivel,&posicion_generada,*nivel);
        nivel->herramientas[nivel->tope_herramientas].posicion=posicion_generada;
        nivel->herramientas[nivel->tope_herramientas].tipo=INTERRUPTORES;
        nivel->tope_herramientas++;
    } 
}
/*
*Pre: El número_nivel tiene que ser 1,2 o 3 y es personaje tiene que ser Stitch,Rayo_McQueen,Olaf
      o Jasmín.
*Pos: Segun el nivel y el personaje_tp1 carga toda la información de las herramientas con coordenada.   
*/
void obtener_herramientas(nivel_t* nivel,int numero_nivel){
    int cantidad_botellas_de_grito=0;
    int cantidad_interruptores=0;
    
    if(numero_nivel==PRIMER_NIVEL){
        cantidad_botellas_de_grito=CANT_BOTELLAS_DE_GRITO_NIVEL_1;
        cantidad_interruptores=AHUYENTA_RANDALL_NIVEL_1; 

    }else if(numero_nivel==SEGUNDO_NIVEL){
       cantidad_botellas_de_grito=CANT_BOTELLAS_DE_GRITO_NIVEL_2;
       cantidad_interruptores=AHUYENTA_RANDALL_NIVEL_2; 

    }else if(numero_nivel==TERCER_NIVEL){
        cantidad_botellas_de_grito=CANT_BOTELLAS_DE_GRITO_NIVEL_3;
        cantidad_interruptores=AHUYENTA_RANDALL_NIVEL_3; 
    }
    agregar_herramientas(numero_nivel,nivel,cantidad_botellas_de_grito,cantidad_interruptores);

}
/*
*Pre: La cantidad de cantidad_papeleos n puede exceder el maximo de del vector de papeleos.
*Pos: Segun la cantidad de catidad_papeleos devuelvo el vector papeleo_t cargado junto con su tope.
*/
void agregar_papeleos(int numero_nivel, nivel_t* nivel,int cantidad_papeleos){
    coordenada_t posicion_generada;

    for(int i = 0; i <cantidad_papeleos; i++){ 
    
        generar_posicion_valida(numero_nivel,&posicion_generada,*nivel);
        nivel->papeleos[nivel->tope_papeleos].posicion=posicion_generada;
        nivel->papeleos[nivel->tope_papeleos].id_papeleo=i;
        nivel->papeleos[nivel->tope_papeleos].recolectado=false;
        nivel->tope_papeleos++;
    }
}
/*
*Pre: El número_nivel tiene que ser 1,2 o 3 y es personaje tiene que ser Stitch,Rayo_McQueen,Olaf
*     o Jasmín.
*Pos: Segun el nivel y el personaje_tp1 carga toda la información de los papeleos.
*/
void obtener_papeleo(nivel_t* nivel,int numero_nivel,char personaje_tp1){
    int cantidad_papeleos=0;
    if(numero_nivel==PRIMER_NIVEL){
        cantidad_papeleos=CANT_PAPELEOS_NIVEL_1;
    
    }else if(numero_nivel==SEGUNDO_NIVEL){
        cantidad_papeleos=CANT_PAPELEOS_NIVEL_2;

    }else if(numero_nivel==TERCER_NIVEL){
        if(personaje_tp1==STITCH){
            cantidad_papeleos=CANT_PAPELEOS_NIVEL_3-OBSEQUIO_STITCH;
        }else{
            cantidad_papeleos=CANT_PAPELEOS_NIVEL_3;
        }
    }
    agregar_papeleos(numero_nivel,nivel,cantidad_papeleos);
}
/*
*Pre: El número_nivel tiene que ser 1,2 o 3 y es personaje tiene que ser Stitch,Rayo_McQueen,Olaf
      o Jasmín.
*Pos: Cargo toda la información de del personaje segun su nivel.   
*/
void inicializar_personaje(jugador_t *jugador,int numero_nivel, char personaje_tp1,
                          coordenada_t pos_inicial_jugador){

    if (numero_nivel==PRIMER_NIVEL){
        
        jugador->movimientos=MOVIMIENTOS_NIVEL_1;
        jugador->martillos=CANT_MARTILLOS_NIVEL_1;
        jugador->extintores=CANT_EXTINTORES_NIVEL_1;
        jugador->ahuyenta_randall=false;
        
        if (personaje_tp1==JASMIN){
            (jugador->martillos)++;
        }else if(personaje_tp1==RAYO_MCQUEEN){
            jugador->movimientos=jugador->movimientos + OBSEQUIO_RAYO;  
        }
    }else if(numero_nivel==SEGUNDO_NIVEL){

        jugador->movimientos=MOVIMIENTOS_NIVEL_2;
        jugador->martillos=CANT_MARTILLOS_NIVEL_2;
        jugador->extintores=CANT_EXTINTORES_NIVEL_2;
        jugador->ahuyenta_randall=false;

    }else if(numero_nivel==TERCER_NIVEL){
                
        jugador->movimientos=MOVIMIENTOS_NIVEL_3;
        jugador->martillos=CANT_MARTILLOS_NIVEL_3;
        jugador->extintores=CANT_EXTINTORES_NIVEL_3;
        jugador->ahuyenta_randall=false;
    }
    jugador->posicion=pos_inicial_jugador;
}

/*
*Pre:
*Pos: Convierte un entero en un char.
*/
char convertir_entero(int numero){

    char numero_2= (char)(numero+49);
 return numero_2;
}
void asignar_dimensiones(int nivel_actual,int* cant_filas,int* cant_columnas){
    if(nivel_actual==PRIMER_NIVEL){
        *cant_filas=LIMITE_FIL_NIVEL_1;
        *cant_columnas=LIMITE_COL_NIVEL_1;
    }else if(nivel_actual==SEGUNDO_NIVEL){
        *cant_filas=LIMITE_FIL_NIVEL_2;
        *cant_columnas=LIMITE_COL_NIVEL_2;
    }else{
        *cant_filas=LIMITE_FIL_NIVEL_3;
        *cant_columnas=LIMITE_COL_NIVEL_3;  
    }
}
/*
*Pre:
*Pos:Genera una matriz vacia. 
*/
void inicializar_matriz(char matriz[MAX_FILAS_NIVEL_1][MAX_COLUMNAS_NIVEL_1],int cant_filas,int cant_columnas){

    for(int i=0;i<cant_filas;i++){
        for(int j=0;j<cant_columnas;j++){
            matriz[i][j]='-' ; 
        }
    }
}  
/*
*Pre:
*Pos:Muestra por pantalla una matriz con las dimensiones asignadas   
*/
void mostrar_matriz(char matriz[MAX_FILAS_NIVEL_1][MAX_COLUMNAS_NIVEL_1],int cant_filas,int cant_columnas){
    for(int i=0;i<cant_filas;i++){
         for(int j=0;j<cant_columnas;j++){
            printf("%c ",matriz[i][j]);
        }
        printf("\n");
    }
}
/*
*Pre:
*Pos:Carga en la matriz los elementos del vector coordenada_ paredes[MAX_PAREDES].   
*/
void cargar_paredes(int tope_paredes,coordenada_t paredes[MAX_PAREDES],char matriz[MAX_FILAS_NIVEL_1][MAX_COLUMNAS_NIVEL_1]){
    for(int i=0;i<tope_paredes;i++){
    matriz[paredes[i].fil][paredes[i].col]='#';
    }
}
/*
*Pre:
*Pos:Carga en la matriz la posición del jugador.
*/
void cargar_jugador(coordenada_t pos_jugador,char matriz[MAX_FILAS_NIVEL_1][MAX_COLUMNAS_NIVEL_1]){
    matriz[pos_jugador.fil][pos_jugador.col]='J';
}
/*
*Pre:
*Pos:Carga en la matriz la posición de los elementos del vector  objeto_t obstaculos[MAX_OBSTACULOS].
*/
void cargar_obstaculos(int tope_obstaculos,objeto_t obstaculos[MAX_OBSTACULOS],char matriz[MAX_FILAS_NIVEL_1][MAX_COLUMNAS_NIVEL_1]){
    for(int i=0;i<tope_obstaculos;i++){
    matriz[obstaculos[i].posicion.fil][obstaculos[i].posicion.col]=obstaculos[i].tipo;
    }
}
/*
*Pre:
*Pos:Carga en la matriz la posición de los elementos del vector  objeto_t herramientas[MAX_HERRAMIENTAS].
*/
void cargar_herramientas(int tope_herramientas,objeto_t herramientas [MAX_HERRAMIENTAS],char matriz[MAX_FILAS_NIVEL_1][MAX_COLUMNAS_NIVEL_1]){
    for(int i=0;i<tope_herramientas;i++){
        matriz[herramientas[i].posicion.fil][herramientas[i].posicion.col]=herramientas[i].tipo;
    }
}
/*
*Pre:
*Pos: Carga en la matriz la posición de los elementos del vector papeleo_t papeleos[MAX_PAPELEOS].  
*/
void cargar_papeleos(int tope_papeleos,papeleo_t papeleos[MAX_PAPELEOS],char matriz[MAX_FILAS_NIVEL_1][MAX_COLUMNAS_NIVEL_1]){
        for(int i=0;i<tope_papeleos;i++){ 
        matriz[papeleos[i].posicion.fil][papeleos[i].posicion.col]=convertir_entero(papeleos[i].id_papeleo);
    }
}


void inicializar_nivel(nivel_t* nivel, int numero_nivel, char personaje_tp1){

    nivel->tope_herramientas=0;
    nivel->tope_obstaculos=0;
    nivel->tope_papeleos=0;

    obtener_paredes(numero_nivel,nivel->paredes, &(nivel->tope_paredes),&(nivel->pos_inicial_jugador));
    obtener_obstaculos(nivel,numero_nivel,personaje_tp1);
    obtener_herramientas(nivel,numero_nivel);
    obtener_papeleo(nivel,numero_nivel,personaje_tp1);
}

void inicializar_juego(juego_t *juego, char personaje_tp1){
     
    for (int i = 1; i <= MAX_NIVELES; i++){

        nivel_t* nivel= &(juego->niveles[i-1]);
        inicializar_nivel(nivel,i, personaje_tp1);
    }  
    juego->personaje_tp1=personaje_tp1;
    juego->nivel_actual=PRIMER_NIVEL;
    jugador_t* jugador=&(juego->jugador);
    
    inicializar_personaje(jugador,juego->nivel_actual,personaje_tp1,
                          juego->niveles[(juego->nivel_actual)-1].pos_inicial_jugador);
}


/*
*Pre:-
*Pos:Muesta por pantalla las caracteristicas del jugador en el nivel actual.
*/
void mostrar_caracteristicas_jugador(jugador_t jugador){
    printf("Extintores: %i\n",jugador.extintores);
    printf("Martillos: %i\n",jugador.martillos);
    printf("Movimientos_restantes: %i\n",jugador.movimientos);
    printf("Movimientos_realizados: %i\n",jugador.movimientos_realizados);
    if(jugador.ahuyenta_randall==false){
        printf("Ahuyenta Randall: false\n\n");
    }else{
        printf("Ahuyenta Randall: true\n\n");
    }
}
/*
*Pre:-
*Pos: Muestra por pantalla si los papeleos del nivel actual ya fueron recolectados o no. 
*/
void mostrar_caracteristicas_papeleos(papeleo_t papeleos[MAX_PAPELEOS],int tope_papeleos){
    for(int i=0;i<tope_papeleos;i++){
        if(papeleos[i].recolectado==true){
            printf("El papeleo %i esta recolectado\n",i);
        }else{
            printf("El papeleo %i no esta recolectado\n",i);
        }
    }

}
/*
*Pre:-
*Pos: Muesta por pantalla la condición del usuario al finalizar el juego. 
*/
void mostrar_fin_de_juego(juego_t juego){
    if(estado_juego(juego)==GANADO){
        printf("GANASTE!!\n");
    }else if(estado_juego(juego)==PERDIDO){
        printf("PERDISTE\n");
    }
}

void imprimir_terreno(juego_t juego){
    
    char matriz[MAX_FILAS_NIVEL_1][MAX_COLUMNAS_NIVEL_1];
    int filas=0;
    int columnas=0;

    mostrar_caracteristicas_jugador(juego.jugador);
    //mostrat_caracteristicas_objetos(juego.niveles[juego.nivel_actual-1]);
    mostrar_caracteristicas_papeleos(juego.niveles[juego.nivel_actual-1].papeleos,juego.niveles[juego.nivel_actual-1].tope_papeleos);

    asignar_dimensiones(juego.nivel_actual,&filas,&columnas);
    inicializar_matriz(matriz,filas,columnas);
    cargar_paredes(juego.niveles[juego.nivel_actual-1].tope_paredes,juego.niveles[juego.nivel_actual-1].paredes,matriz);
    cargar_obstaculos(juego.niveles[juego.nivel_actual-1].tope_obstaculos,juego.niveles[juego.nivel_actual-1].obstaculos,matriz);
    cargar_herramientas(juego.niveles[juego.nivel_actual-1].tope_herramientas,juego.niveles[juego.nivel_actual-1].herramientas,matriz);
    cargar_papeleos(juego.niveles[juego.nivel_actual-1].tope_papeleos,juego.niveles[juego.nivel_actual-1].papeleos,matriz);
    cargar_jugador(juego.jugador.posicion,matriz);
    mostrar_matriz(matriz,filas,columnas);

    mostrar_fin_de_juego(juego);  
}

/*
*Pre:-
*Pos:Devuelve true si un papeleo se encuntra recolectado, y sino false. 
*/
bool esta_recolectado(papeleo_t papeleo){
    return(papeleo.recolectado==true);
}
/*
*Pre:-
*Pos:Devuelve true si se encuentran todos los papeleos recolectados, sino false.
*/
bool estan_papeleos_recolectados(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
    bool estan_todos_recolectodos=true;
    for(int i=0;i<tope_papeleos;i++){
        if(!esta_recolectado(papeleos[i])){
            estan_todos_recolectodos=false;
        }
    }
    return(estan_todos_recolectodos);
}

int estado_nivel(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
    int estado_nivel=JUGANDO;
    if(estan_papeleos_recolectados(papeleos,tope_papeleos)==true){
        estado_nivel=GANADO;
    }
    return(estado_nivel);
}
int estado_juego(juego_t juego){
    int estado_juego=JUGANDO;
    if((juego.nivel_actual=TERCER_NIVEL) && estado_nivel(juego.niveles[TERCER_NIVEL-1].papeleos,juego.niveles[TERCER_NIVEL-1].tope_papeleos)==GANADO){
        estado_juego=GANADO;
    }else if(juego.jugador.movimientos<=0){
        estado_juego=PERDIDO;
    }else if(estado_nivel(juego.niveles[juego.nivel_actual-1].papeleos,juego.niveles[juego.nivel_actual-1].tope_papeleos)==JUGANDO){
        estado_juego=JUGANDO;
    }
    return(estado_juego);
}

/*
*Pre:
*Pos:Rota de forma horaria las paredes que pertenecen al vector de paredes.
*/
void rotar_paredes_horario(coordenada_t paredes[MAX_PAREDES],int tope,int cantidad_filas){
    int aux=0;
    for(int i=0;i< tope;i++){
        aux=paredes[i].fil;
        paredes[i].fil=paredes[i].col;
        paredes[i].col=abs(aux-(cantidad_filas-1));
    }
}
/*
*Pre:-
*Pos:Rota de forma horaria todos los objetos que pertenecen al vector de objetos.
*/
void rotar_objetos_horario(objeto_t objetos[MAX_OBJETOS],int tope,int cantidad_filas){
    int aux=0;
    for(int i=0;i< tope;i++){
        aux=objetos[i].posicion.fil;
        objetos[i].posicion.fil=objetos[i].posicion.col;
        objetos[i].posicion.col=abs(aux-(cantidad_filas-1));
    }
}
/*
*Pre:
*Pos:Rota de forma horaria todos los papeleos que pertenecen al vector de papeleos.
*/
void rotar_papeleos_horario(papeleo_t papeleos[MAX_PAPELEOS],int tope,int cantidad_filas){
    int aux=0;
    for(int i=0;i< tope;i++){
        aux=papeleos[i].posicion.fil;
        papeleos[i].posicion.fil=papeleos[i].posicion.col;
        papeleos[i].posicion.col=abs(aux-(cantidad_filas-1));
    }
}
/*
*Pre:
*Pos:Rota de forma horaria al jugador.
*/
void rotar_jugador_horario(coordenada_t* posicion_jugador,int cantidad_filas){
    int aux=0;
    aux=posicion_jugador->fil;
    posicion_jugador->fil=posicion_jugador->col;
    posicion_jugador->col=abs(aux-(cantidad_filas-1));   
}
/*
*Pre:cantidad_filas tiene que ser acorde a las dimensiones de la matriz a rotar.
*Pos:Rota todos los objetos del mapa de forma horaria.
*/
void rotar_mapa_horario(nivel_t* nivel,int filas,coordenada_t* posicion_jugador){
    rotar_paredes_horario(nivel->paredes,nivel->tope_paredes,filas);
    rotar_objetos_horario(nivel->obstaculos,nivel->tope_obstaculos,filas);
    rotar_objetos_horario(nivel->herramientas,nivel->tope_herramientas,filas);
    rotar_papeleos_horario(nivel->papeleos,nivel->tope_papeleos,filas);
    rotar_jugador_horario(posicion_jugador,filas);
}

/*
*Pre:-
*Pos:Rota de forma antihoraria las paredes que pertenecen al vector de paredes.
*/
void rotar_paredes_antihorario(coordenada_t paredes[MAX_PAREDES],int tope,int cantidad_columnas){
    int aux=0;
    for(int i=0;i< tope;i++){
        aux=paredes[i].col;
        paredes[i].col=paredes[i].fil;
        paredes[i].fil=abs(aux-(cantidad_columnas-1));
    }
}
/*
*Pre:
*Pos:Rota de forma antihoraria todos los objetos que pertenecen al vector de objetos.
*/
void rotar_objetos_antihorario(objeto_t objetos[MAX_OBJETOS],int tope, int cantidad_columnas){
    int aux=0;
    for(int i=0;i< tope;i++){
        aux=objetos[i].posicion.col;
        objetos[i].posicion.col=objetos[i].posicion.fil;
        objetos[i].posicion.fil=abs(aux-(cantidad_columnas-1));
    }
}
/*
*Pre:
*Pos:Rota de forma antihoraria todos los papeleos que pertenecen al vector de papeleos.
*/
void rotar_papeleos_antihorario(papeleo_t papeleos[MAX_PAPELEOS],int tope,int cantidad_columnas){
    int aux=0;
    for(int i=0;i< tope;i++){
        aux=papeleos[i].posicion.col;
        papeleos[i].posicion.col=papeleos[i].posicion.fil;
        papeleos[i].posicion.fil=abs(aux-(cantidad_columnas-1));
    }
}
/*
*Pre:
*Pos:Rota de forma antihoraria al jugador.
*/
void rotar_jugador_antihorario(coordenada_t* posicion_jugador,int cantidad_columnas){
    int aux=0;
    aux=posicion_jugador->col;
    posicion_jugador->col=posicion_jugador->fil;
    posicion_jugador->fil=abs(aux-(cantidad_columnas-1));   
}
/*
*Pre:cantidad_filas tiene que ser acorde a las dimensiones de la matriz a rotar.
*Pos:Rota todos los objetos del mapa de forma antihoraria. 
*/
void rotar_mapa_antihorario(nivel_t* nivel,int columnas,coordenada_t* posicion_jugador){
    rotar_paredes_antihorario(nivel->paredes,nivel->tope_paredes,columnas);
    rotar_objetos_antihorario(nivel->obstaculos,nivel->tope_obstaculos,columnas);
    rotar_objetos_antihorario(nivel->herramientas,nivel->tope_herramientas,columnas);
    rotar_papeleos_antihorario(nivel->papeleos,nivel->tope_papeleos,columnas);
    rotar_jugador_antihorario(posicion_jugador,columnas);
}

/*
*Pre:-
*Pos:Muevo una posición hacia la derecha al jugador. 
*/
void mover_derecha(coordenada_t* posicion_jugador){
    posicion_jugador->col++;
}
/*
*Pre:-
*Pos:Muevo una posición hacia la izquierda al jugador.
*/
void mover_izquierda(coordenada_t* posicion_jugador){
    posicion_jugador->col--;
}

/*
*Pre:Al sumar el número tengo que encontrarme dentro de la matriz.
*Pos:Devuelve true si tengo un elemento a la derecha o a la izquierda dependiendo del valor del número.
*/
bool hay_elemento_horizontal(coordenada_t posicion_jugador,coordenada_t posicion_pared,int numero){
    return(posicion_jugador.fil==posicion_pared.fil && posicion_jugador.col+numero==posicion_pared.col);
}
/*
*Pre:Al sumar el número tengo que encontrarme dentro de la matriz.
*Pos:Devuelve true si tengo un elemento a la arriba o abajo dependiendo del valor del número.
*/
bool hay_elemento_vertical(coordenada_t posicion_jugador,coordenada_t posicion_pared,int numero){
    return(posicion_jugador.fil+numero==posicion_pared.fil && posicion_jugador.col==posicion_pared.col);
}
/*
*Pre:PREGUNTAR:Los coordendas de el jugador y de la pared tienen que pertenecer al los vectores analizados. 
*Pos:Devuelve true si hay un pared en la posición horizontal en la que quiero hacer una acción(movimiento o utilizar ventaja), 
     sino false.
*/
bool hay_pared_en_posicion_lateral_requerida(coordenada_t jugador,int tope_paredes,coordenada_t paredes[MAX_PAREDES],int numero ){
    
    bool hay_pared=true;
    int cont_paredes=0;
    while(cont_paredes<tope_paredes && hay_pared){
        if(hay_elemento_horizontal(jugador,paredes[cont_paredes],numero)==true){
            hay_pared=false;
        }
        cont_paredes++;
    }
    return(hay_pared);
}

/*
*Pre:-
*Pos:Devuelve true si tengo ventajas,sino false.
*/
bool tengo_ventaja(int ventaja){
    return(ventaja>0);
}
/*
*Pre:-
*Pos:Devuelve true si el obstaculo a analizar es un fuego
*/
bool es_obstaculo_un_fuego(objeto_t obstaculo){
    return(obstaculo.tipo==FUEGOS);
}

/*
*Pre:-
*Pos:Devuelve verdadero si ingreso una dirección válida(A,D,W,S),sino devuelve false.
*/
bool es_direccion_valida(char direccion){
    return(direccion==MOV_DERECHA || direccion==MOV_IZQUIERDA || direccion==MOV_ARRIBA || direccion==MOV_ABAJO);
}

/*
*Pre:-
*Pos:Pregunta es que dirección se quiere utilizar la ventaja del martillo y solicita ingresar una dirección.
*/
void preguntar_direccion_para_martillar(char* direccion){
    while(!es_direccion_valida(*direccion)){
        printf("En que dirección quiere martillar ?\n");
        scanf(" %c",direccion);
    }


}
/*
*Pre:-
*Pos:Pregunta en que dirección se quiere utilizar la ventja del extintor y solicita ingresar una dirección
*/
void preguntar_direccion_para_extingir(char* direccion){
    while(!es_direccion_valida(*direccion)){
        printf("En que dirección quiere extingir ?\n");
        scanf(" %c",direccion);
    }
}

/*
*Pre:-
*Pos:Verifico si tengo martillos, en el caso de tenerlos pregunto la dirección se quiere martillar.
*/
void verificar_si_tengo_martillos(char* direccion,int martillos){
    
    if(tengo_ventaja(martillos)){
        preguntar_direccion_para_martillar(direccion);
    }else{
        printf("No te quedan más martillos\n");
    }
}
/*
*Pre:-
*Pos:Verifico si tengo extintores, en el caso de tenerlos pregunto la dirección se quiere extinguir.
*/
void verificar_si_tengo_extintores(char* direccion, int extintores){
    if(tengo_ventaja(extintores)){
        preguntar_direccion_para_extingir(direccion);
    }else{
        printf("No te quedan más extintores\n");
    }
}

/*
*Pre:Limite_dimensiones tiene que ser acorde a las dimensiones de la matriz que se este analizando.
*Pos:Devuelve verdadero si la pared solicitada se encuntra en el minite de la matriz, sino false.
*/
bool es_pared_borde_del_mapa(coordenada_t pared,int limite_dimensiones){
    return(pared.fil==0 || pared.fil==limite_dimensiones || pared.col==0 || pared.col==limite_dimensiones);
}
/*
*Pre:-
*Pos:Devuelve true si el movimiento el movimiento no es válido, sino false.
*/
bool es_movimiento_valido(coordenada_t jugador,coordenada_t pared,int numero){
    return((jugador.col+numero==pared.col && jugador.fil==pared.fil) ||
           (jugador.fil+numero==pared.fil && jugador.col==pared.col));
}

/*
*Pre:-
*Pos:En el caso de existir devuelve la posición de la pared,dentro del vector de paredes, que se encuentra horizontal al jugador,
     y sino devuelve -1.
*/
int posicion_pared_horizontal(coordenada_t posicion_jugador,coordenada_t paredes[MAX_PAREDES],int tope_paredes,int numero){
    int cont=0;
    bool encontre=false;
    while(cont<tope_paredes && !encontre){
        encontre=hay_elemento_horizontal(posicion_jugador,paredes[cont],numero);
        if(!encontre){
            cont++;
        }
    }
    if(!encontre){  
        return NO_EXISTE;
    }
    return cont;
}
/*
*Pre:-
*Pos:En el caso de existir devuelve la posición de la pared,dentro del vector de paredes, que se encuentra vertical al jugador,
     y sino devuelve -1.
*/
int posicion_pared_vertical(coordenada_t posicion_jugador,coordenada_t paredes[MAX_PAREDES],int tope_paredes,int numero){
    int cont=0;
    bool encontre=false;
    while(cont<tope_paredes && !encontre){
        encontre=hay_elemento_vertical(posicion_jugador,paredes[cont],numero);
        if(!encontre){
            cont++;
        }

    }
    if(!encontre){  
        return NO_EXISTE;
    }
    return cont;
}

/*
*Pre:-
*Pos:En el caso de existir devuelve la posición del fuego,dentro del vector de obstaculos, que se encuentra horizontal al jugador,
     y sino devuelve -1.
*/
int posicion_fuego_horizontal(coordenada_t posicion_jugador, objeto_t obstaculos[MAX_OBSTACULOS],int* tope_fuegos,int numero){
    int cont=0;
    bool encontre=false;
    while(cont<*tope_fuegos && !encontre){
        encontre= (hay_elemento_horizontal(posicion_jugador,obstaculos[cont].posicion,numero) && es_obstaculo_un_fuego(obstaculos[cont]));
        if(!encontre){
            cont++;
        }
    }
    if(!encontre){
        return NO_EXISTE;
    }
    return cont;
}
/*
*Pre:-
*Pos:En el caso de existir devuelve la posición del fuego,dentro del vector de obstaculos, que se encuentra vertical al jugador,
     y sino devuelve -1.
*/
int posicion_fuego_vertical(coordenada_t posicion_jugador, objeto_t obstaculos[MAX_OBSTACULOS],int* tope_fuegos,int numero){
    int cont=0;
    bool encontre=false;
    while(cont<*tope_fuegos && !encontre){
        encontre= (hay_elemento_vertical(posicion_jugador,obstaculos[cont].posicion,numero) && es_obstaculo_un_fuego(obstaculos[cont]));
        if(!encontre){
            cont++;
        }
    }
    if(!encontre){
        return NO_EXISTE;
    }
    return cont;
}
/*
*Pre:-
*Pos:Elimina una pared del vector de paredes y disminuye su tope.
*/
void eliminar_pared(int* tope_paredes,coordenada_t paredes[MAX_PAREDES],coordenada_t jugador,int posicion_pared){
    if (posicion_pared > NO_EXISTE) {
	    for (int i = posicion_pared; i < *tope_paredes-1; i++){
	    	paredes[i] = paredes[i+1];
	    }
	    (*tope_paredes)--;
	}
}
/*
*Pre:-
*Pos:Elimina un fuego de el vector de obstaculos y disminuye en uno su tope.
*/
void eliminar_fuego(int* tope_fuegos,objeto_t fuegos[MAX_OBJETOS],coordenada_t jugador,int posicion_fuego){
    if (posicion_fuego > NO_EXISTE) {
	    for (int i = posicion_fuego; i < *tope_fuegos-1; i++){
	    	fuegos[i] = fuegos[i+1];
	    }
	    (*tope_fuegos)--;
	}
}

/*
*Pre:Limite_dimensiones tiene que ser acorde a las dimensiones de la matriz que se este analizando.
*Pos:Se elimina una pared horizontal en el caso de existir y no estar en en borde de la matriz.
*/
void martillar_horizontal(int* martillos,coordenada_t jugador,coordenada_t paredes[MAX_PAREDES],int* tope_paredes,int limite_dimensiones,
int numero){
    int posicion=posicion_pared_horizontal(jugador,paredes,*tope_paredes,numero);
    if(posicion!=NO_EXISTE && !es_pared_borde_del_mapa(paredes[posicion],limite_dimensiones)){
        eliminar_pared(tope_paredes,paredes,jugador,posicion);
        (*martillos)--;
    }

}
/*
*Pre:Limite_dimensiones tiene que ser acorde a las dimensiones de la matriz que se este analizando.
*Pos:Se elimina una pared vertical en el caso de existir y no estar en en borde de la matriz.
*/
void martillar_vertical(int* martillos,coordenada_t jugador,coordenada_t paredes[MAX_PAREDES],int* tope_paredes,int limite_dimensiones,
int numero){
    int posicion=posicion_pared_vertical(jugador,paredes,*tope_paredes,numero);
    if(posicion!=NO_EXISTE && !es_pared_borde_del_mapa(paredes[posicion],limite_dimensiones)){
        eliminar_pared(tope_paredes,paredes,jugador,posicion);
        (*martillos)--;
    }

}

/*
*Pre:-
*Pos:Si existe se elimina un fuego horizontal al jugador.
*/
void extingir_horizontal(int* extintores,coordenada_t jugador,objeto_t fuegos[MAX_OBJETOS],int* tope_fuegos,int numero){
    int posicion=posicion_fuego_horizontal(jugador,fuegos,tope_fuegos,numero);
    if(posicion!=NO_EXISTE){
        eliminar_fuego(tope_fuegos,fuegos,jugador,posicion);
        (*extintores)--;
    }
}
/*
*Pre:-
*Pos:Si existe se elimina un fuego vertical al jugador.
*/
void extingir_vertical(int* extintores,coordenada_t jugador,objeto_t fuegos[MAX_OBJETOS],int* tope_fuegos,int numero){
    int posicion=posicion_fuego_vertical(jugador,fuegos,tope_fuegos,numero);
    if(posicion!=NO_EXISTE){
        eliminar_fuego(tope_fuegos,fuegos,jugador,posicion);
        (*extintores)--;
    }
}

/*
*Pre:Limite_dimensiones tiene que ser acorde a las dimensiones de la matriz que se este analizando.
*Pos:En el caso de tener martillos pregunta en que dirección se quiere martillar y la dirección ingresada se elimina la pared,sino
     te muestra por pantalla que no tenes más martillos.
*/
void utilizar_martillo(int* martillos,coordenada_t jugador,coordenada_t paredes[MAX_PAREDES],int* tope_paredes,int limite_dimensiones){
    char direccion='L';
    if(tengo_ventaja(*martillos)){
        preguntar_direccion_para_martillar(&direccion);
        if(direccion==MOV_DERECHA){
            martillar_horizontal(martillos,jugador,paredes,tope_paredes,limite_dimensiones,POSICION_AUMENTADA);
        }else if(direccion==MOV_IZQUIERDA){
            martillar_horizontal(martillos,jugador,paredes,tope_paredes,limite_dimensiones,POSICION_DISMINUIDA);
        }else if (direccion==MOV_ARRIBA){
            martillar_vertical(martillos,jugador,paredes,tope_paredes,limite_dimensiones,POSICION_DISMINUIDA);
        }else if(direccion==MOV_ABAJO){
            martillar_vertical(martillos,jugador,paredes,tope_paredes,limite_dimensiones,POSICION_AUMENTADA);
        }
    }else{
        printf("No te quedan más martillos\n");
    }
}
/*
*Pre:-
*Pos:En el caso de tener extintores pregunta en que dirección se quiere extinguir y la dirección ingresada se elimina el fuego, sino
     te muestra por pantalla que no tenes más extintores.
*/
void utlilizar_extintor(int* extintores,coordenada_t jugador,objeto_t fuegos[MAX_OBJETOS],int* tope_fuegos){
    char direccion='L';
    if(tengo_ventaja(*extintores)){
        preguntar_direccion_para_extingir(&direccion);
        if(direccion==MOV_DERECHA){
            extingir_horizontal(extintores,jugador,fuegos,tope_fuegos,POSICION_AUMENTADA);
        }else if(direccion==MOV_IZQUIERDA){
            extingir_horizontal(extintores,jugador,fuegos,tope_fuegos,POSICION_DISMINUIDA);
        }else if(direccion==MOV_ARRIBA){
            extingir_vertical(extintores,jugador,fuegos,tope_fuegos,POSICION_DISMINUIDA);
        }
    }else{
        printf("No te quedan más extintores\n");
    }
}
/*
*Pre:La ventaja tiene que ser un caracter valido, en este caso Z y C, y Limite_dimensiones tiene que ser acorde a las 
     dimensiones de la matriz que se este analizando.
*Pos: Segun el valor ingresado(Z,C) va a martillar una pared o extinguir un fuego.
*/
void utilizar_ventajas(nivel_t* nivel,char ventaja,jugador_t* jugador,int limite_dimensiones){

    if(ventaja==MARTILLO){
        utilizar_martillo(&jugador->martillos,jugador->posicion,nivel->paredes,&nivel->tope_paredes,limite_dimensiones);
    }
    if(ventaja==EXTINTOR){
        utlilizar_extintor(&jugador->extintores,jugador->posicion,nivel->obstaculos,&nivel->tope_obstaculos);
    }
}

/*
*Pre:-
*Pos:Devuelve true si hay algun objeto,perteneciente al vector de objetos, que este en la misma posción del jugador, sino false.
*/
bool hay_objeto_en_posicion(coordenada_t jugador,objeto_t objetos[MAX_OBJETOS],int tope,char objeto){
    bool hay_objeto=false;
    for(int i=0;i<tope;i++){
        if(jugador.col==objetos[i].posicion.col && jugador.fil==objetos[i].posicion.fil && objetos[i].tipo==objeto){
            hay_objeto=true;
        }
    }
    return hay_objeto;
}
/*
*Pre:
*Pos:Determina lo que sucede cuando paso por arriba de una herramienta o un obstaculo.
*/
void pasar_por_objeto(jugador_t* jugador,nivel_t nivel){

    if(hay_objeto_en_posicion(jugador->posicion,nivel.obstaculos,nivel.tope_obstaculos,FUEGOS)){
        jugador->movimientos=0;
    }else if(hay_objeto_en_posicion(jugador->posicion,nivel.obstaculos,nivel.tope_obstaculos,MEDIAS)){
        jugador->movimientos=jugador->movimientos-MOVIMIENTOS_RESTADOS;
    }else if(hay_objeto_en_posicion(jugador->posicion,nivel.herramientas,nivel.tope_herramientas,INTERRUPTORES)){
        if(jugador->ahuyenta_randall==false){
            jugador->ahuyenta_randall=true;
        }else{
            jugador->ahuyenta_randall=false;
        }
    }else if(hay_objeto_en_posicion(jugador->posicion,nivel.herramientas,nivel.tope_herramientas,BOTELLA_DE_GRITOS)){
        jugador->movimientos=jugador->movimientos+MOVIMIENTOS_SUMADOS;
    }
}

/*
*Pre:
*Pos:Devuelve true si la posición del jugador es igual a la posición del papeleo, sino devuelve false.
*/
bool hay_papeleo_en_posicion(coordenada_t  posicion_jugador,papeleo_t papeleo ){
    return(posicion_jugador.col==papeleo.posicion.col && posicion_jugador.fil==papeleo.posicion.fil);
}
/*
*Pre: i tiene que ser un valor positivo.
*Pos:Devuelve true si el papeleo anterior ya fue recolectado, sino devuelve false.
*/
bool esta_papeleo_anterior_recolectado(papeleo_t papeleos[MAX_PAPELEOS],int tope_papeleos,int i){
    return(papeleos[i-1].recolectado==true);
}
/*
*Pre:-
*Pos:Si hay un papeleo en la posción del jugador y no esta recolectado lo recolecta.
*/
void recolectar_papeleo(coordenada_t posicion_jugador, papeleo_t papeleos[MAX_PAPELEOS],int tope_papeleos){
    for(int i=0;i<tope_papeleos;i++){
        if(hay_papeleo_en_posicion(posicion_jugador,papeleos[i]) && !esta_recolectado(papeleos[i]) &&
            esta_papeleo_anterior_recolectado(papeleos,tope_papeleos,i)){
            papeleos[i].recolectado=true;
        }
    }
}

/*
*Pre:No sirve para en el limite inferior de la matriz.
*Pos:Devuelve verdadero si tengo una pared una posción abajo, sino devuelve false.
*/
bool hay_pared_debajo(coordenada_t jugador,coordenada_t paredes[MAX_PAREDES], int tope_paredes){
    bool hay_pared=false;
    for(int i=0;i<tope_paredes;i++){
        if(jugador.col==paredes[i].col && jugador.fil+1== paredes[i].fil){
            hay_pared=true;
        }     
    }
    return hay_pared;
}
/*
*Pre:-
*Pos:El jugador desciende una posción.
*/
void caer_una_posicion(coordenada_t* jugador){
    jugador->fil++;
}
/*
*Pre:-
*Pos:Genera el efecto de gravedad y chequea por todas las posiciones por las que pasa el jugador si es que hay algun obstaculo,
     herramienta o papeleo y determina lo que sucede en cada caso.
*/
void generar_gravedad(jugador_t* jugador,nivel_t* nivel){
    while(!hay_pared_debajo(jugador->posicion,nivel->paredes,nivel->tope_paredes) && ((jugador->movimientos!=0) ||  estado_nivel(nivel->papeleos,nivel->tope_papeleos)==JUGANDO)){
        caer_una_posicion(&jugador->posicion);
        pasar_por_objeto(jugador,*nivel);
        recolectar_papeleo(jugador->posicion,nivel->papeleos,nivel->tope_paredes);

    }
}

/*
*Pre:El valor de las paredes,movimientos y número_nivel tienen que ser positivos.
*Pos:Genera nuevas paredes de forma aleatoria durante los primeros x movimientos que esta determinado por cant_nuevas_paredes que
     varía con cada nivel.
*/
void agregar_nuevas_paredes(int numero_nivel,nivel_t* nivel,int movimientos_realizados,int cant_nuevas_paredes){

    coordenada_t posicion_generada;
    posicion_generada.fil=0;
    posicion_generada.col=0;
    if(movimientos_realizados<=cant_nuevas_paredes){
        generar_posicion_valida(numero_nivel,&posicion_generada,*nivel);
        nivel->paredes[(nivel->tope_paredes)]=posicion_generada;
        nivel->tope_paredes++;
    }
}
/*
*Pre:-
*Pos:Genera un número al azar entre 0 y el tope de los papeleos.
*/
void seleccionar_papeleo_al_azar(int tope_papeleos,int* papeleo_seleccionado){
    (*papeleo_seleccionado)=rand() % tope_papeleos;
}
/*
*Pre:-
*Pos:Devuelve la posición de un papeleo dentro del vector papeleos mientras no esta recolectado y se siga jugando el nivel.
*/
int ubicacion_papeleo_no_recolectado(papeleo_t papeleos[MAX_PAPELEOS],int tope_papeleos){
    
    int papeleo_seleccionado=0;
    seleccionar_papeleo_al_azar(tope_papeleos,&papeleo_seleccionado);
    while(esta_recolectado(papeleos[papeleo_seleccionado])&& estado_nivel(papeleos,tope_papeleos)==JUGANDO){
        seleccionar_papeleo_al_azar(tope_papeleos,&papeleo_seleccionado);
    }
    return(papeleo_seleccionado);
}
/*
*Pre:La fila y columna de nueva_posicion tinen que ser mayores o iguales a cero.
*Pos:Cambía la posción de un papeleo.
*/
void cambiar_posicion_papeleo(papeleo_t* papeleo,coordenada_t nueva_posicion){
    papeleo->posicion=nueva_posicion;
}
/*
*Pre:Divisor tiene que ser mayor a cero y numero tiene que ser mayor o igual a cero.
*Pos:Devuelve verdadero si el número ingresado es divisible por divisor.
*/
bool es_divisible(int numero,int divisor){
    return(numero%divisor==0);
}
/*
*Pre:divisor tiene que ser positivo.
*Pos:Si el interruptor ahuyenta_randall es false y los movimientos son divisibles por un valor R asignado en cada nivel se mueve 
     el papeleo de forma aleatoria, sino no se mueve.
*/
void mover_papeleo(nivel_t nivel,int numero_nivel,papeleo_t papeleos[MAX_PAPELEOS],int tope_papeleos,jugador_t jugador,int divisor){
    
    int ubic_papeleo=ubicacion_papeleo_no_recolectado(papeleos,tope_papeleos);
    coordenada_t nueva_coordenada;
    nueva_coordenada.fil=0;
    nueva_coordenada.col=0;
    if(jugador.ahuyenta_randall==false && es_divisible(jugador.movimientos_realizados,divisor)){
        generar_posicion_valida(numero_nivel,&nueva_coordenada,nivel);
        cambiar_posicion_papeleo(&papeleos[ubic_papeleo],nueva_coordenada);
    }
}

/*
*Pre:-
*Pos:Devuelve true si en movimiento ingresado en válido, sino false.
*/
bool es_movimiento_valido_2(char movimiento){
    return(movimiento==MOV_DERECHA || movimiento==MOV_IZQUIERDA || movimiento==MOV_ARRIBA || movimiento==MOV_ABAJO || 
           movimiento==MOV_ROTACIONAL_HORARIO || movimiento==MOV_ROTACIONAL_ANTIHORARIO || movimiento== MARTILLO || 
           movimiento==EXTINTOR);
}
/*
*Pre:Divisor,limite_dimensiones,numero_nivel y cant_nuevas paredes tienen que ser mayores o iguales a 0.
*Pos:Según el comando ingresado realiza un movimiento, modifica las condiciones del jugador y si se cumplen sus condiciones se 
     se generan nuevas paredes y se mueve un papeleo de forma aleatoria.
*/
void realizar_movimientos(nivel_t* nivel,jugador_t* jugador,char* movimiento,int limite_dimensiones,int numero_nivel,
                          int cant_nuevas_paredes,int divisor){
        
    if((*movimiento) == MOV_ROTACIONAL_HORARIO){
        rotar_mapa_horario(nivel,limite_dimensiones,&jugador->posicion);
        jugador->movimientos_realizados++;
        agregar_nuevas_paredes(numero_nivel,nivel,jugador->movimientos_realizados,cant_nuevas_paredes);
        mover_papeleo(*nivel,numero_nivel,nivel->papeleos,nivel->tope_papeleos,*jugador,divisor);
        jugador->movimientos--;
    }else if((*movimiento) == MOV_ROTACIONAL_ANTIHORARIO){
        rotar_mapa_antihorario(nivel,limite_dimensiones,&jugador->posicion);
        jugador->movimientos_realizados++;
        jugador->movimientos--;
        agregar_nuevas_paredes(numero_nivel,nivel,jugador->movimientos_realizados,cant_nuevas_paredes);
        mover_papeleo(*nivel,numero_nivel,nivel->papeleos,nivel->tope_papeleos,*jugador,divisor);
    }else if ((*movimiento) == MOV_DERECHA && hay_pared_en_posicion_lateral_requerida(jugador->posicion,nivel->tope_paredes,
                                                                           nivel->paredes, POSICION_AUMENTADA)==true){
        mover_derecha(&jugador->posicion);
        jugador->movimientos_realizados++;
        jugador->movimientos--;
        agregar_nuevas_paredes(numero_nivel,nivel,jugador->movimientos_realizados,cant_nuevas_paredes);
        mover_papeleo(*nivel,numero_nivel,nivel->papeleos,nivel->tope_papeleos,*jugador,divisor);
    }else if ((*movimiento) == MOV_IZQUIERDA && hay_pared_en_posicion_lateral_requerida(jugador->posicion,nivel->tope_paredes,
                                                                             nivel->paredes,POSICION_DISMINUIDA)==true){
        mover_izquierda(&jugador->posicion);
        jugador->movimientos_realizados++;
        jugador->movimientos--;
        agregar_nuevas_paredes(numero_nivel,nivel,jugador->movimientos_realizados,cant_nuevas_paredes);
        mover_papeleo(*nivel,numero_nivel,nivel->papeleos,nivel->tope_papeleos,*jugador,divisor);
    }
}
/*
*Pre:-
*Pos:Se valida el movimiento ingresado.
*/
void validar_movimiento(char* movimiento){
    
    while(!es_movimiento_valido_2(*movimiento)){
        printf("Comando invalido\n");
        printf("Ingrese su movimiento\n");
        scanf(" %c",movimiento);   
    }
}
/*
*Pre: divosor tiene que ser mayor a 0, cant_nuevas paredes tienen que ser mayor igual a 0 y limite_dimensiones tiene que ser acorde
      a las dimensiones de la matriz.
*Pos:Realiza un jugada segun los valores limite_dimensiones,divisor y cant_nuevas_paredes.
*/
void jugar_nivel(juego_t* juego,int limite_dimensiones,int divisor,int cant_nuevas_paredes){
    
    char movimiento='L';
    validar_movimiento(&movimiento);
    realizar_movimientos(&juego->niveles[juego->nivel_actual-1],&juego->jugador,&movimiento,limite_dimensiones,juego->nivel_actual,
    cant_nuevas_paredes,divisor);
    utilizar_ventajas(&juego->niveles[juego->nivel_actual-1],movimiento,&juego->jugador,limite_dimensiones-1);
    pasar_por_objeto(&juego->jugador,juego->niveles[juego->nivel_actual-1]);
    recolectar_papeleo(juego->jugador.posicion,juego->niveles[juego->nivel_actual-1].papeleos,juego->niveles[juego->nivel_actual-1].tope_papeleos);
    generar_gravedad(&juego->jugador,&juego->niveles[juego->nivel_actual-1]);
}
/*
*Pre:-
*Pos:Pasa de nivel, reinicia los movimientos realizados,carga las caracteristicas del jugador del siguiente nivel y se suman los 
     movimintos que sobraron del nivel anterior a los del nuevo nivel. 
*/
void pasar_de_nivel(papeleo_t papeleos[MAX_PAPELEOS],int tope_papeleos,juego_t* juego){
    if(estado_nivel(papeleos,tope_papeleos)==GANADO && estado_juego(*juego)==JUGANDO){
        int movimientos_nivel_anterior=juego->jugador.movimientos;
        (juego->nivel_actual)++;
        juego->jugador.movimientos_realizados=0;
        inicializar_personaje(&juego->jugador,juego->nivel_actual,juego->personaje_tp1,juego->niveles[juego->nivel_actual-1].pos_inicial_jugador);
        juego->jugador.movimientos=juego->jugador.movimientos+movimientos_nivel_anterior;
    }
}
/*
*Pre:Nivel_actual tiene que ser un número positivo y tiene que pertencer al vector de niveles.
*Pos:Según el nivel en el que se encuntre se cargan los valores de limite_dimensiones,divisor y cant_nuevas_paredes.
*/
void caracterizar_jugada_segun_nivel(int* limite_dimensiones,int* divisor,int* cant_nuevas_paredes,int nivel_actual){
    if(nivel_actual==PRIMER_NIVEL){
        (*limite_dimensiones)=LIMITE_FIL_NIVEL_1;
        (*divisor)=DIVISOR_NIVEL_1;
        (*cant_nuevas_paredes)=NUEVAS_PAREDES_NIVEL_1;
    }else if(nivel_actual==SEGUNDO_NIVEL){
        (*limite_dimensiones)=LIMITE_FIL_NIVEL_2;
        (*divisor)=DIVISOR_NIVEL_2;
        (*cant_nuevas_paredes)=NUEVAS_PAREDES_NIVEL_2;
    }else{
        (*limite_dimensiones)=LIMITE_COL_NIVEL_3;
        (*divisor)=DIVISOR_NIVEL_3;
        (*cant_nuevas_paredes)=NUEVAS_PAREDES_NIVEL_3;
    } 
}

void realizar_jugada(juego_t* juego){
    int limite_dimensiones=0;
    int divisor=0;
    int cant_nuevas_paredes=0;
    caracterizar_jugada_segun_nivel(&limite_dimensiones,&divisor,&cant_nuevas_paredes,juego->nivel_actual);
    jugar_nivel(juego,limite_dimensiones,divisor,cant_nuevas_paredes);
    pasar_de_nivel(juego->niveles[juego->nivel_actual-1].papeleos,juego->niveles[juego->nivel_actual-1].tope_papeleos,juego);
}
