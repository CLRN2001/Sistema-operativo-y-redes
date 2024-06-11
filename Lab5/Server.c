#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *mensaje = "Hola Cliente";

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("error del socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección y puerto del servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Asociar el socket al puerto
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("error en el puerto");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Poner el socket en modo escucha
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("El servidor escucha en el puerto %d\n", PORT);

    // Aceptar una conexión entrante
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Leer datos del cliente
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Mensaje del cliente: %s\n", buffer);

    // Enviar una respuesta al cliente
    send(new_socket, mensaje, strlen(hello), 0);
    printf("Mensaje enviado\n");

    // Cerrar el socket
    close(new_socket);
    close(server_fd);
    return 0;
}