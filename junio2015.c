#include <stdio.h>
#include <stdlib.h>

/*1.- (3 puntos) Se ha decidido organizar un concurso para nuevos talentos musicales en el que
van a concursar 20 aspirantes. Para apuntarse a la competición cada concursante debe indicar su
nombre artístico, fecha de nacimiento (con formato día, mes y año) y estilo musical que
presenta (flamenco, pop o rock).
Cada concursante presenta su canción ante el jurado que está formado por cinco personas y cada
miembro del jurado emite un voto entre 0 y 10 puntos (siendo 0 la nota más baja y 10 la mejor
nota), la puntuación total del jurado será la media de las puntuaciones de sus miembros. Además
de la votación del jurado se tendrá en cuenta también la votación del público que también se
computará con un solo voto entre 0 y 10 puntos. La puntuación final de cada concursante se
obtendrá como suma de las dos, teniendo en cuenta que la votación del jurado representará el
60% de la puntuación total y la votación del público será el 40% restante */

typedef enum {FLAMENCO, POP, ROCK} estiloMusical;
#define N_ASPIRANTES 20
#define N_JURADO 5
#define N_CATEGORIAS 3

typedef struct {
    char nombre[50];
    estiloMusical estiloMusicalAspirante;
    int diaNacimiento;
    int mesNacimiento;
    int anoNacimiento;
    float puntuacionJurado[N_JURADO];
    float puntuacionPublico;
    float puntuacionFinal;
}aspirantes;

void nota_final(aspirantes *);
void puntuacionMaxima(aspirantes *);

int main(){
    aspirantes listaAspirante[N_ASPIRANTES] = {
        {"Juan Perez", ROCK, 15, 3, 1995, {8.5, 9.0, 7.5, 8.0, 9.2}, 8.7, 0},
        {"Maria Gomez", POP, 22, 6, 2000, {7.5, 8.0, 8.2, 7.9, 8.3}, 7.8, 0},
        {"Carlos Lopez", FLAMENCO, 5, 11, 1998, {9.0, 8.5, 9.2, 8.7, 9.1}, 9.0, 0},
        {"Laura Sánchez", ROCK, 10, 2, 1993, {8.8, 9.1, 8.9, 9.0, 8.7}, 8.9, 0},
        {"Pedro Martinez", POP, 30, 7, 1997, {7.0, 7.5, 7.8, 7.3, 7.6}, 7.4, 0},
        {"Ana Torres", FLAMENCO, 12, 4, 1999, {9.1, 9.3, 9.0, 9.2, 9.4}, 9.2, 0},
        {"Luis Ramirez", ROCK, 18, 10, 1996, {8.0, 7.8, 8.2, 8.0, 7.9}, 7.8, 0},
        {"Sofía Herrera", POP, 25, 8, 2001, {9.5, 9.2, 9.3, 9.4, 9.1}, 9.3, 0},
        {"Daniel Rojas", FLAMENCO, 7, 1, 1994, {8.2, 8.4, 8.5, 8.6, 8.3}, 8.4, 0},
        {"Carolina Díaz", ROCK, 19, 5, 1995, {7.9, 7.6, 7.8, 7.5, 7.7}, 7.6, 0},
        {"Javier Mendez", POP, 14, 9, 1992, {9.0, 8.8, 9.1, 8.9, 9.2}, 9.0, 0},
        {"Paula Fernández", FLAMENCO, 8, 3, 1998, {7.7, 8.1, 7.9, 8.0, 7.8}, 7.9, 0},
        {"Fernando Castro", ROCK, 21, 6, 1999, {8.6, 8.9, 8.7, 8.8, 8.5}, 8.8, 0},
        {"Gabriela Paredes", POP, 3, 12, 1996, {9.3, 9.5, 9.4, 9.2, 9.6}, 9.5, 0},
        {"Roberto Ortiz", FLAMENCO, 28, 7, 2002, {7.3, 7.5, 7.6, 7.4, 7.2}, 7.4, 0},
        {"Camila Nuñez", ROCK, 11, 11, 1993, {8.9, 9.2, 9.0, 9.1, 8.8}, 9.0, 0},
        {"Alejandro Vera", POP, 6, 2, 1997, {7.8, 7.9, 7.7, 8.0, 7.6}, 7.8, 0},
        {"Isabel Mendoza", FLAMENCO, 16, 5, 1995, {9.4, 9.6, 9.5, 9.3, 9.2}, 9.5, 0},
        {"Oscar Jimenez", ROCK, 20, 4, 1991, {8.3, 8.6, 8.4, 8.2, 8.5}, 8.4, 0},
        {"Valentina Flores", POP, 9, 8, 2003, {7.5, 7.7, 7.6, 7.8, 7.4}, 7.7, 0}
    };
    nota_final(listaAspirante);
    puntuacionMaxima(listaAspirante);
    for(int i = 0; i < N_ASPIRANTES; i++){
      printf("Aspirante %s y %f. \n", listaAspirante[i].nombre, listaAspirante[i].puntuacionFinal);
    }
    return 0;
}

