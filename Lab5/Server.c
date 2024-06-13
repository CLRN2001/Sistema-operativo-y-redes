#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PUERTO 8080
#define BUF_SIZE 1024

int main() {
    struct sockaddr_in address;
    int server_fd;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0};
    const char *mensaje = "Bienvenido al servidor\n";

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Adjuntar el socket al puerto 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Error en setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PUERTO);

    // Vincular el socket al puerto especificado
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error en bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(server_fd, 1) < 0) {
        perror("Error en listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d\n", PUERTO);

    int new_socket;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0){
	perror("accept");
	close(server_fd);
	exit(EXIT_FAILURE);
	}
    // Leer el mensaje del cliente
    int valread = read(new_socket, buffer, BUF_SIZE);
    if (valread > 0) {
        printf("Mensaje recibido del cliente: %s\n", buffer);
    }

    // Enviar mensaje de vuelta
    send(new_socket, buffer, BUF_SIZE, 0);
    printf("Mensaje de vuelta enviado\n");

    // Cerrar los sockets
    close(new_socket);
    close(server_fd);
    return 0;
}
