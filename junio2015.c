#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
1.- (3 puntos) Se va a celebrar una regata nacional de vela en la Bahía de Cádiz.
En la regata compiten tres modalidades: Snipe, Láser y Optimits. En la cada modalidad pueden participar como
máximo N regatistas. La organización necesita almacenar para cada regatista  la siguiente información:
apellidos y nombre del regatista, número de vela, club al que pertenece y resultado obtenido por el participante
en cada una de las cinco mangas (pruebas) realizadas. El resultado que en cada manga tiene un participante es el
lugar que ha quedado en la prueba, así el que ha llegado primero recibe un punto, el que ha llegado
segundo dos puntos y así sucesivamente.
*/

#define N_PRUEBAS 5

typedef enum{SNIPE, LASER, OPTIMITS} modalidades;

typedef struct{
    char nombre[50];
    char apellidos[100];
    int numVela;
    char club[50];
    int resultados[N_PRUEBAS];
    modalidades modalidadRegatista;
}regatistas;

int main(){
    int nRegatistas;
    regatistas *regatista;
    printf("Introduzca el numero de regatistas: ");
    scanf("%d", &nRegatistas);

    /*b) Suponga que el usuario introduce el numero de regatista. Implemente el código para reservar memoria.*/

    regatista = (regatistas *)calloc(nRegatistas, sizeof(regatistas));
    if(regatista == NULL){
        printf("No se pudo reservar memoria. \n");
        exit(1);
    }

    free(regatista);
    return 0;
}

/*
(1,25 puntos) Suponiendo que la estructura ya tiene la información almacenada,
diseña una función en pseudocódigo que reciba como parámetro la estructura , el nombre de un club y
una modalidad (Snipe, Láser u Optimits) y escriba los puntos
totales obtenidos por el club en dicha modalidad.
Para calcular los puntos de un regatista hay que tener en cuenta que todos los regatistas
hacen un descarte, es decir, tienen que eliminar de sus cinco puntuaciones la peor de todas (la más alta) y
el resto se sumará para calcular la puntuación total.
*/

//Precondición: recibir la estructura inicializada, {numRegatista >= 1 ^ modalidad >= 0 ^ modalidad <= 2}, nombreClub inicializado
void puntuacion_modalidad(regatistas *regatistaModalidad, int numRegatistas, const char *nombreClub, modalidades modalidad){
    int maxPuntos = 0, puntosTotal = 0;
    for(int i = 0; i < numRegatistas; i++){
        //Encontrar regatista por nombre, modalidad y club
        if(!strcmp(regatistaModalidad[i].club, nombreClub) && regatistaModalidad[i].modalidadRegatista == modalidad){
          //Eliminar nota más alta
          for(int j = 0; j < N_PRUEBAS; j++){
            puntosTotal += regatistaModalidad[i].resultados[j];
            if(regatistaModalidad[i].resultados[j] > maxPuntos){
                maxPuntos = regatistaModalidad[i].resultados[j];
            }
          }
          //Una vez encontrado el maximo se le resta a la suma total
          puntosTotal -= maxPuntos;
        }
    }

    //Tras tener todo ya calculado mostramos
    printf("El club %s ha conseguido en total %d puntos en la modalidad %d. \n", nombreClub, puntosTotal, modalidad);
}

/*d) (0,75 puntos) Suponiendo que la estructura ya tiene la información almacenada, diseña un procedimiento en lenguaje C que reciba un puntero a la estructura,
una modalidad (Snipe, Laser u Optimits) y escriba el nombre del campeón de la modalidad. */



//Precondición: recibir una estructura ya inicializada, {numRegatistas = N >= 1 ^ modalidadRegatista <= 0 ^ modalidadRegatista <= 2}
//Poscondición: imprime en pantalla el ganador de esa categoria
void ganador_modalidad(regatistas *regatistaGanador, int numRegatistas, modalidades modalidadRegatista){
    int puntuacionMaxima = 0, puntuacionTotalRegatista = 0, puntuacionMaximaRegatista = 0;
    int indexRegatistaGanador;

    for(int i = 0; i < numRegatistas; i++){
      //Buscamos por modalidad
      if((regatistaGanador+i)->modalidadRegatista == modalidadRegatista){
        //Buscamos la puntuación maxima para almacenarla y guardar su index
        puntuacionTotalRegatista = 0; //Ambas se reinician para otros regatistas
        puntuacionMaximaRegatista = 0;
        for(int j = 0; j < N_PRUEBAS; j++){ //recorre cada prueba
          puntuacionTotalRegatista += (regatistaGanador+i)->resultados[j];
          if((regatistaGanador+i)->resultados[j] > puntuacionMaximaRegatista){
            puntuacionMaximaRegatista = (regatistaGanador+i)->resultados[j];  //Encuentra la puntuación maxima de un regatista en concreto para eliminarla
          }
        }

        puntuacionTotalRegatista -= puntuacionMaximaRegatista;
      }

      if(puntuacionTotalRegatista > puntuacionMaxima){  //Ya calculada la puntuacion de ese regatista comprobamos si es maxima
          puntuacionMaxima = puntuacionTotalRegatista;
          indexRegatistaGanador = i;
      }
    }

    printf("El ganador de la categoria %d es %s con %d puntos. \n", modalidadRegatista, regatistaGanador[indexRegatistaGanador].nombre, puntuacionMaxima);
}

