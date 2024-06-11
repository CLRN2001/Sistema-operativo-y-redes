#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *mensaje = "Hola Servidor";
    char buffer[BUFFER_SIZE] = {0};

    // Crear el socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error en la creacion del socket \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir direcciones IPv4 e IPv6 de texto a binario
    if (inet_pton(AF_INET, "", &serv_addr.sin_addr) <= 0) {
        printf("\nError en la direccion \n");
        return -1;
    }

    // Conectar al servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConeccion fallida \n");
        return -1;
    }

    // Enviar un mensaje al servidor
    send(sock, mensaje, strlen(hello), 0);
    printf("Mensaje enviado\n");

    // Leer la respuesta del servidor
    valread = read(sock, buffer, BUFFER_SIZE);
    printf("Servidor: %s\n", buffer);

    // Cerrar el socket
    close(sock);
    return 0;
}