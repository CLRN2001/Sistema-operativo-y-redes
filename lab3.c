#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_THREADS 30

// Estructura del hilo
typedef struct {
  int disponibilidad;
  int posicion;
} ThreadArgs;

//Subproceso encargado de mostrar el estado de los asientos
void *comprobacion(void *args) {
  ThreadArgs *threadArgs = (ThreadArgs *)args;

  if (threadArgs->disponibilidad == 0) {
    printf("El asiento %d esta disponible\n", threadArgs->posicion);
  } else if (threadArgs->disponibilidad == 1)
    printf("El asiento %d esta reservado\n", threadArgs->posicion);

  pthread_exit(NULL);
}

//Subproceso encargado de reservar los asientos
void *reservacion(void *args) {
  ThreadArgs *threadArgs = (ThreadArgs *)args;

  if (threadArgs->disponibilidad == 0) {
    printf("El asiento %d ha sido reservado con exito\n", threadArgs->posicion);
    threadArgs->disponibilidad = 1;
  } else if (threadArgs->disponibilidad == 1)
    printf("El asiento %d no esta disponible, intente con otro\n",
           threadArgs->posicion);
  pthread_exit(NULL);
}

//Subproceso encargado de cancelar los asientos
void *cancelacion(void *args) {
  ThreadArgs *threadArgs = (ThreadArgs *)args;

  if (threadArgs->disponibilidad == 1) {
    printf("El asiento %d ha sido cancelado con exito\n", threadArgs->posicion);
    threadArgs->disponibilidad = 0;
  } else if (threadArgs->disponibilidad == 0)
    printf("El asiento %d esta disponible\n", threadArgs->posicion);

  pthread_exit(NULL);
}

int main() {
  pthread_t threads[NUM_THREADS];
  ThreadArgs threadArgs[NUM_THREADS];
  int decision, reserva;

  for (int i = 0; i < NUM_THREADS; ++i) {
    threadArgs[i].disponibilidad = 0;
    threadArgs[i].posicion = i;
  }

  while (decision != 0) {
    printf("Bienvenido al teatro ICB\n");
    printf("[1] Consultar estado de los asientos\n");
    printf("[2] Reservar asiento\n");
    printf("[3] Cancelar reserva\n");
    printf("[0] Salir\n");
    scanf("%d", &decision);

    if (decision == 1) {
      for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, comprobacion, (void *)&threadArgs[i]);
      }
      for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
      }
    }

    else if (decision == 2) {
      printf("Ingrese el numero de asiento que desea reservar:\n");
      scanf("%d", &reserva);
      
      if (reserva > 29){
        printf("Error en el numero de asiento (0-29)");
        break;
      }

      for (int i = 0; i < NUM_THREADS; ++i) {
        if (i == reserva) {
          pthread_create(&threads[i], NULL, reservacion,(void *)&threadArgs[i]);
          pthread_join(threads[i], NULL);
          i = NUM_THREADS;
        }
      }
    }

    else if (decision == 3) {
      printf("Ingrese el numero de asiento que desea cancelar:\n");
      scanf("%d", &reserva);
      if (reserva > 29){
        printf("Error en el numero de asiento (0-29)");
        break;
      }
      
      for (int i = 0; i < NUM_THREADS; ++i) {
        if (i == reserva) {
          pthread_create(&threads[i], NULL, cancelacion,(void *)&threadArgs[i]);
          pthread_join(threads[i], NULL);
          i = NUM_THREADS;
        }
      }
    }

    else if (decision == 0)
      return 0;

    else
      printf("Ingrese una opcion valida\n");
  }

  return 0;
}
