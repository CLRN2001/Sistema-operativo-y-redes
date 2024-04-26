#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 30

// Estructura para pasar argumentos a la función del hilo
typedef struct {
    int disponibilidad;
    int posicion;
} ThreadArgs;

// Función que será ejecutada por cada hilo para mostrar el estado de los asientos
void *reservacion(void *args) {
    ThreadArgs *threadArgs = (ThreadArgs *)args;

    if (threadArgs->disponibilidad == 0) {
        printf ("El asiento %d esta disponible\n", threadArgs->posicion);
    }
    else if (threadArgs->disponibilidad == 1)
        printf("El asiento %d esta reservado\n", threadArgs->posicion);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadArgs threadArgs[NUM_THREADS];
    int decision, reserva;

    //se configuran los atributos de los hilos para saber su disponibilidad y su posicion
    for (int i = 0; i < NUM_THREADS; ++i){
        threadArgs[i].disponibilidad = 0;
        threadArgs[i].posicion = i;
    }



    while (decision != 0){
      printf("Bienvenido al teadro ICB\n");
      printf("[1] Consultar estado de los asientos\n");
      printf("[2] Reservar asiento\n");
      printf("[3] Cancelar reserva\n");
      printf("[0] Salir\n");
      scanf( "%d", &decision);

      
      if (decision == 1){
        for (int i = 0; i < NUM_THREADS; ++i) {
          //Creacion de hilos
          pthread_create(&threads[i], NULL, reservacion,(void *)&threadArgs[i]);    
        }
        for (int i = 0; i < NUM_THREADS; ++i) {
          //Esperar a que cada uno termine 
          pthread_join(threads[i], NULL);
        }
      }

      else if (decision == 2){
        printf("Ingrese el numero de asiento que desea reservar:\n");
        scanf("%d", &reserva);

        
        for (int i = 0; i < NUM_THREADS; ++i){
          //Se revisan los argumentos de cada hilo para ver si esta disponible
          if (i == reserva && threadArgs[i].disponibilidad == 0){
            printf( "El asiento %d ha sido reservado con exito\n", reserva);
            threadArgs[i].disponibilidad = 1;
            i = NUM_THREADS;
          }
            
          //en caso de que el hilo/asiento no este disponible no permitira reservarlo
          else if (i == reserva && threadArgs[i].disponibilidad == 1){
            printf ("El asiento %d no esta disponible, intente con otro\n", reserva);
            i = NUM_THREADS;
          }
        }
      }

      else if (decision == 3){
        printf( "Ingrese el numero de asiento que desea cancelar:\n");
        scanf( "%d", &reserva);

        
        for (int i = 0; i < NUM_THREADS; ++i){
          //Se revisan los argumentos en este caso para cancelar la reserva
          if (reserva == i && threadArgs[i].disponibilidad == 1){
            printf( "El asiento %d ha sido cancelado con exito\n", reserva);
            threadArgs[i].disponibilidad = 0;
            i = NUM_THREADS;
          }

          //esto permite que solo asientos reservados sean cancelados
          else if (reserva == i && threadArgs[i].disponibilidad == 0){
            printf ("El asiento %d esta disponible\n", reserva);
            i = NUM_THREADS;
          }
        }
      }

      else if (decision == 0)
        return 0;

      else
        printf ("Ingrese una opcion valida\n");

    }


    return 0;
}
