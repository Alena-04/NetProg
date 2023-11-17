#include <iostream>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

int main() {
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        cerr << "Ошибка при создании сокета" << endl;
        return 1;
    }

    sockaddr_in serverAddress;
 	memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(44214);

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
		cerr << "Ошибка связывания сокета с адресом" << endl;
        return 1;
    }

    while (true) {
        char buffer[1024];
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr *) &clientAddress, &clientAddressLength);

        if (bytesRead > 0) {
            time_t currentTime = time(nullptr);
            struct tm *localTime = localtime(&currentTime);
            char timeStr[128];
            strftime(timeStr, sizeof(timeStr), "%d.%m.%Y %H:%M:%S", localTime);

            sendto(serverSocket, timeStr, strlen(timeStr), 0, (struct sockaddr *) &clientAddress, clientAddressLength);
        }
    }

    close(serverSocket);

    return 0;
}
