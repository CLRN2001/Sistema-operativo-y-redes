#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int stop;
    char pid[10];
    //Creamos una variable pid_t lo cual representara un Pid siendo un int.
    pid_t process;

    //Se crea mediante el uso de fork() un proceso hijo, tendra un valor de 0 o mayor que 0 si es el padre
	process = fork(); 

    // Mediante este if se puede distinguir que proceso se esta produciendo (si el padre o el hijo).
    if (process == 0){
		printf("proceso hijo ["); 
        printf("hijo: pid es %d]\n", getpid());
        printf("Ingrese el comando que desea realizar:\n");
    }

    else{
		printf("proceso padre [");
        printf("padre: pid es %d]\n", getpid());
        //con esta pausa podemos recordar los Pid del padre e hijo asi poder usar kill mas adelante
        //sleep(15);

        printf("(1) Ejemplo de exit()\n");
        printf("(2) Ejemplo de abort()\n");
        printf("(3) Ejemplo de kill()\n");
        printf("(4) Ejemplo de ps()\n");
        printf("(5) Ejemplo de pstree()\n");
        scanf("%d", &stop);

        if(stop == 1){
            //Con esto terminara el programa al salir y entregar un int 0
            printf("Adios!\n");
            exit(0);
        }
        else if(stop == 2){
            //A continuacion se generara un error de core dumped por el aborto\n
            abort();

        }
        else if(stop == 3){
            //Con este if convertimos nuestro pid en una variable tipo char para asi ejecutar un execlp que mate al proceso padre
            sprintf(pid, "%d", getpid());
            execlp("kill", "kill", "-9", pid, NULL);
 
        }
        else if(stop == 4){
            //Con este execlp ejecutamos un ps para asi ver los procesos de manera detallada
            execlp("ps", "ps", NULL);
            
        }
        else if(stop == 5){
            //Con este execlp ejecutamos un pstree que este ordenado segun los Pid asi buscar el proceso padre e hijo y comprobar su relacion.     
            execlp("pstree","pstree", "-pn",NULL);
    
            }
    }
    
    
    return 0;   
}