/*Suponiendo que en la estructura están almacenados ya los datos de los
concursantes junto con las puntuaciones parciales del jurado y la puntuación del público.
Realiza un procedimiento en pseudocódigo que calcule y almacene en la estructura la
puntuación final de cada concursante.*/

//Precondición: recibir la estructura ya inicializada
//Poscondición: almacenar la nota final en la estructura
void nota_final(aspirantes *aspirante){
    float notaJurado = 0;
    for(int i = 0; i < N_ASPIRANTES; i++){
        for(int j = 0; j < N_JURADO; j++){
            notaJurado += aspirante[i].puntuacionJurado[j];
        }

        notaJurado /= N_JURADO;
        aspirante[i].puntuacionFinal = notaJurado * 0.6 + 0.4 * (aspirante[i].puntuacionPublico);
        notaJurado = 0;
    }
}

/*(1,25 puntos) Realiza un procedimiento que reciba como parámetro la estructura (con
los datos de las puntuaciones finales ya almacenados), y un determinado estilo musical y
escriba por pantalla el nombre del concursante con mejor puntuación en ese estilo. En
caso de que haya más de uno con la misma puntuación deberá escribir el nombre del
concursante más joven de ellos (suponiendo que no existen fechas repetidas) */


//Precondición: recibir toda la estructura almacenada incluyendo su nota final
//Poscondición: imprime las notas más altas de cada categoria
void puntuacionMaxima(aspirantes *aspirante){
  float puntuacionMaxima[N_CATEGORIAS] = {0.0, 0.0, 0.0}; //Cada posición tiene una nota según su categoria !Fijarse en tipo enumerado para saber valor!
  estiloMusical categoria;
  int indexMaxPuntuacion[N_CATEGORIAS];
  for(int i = 0; i < N_ASPIRANTES; i++){  //Recorre cada aspirante en busca de puntuación maxima

    categoria = aspirante[i].estiloMusicalAspirante;  //Recibe una categoria asociada a un número

    if(aspirante[i].puntuacionFinal > puntuacionMaxima[categoria]){ //La categoria hará como indice del vector puntuación Max
      puntuacionMaxima[categoria] = aspirante[i].puntuacionFinal;
      indexMaxPuntuacion[categoria] = i;                                        //Guarda el indice de la nota maxima
    } else if(aspirante[i].puntuacionFinal == puntuacionMaxima[categoria]) {  //En caso de notas =, compara aquel mas jove
      if(aspirante[i].anoNacimiento < aspirante[indexMaxPuntuacion[categoria]].anoNacimiento){
        puntuacionMaxima[categoria] = aspirante[i].puntuacionFinal;
      } else if (aspirante[i].mesNacimiento < aspirante[indexMaxPuntuacion[categoria]].mesNacimiento){
        puntuacionMaxima[categoria] = aspirante[i].puntuacionFinal;
      } else if (aspirante[i].diaNacimiento < aspirante[indexMaxPuntuacion[categoria]].diaNacimiento){
        puntuacionMaxima[categoria] = aspirante[i].puntuacionFinal;
      }

    }
  }

  for(int j = 0; j < N_CATEGORIAS; j++){  //Imprime cada posición del vector indexMaxPuntuacion 0(FLAMENCO), 1(POP) y 2(ROCK)
    if(aspirante[indexMaxPuntuacion[j]].estiloMusicalAspirante == FLAMENCO){
      printf("El concursante con la nota más alta de FLAMENCO es %s y su nota es %f. \n", aspirante[indexMaxPuntuacion[j]].nombre, aspirante[indexMaxPuntuacion[j]].puntuacionFinal);
    } else if (aspirante[indexMaxPuntuacion[j]].estiloMusicalAspirante == POP){
      printf("El concursante con la nota más alta de POP es %s y su nota es %f. \n", aspirante[indexMaxPuntuacion[j]].nombre, aspirante[indexMaxPuntuacion[j]].puntuacionFinal);
    } else if (aspirante[indexMaxPuntuacion[j]].estiloMusicalAspirante == ROCK){
      printf("El concursante con la nota más alta de ROCK es %s y su nota es %f. \n", aspirante[indexMaxPuntuacion[j]].nombre, aspirante[indexMaxPuntuacion[j]].puntuacionFinal);
    }
  }
}
