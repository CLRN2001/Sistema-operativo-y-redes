#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PUERTO 8080
#define BUF_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};
    const char *mensaje = "Hola, servidor!\n";

    // Crear el socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PUERTO);

    // Convertir direcciones IPv4 e IPv6 de texto a binario
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Dirección no válida/ no soportada");
        exit(EXIT_FAILURE);
    }

    // Conectar al servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error en connect");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Leer mensaje de bienvenida del servidor
    int valread = read(sock, buffer, BUF_SIZE);
    if (valread > 0) {
        printf("Mensaje recibido del servidor: %s\n", buffer);
    }

    // Enviar mensaje al servidor
    send(sock, mensaje, strlen(mensaje), 0);
    printf("Mensaje enviado al servidor\n");

    // Cerrar el socket
    close(sock);

    return 0;
}
