#include <stdio.h>
#include <stdlib.h>
/*
Un restaurante tiene interés en informatizar las reservas de su comedor. Debido al protocolo
COVID-19 el número de mesas y comensales está limitado y el restaurante ha decidido
establecer cuatro turnos de comida para compensar las pérdidas del negocio. Los dos primeros
turnos son para el horario de comidas y los dos últimos para el horario de cenas. El número
máximo de mesas que se pueden ocupar en cada turno es de 25.
Cuando se realiza una reserva, se deberá indicar el turno que se desea (1º, 2º, 3º o 4º). Si quedan
mesas disponibles según las preferencias del cliente, el “maitre” realizará la reserva
almacenando para esa mesa y turno, el nombre y apellidos del comensal que realiza la reserva,
el número de teléfono y el número total de comensales. Al finalizar el servicio, se almacenará
también el importe de la factura de la mesa.
El gestor del restaurante desea tener almacenada la información de las reservas realizadas por
cada día del mes (suponiendo un mes de 30 días y que el restaurante no cierra nunca). Se supone
que al comenzar el mes todas las mesas de todos los turnos se inicializan poniendo el número de
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
(1,25 puntos) Diseña un procedimiento en pseudocódigo que reciba como parámetro la
estructura diseñada en el apartado anterior y escriba cual es el día del mes y en qué tipo de
turno (comida o cena) ha habido mayor número de comensales. El procedimiento también
deberá escribir por pantalla el número de mesas que se han quedado libres por día y turno
(1, 2, 3 o 4).
*/

//Precondición recibir la estructura ya inicializada
//Poscondición: imprimir turno y dia con mas comensales además de mesas vacias en cada día.
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

    printf("El día %d sobraron %d.\n", i+1, mesasVacias);
    mesasVacias = 0;
  }

  printf("El día %d en el turno %d tuvo el mayor número de comensales con un total de %d comensales. \n", indexDiaMax+1, indexTurnoMax+1, numComensalesMax);
}

/*
(1,25 puntos) Diseña una función en lenguaje C que reciba como parámetros la estructura
anterior, el apellido de un comensal y el número de turno (1, 2, 3 o 4) y escriba en un
fichero el total facturado por las mesas reservadas por dicho comensal a lo largo del mes en
dicho turno.
*/

//Precondición: recibir la estructura ya inicializada, cadena inicializada y el tipo de turno
//Poscondición: devuelve en un fichero el dinero gastado en ese turno recibido por el apellido buscado.
void facturado_reserva(diasAbiertos *diaDisponibles, const char *apellidos, tipoTurno turnoReserva){
  float totalFacturado = 0;
  FILE *f;
  f = fopen("factura.txt", "w");
  if(f == NULL){
    printf("No se pudo abrir el fichero. \n");
    exit(1);
  }

  for(int i = 0; i < N_ABIERTO; i++){ //Recorre cada día del mes
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
