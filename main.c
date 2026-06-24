#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void notify(const char *message) {
    printf("PS5 Notification: %s\n", message);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9090);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    
    notify("VoxManager Ready on Port 9090");

    while(1) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) continue;

        memset(buffer, 0, 1024);
        read(client_socket, buffer, 1024);

        if (strncmp(buffer, "shutdown", 8) == 0) {
            notify("System Shutdown Requested...");
        } else if (strncmp(buffer, "robo", 4) == 0) {
            notify("Entering Rest Mode...");
        }

        close(client_socket);
    }
    return 0;
}

