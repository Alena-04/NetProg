#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cerr << "Ошибка при создании сокета" << endl;
        return 1;
    }

    sockaddr_in serverAddress;
    std::memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(7777);

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "Ошибка связывания сокета с адресом" << endl;
        return 1;
    }

    if (listen(serverSocket, 5) < 0) {
        cerr << "Ошибка прослушивания сокета" << endl;
        return 1;
    }

    while (true) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket < 0) {
            cerr << "Ошибка при принятии соединения" << endl;
            return 1;
        }

        char buffer[1025];  // 
        int bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);  
        if (bytesRead < 0) {
            cerr << "Ошибка при чтении данных" << endl;
            return 1;
        }

        buffer[bytesRead] = '\0'; 

        cout << "Получено сообщение от клиента: " << buffer << endl;

        int bytesWritten = write(clientSocket, buffer, bytesRead);
        if (bytesWritten < 0) {
            cerr << "Ошибка при записи данных" << endl;
            return 1;
        }

        close(clientSocket);
    }

    close(serverSocket);

    return 0;
}
