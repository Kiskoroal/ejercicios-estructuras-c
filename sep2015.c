#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
1.- (2,5 puntos) Una compañía de seguros desea almacenar los datos de todas las ventas
realizadas en un mes por la empresa. De cada póliza vendida se quiere almacenar el nº de
póliza, el código del vendedor (alfanumérico de 9 caracteres), el dni del cliente y la prima
total del seguro. Los vendedores tienen un sueldo básico de 700€ mensuales y una comisión
del 1,25% del total de la prima de cada póliza vendida si superan un determinado número de
pólizas. Suponemos que el máximo de pólizas en un mes es de 100.
*/

#define N_POLIZAS 100
#define N_MES 12
#define COMISION 1.25
#define SUELDO_BASE 700.0

typedef struct{
  int numPoliza;
  char codigoVendedor[10];
  char dni[10];
  float primaTotalSeguro;
}polizas;

typedef struct{
  polizas polizaMes[N_POLIZAS];
}conjunto_polizas;

float calcular_comision(conjunto_polizas *, const char *, int );
void poliza_mayor(conjunto_polizas *);
float almacenar_polizas(conjunto_polizas *, int );

int main(){
  return 0;
}

/*
Escribe en pseudocódigo una función que reciba la estructura anterior y devuelva el total
de ingresos en euros por seguros vendidos en el mes por la empresa
*/

float almacenar_polizas(conjunto_polizas *polizasEnMeses, int mes){
  float primaTotal = 0;
  for(int j = 0; j < N_POLIZAS; j++){
    primaTotal += polizasEnMeses[mes-1].polizaMes[j].primaTotalSeguro;
  }

  return primaTotal;
}

/*
Escribe un procedimiento en pseudocódigo que reciba la estructura de datos y escriba la
póliza de mayor prima indicando cual es el número de póliza y cuál es el código de vendedor
que realizó la venta (Suponemos que solo habrá una póliza de mayor prima)

*/

void poliza_mayor(conjunto_polizas *polizasEnMeses){
  float primaMax = 0;
  int indexPrimaMax, indexDiaMaxPrima;

  for(int i = 0; i < N_MES; i++){
    for(int j = 0; j < N_POLIZAS; j++){
      if(polizasEnMeses[i].polizaMes[j].primaTotalSeguro >= primaMax){
        primaMax = polizasEnMeses[i].polizaMes[j].primaTotalSeguro;
        indexPrimaMax = j;
        indexDiaMaxPrima = i;
      }
    }
  }

  printf("La póliza con mayor prima se vendio el día %d por el vendedor de código %s y número de poliza %d", indexDiaMaxPrima+1, polizasEnMeses[indexDiaMaxPrima].polizaMes[indexPrimaMax].codigoVendedor, polizasEnMeses[indexDiaMaxPrima].polizaMes[indexPrimaMax].numPoliza);
}

/*
d) Implementa una función en C que reciba la estructura y un código de vendedor y devuelva
el sueldo del mes teniendo en cuenta que si ha realizado menos de 10 pólizas sólo cobrará el
sueldo base y si ha superado las 10 pólizas cobrará el sueldo base más el 1,25% de comisión
de cada póliza.
*/
float calcular_comision(conjunto_polizas *polizasEnMes, const char *codigoVendedor, int mes){
  float comision = 0;
  int numVentas = 0;
  for(int i = 0; i < N_POLIZAS; i++){
    if(!strcmp(polizasEnMes[mes-1].polizaMes[i].codigoVendedor, codigoVendedor)){
      numVentas++;
      comision += polizasEnMes[mes-1].polizaMes[i].primaTotalSeguro;
    }
  }

  if(numVentas > 10)
    comision *= COMISION;

  return comision + SUELDO_BASE;
}

