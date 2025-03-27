#include <stdio.h>
#include <stdlib.h>
/*
Un restaurante tiene inter�s en informatizar las reservas de su comedor. Debido al protocolo
COVID-19 el n�mero de mesas y comensales est� limitado y el restaurante ha decidido
establecer cuatro turnos de comida para compensar las p�rdidas del negocio. Los dos primeros
turnos son para el horario de comidas y los dos �ltimos para el horario de cenas. El n�mero
m�ximo de mesas que se pueden ocupar en cada turno es de 25.
Cuando se realiza una reserva, se deber� indicar el turno que se desea (1�, 2�, 3� o 4�). Si quedan
mesas disponibles seg�n las preferencias del cliente, el �maitre� realizar� la reserva
almacenando para esa mesa y turno, el nombre y apellidos del comensal que realiza la reserva,
el n�mero de tel�fono y el n�mero total de comensales. Al finalizar el servicio, se almacenar�
tambi�n el importe de la factura de la mesa.
El gestor del restaurante desea tener almacenada la informaci�n de las reservas realizadas por
cada d�a del mes (suponiendo un mes de 30 d�as y que el restaurante no cierra nunca). Se supone
que al comenzar el mes todas las mesas de todos los turnos se inicializan poniendo el n�mero de
comensales a cero.
*/

typedef struct {
  char NombreReserva[50];
  char ApellidosReserva[100];
  int numTelefono;
  int numComensal;
  float cuentaMesa;
}mesa;

#define N_ABIERTO 30
#define N_MESAS 25
#define N_TURNOS 4

typedef enum {ALMUERZO, CENA} tipoTurno;

typedef struct {
  mesa mesas[N_MESAS];
  tipoTurno miTurno;
}turno;

typedef struct {
  turno turnosDias[N_TURNOS];
}diasAbiertos;

void turno_comensales(diasAbiertos *);
void facturado_reserva(diasAbiertos *, const char *, tipoTurno);

int main(){
  return 0;
}


/*
(1,25 puntos) Dise�a un procedimiento en pseudoc�digo que reciba como par�metro la
estructura dise�ada en el apartado anterior y escriba cual es el d�a del mes y en qu� tipo de
turno (comida o cena) ha habido mayor n�mero de comensales. El procedimiento tambi�n
deber� escribir por pantalla el n�mero de mesas que se han quedado libres por d�a y turno
(1, 2, 3 o 4).
*/

//Precondici�n recibir la estructura ya inicializada
//Poscondici�n: imprimir turno y dia con mas comensales adem�s de mesas vacias en cada d�a.
void turno_comensales(diasAbiertos diasDisponibles[N_ABIERTO]){
  int numComensalesTurno = 0, numComensalesMax = 0, indexDiaMax, indexTurnoMax, mesasVacias = 0;

  for(int i = 0; i < N_ABIERTO; i++){
    for(int j = 0; j < N_TURNOS; j++){
      for(int k = 0; k < N_MESAS; k++){
        numComensalesTurno += diasDisponibles[i].turnosDias[j].mesas[k].numComensal;
        if(!diasDisponibles[i].turnosDias[j].mesas[k].numComensal){
          mesasVacias++;
        }
      }

      if(numComensalesTurno > numComensalesMax){
        numComensalesMax = numComensalesTurno;
        indexDiaMax = i;
        indexTurnoMax = j;
      }

      numComensalesTurno = 0;
    }

    printf("El d�a %d sobraron %d.\n", i+1, mesasVacias);
    mesasVacias = 0;
  }

  printf("El d�a %d en el turno %d tuvo el mayor n�mero de comensales con un total de %d comensales. \n", indexDiaMax+1, indexTurnoMax+1, numComensalesMax);
}

/*
(1,25 puntos) Dise�a una funci�n en lenguaje C que reciba como par�metros la estructura
anterior, el apellido de un comensal y el n�mero de turno (1, 2, 3 o 4) y escriba en un
fichero el total facturado por las mesas reservadas por dicho comensal a lo largo del mes en
dicho turno.
*/

//Precondici�n: recibir la estructura ya inicializada, cadena inicializada y el tipo de turno
//Poscondici�n: devuelve en un fichero el dinero gastado en ese turno recibido por el apellido buscado.
void facturado_reserva(diasAbiertos *diaDisponibles, const char *apellidos, tipoTurno turnoReserva){
  float totalFacturado = 0;
  FILE *f;
  f = fopen("factura.txt", "w");
  if(f == NULL){
    printf("No se pudo abrir el fichero. \n");
    exit(1);
  }

  for(int i = 0; i < N_ABIERTO; i++){ //Recorre cada d�a del mes
    for(int j = 0; j < N_TURNOS; j++){  //Recorre cada turno
      for(int k = 0; k < N_MESAS; k++){ //Recorre cada mes
        //Toma la cuenta de cada mesa si el apellido y turno coincide
        if(!strcmp(apellidos, diaDisponibles[i].turnosDias[j].mesas[k].ApellidosReserva) && diaDisponibles[i].turnosDias[j].miTurno == turnoReserva){
          totalFacturado += diaDisponibles[i].turnosDias[j].mesas[k].cuentaMesa;
        }
      }
    }
  }

  printf("%f", totalFacturado);

  if(turnoReserva == CENA){
    fprintf(f, "El cliente de apellido %s ha gastado en nuestro restaurante %f euros en turno de CENA. \n", apellidos, totalFacturado);
  } else {
    fprintf(f, "El cliente de apellido %s ha gastado en nuestro restaurante %f euros en turno de ALMUERZO. \n", apellidos, totalFacturado);
  }
  fclose(f);
}
