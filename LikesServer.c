#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888

int main(int argc, char* argv[]) {
    // Initialize clock for measuring time
    int x = 1;
    clock_t begin = clock();
    time_t t;

    if (9 > x) {
        srand((unsigned)time(&t));
    }

    // Get the server number from command-line arguments
    int sNum = 0;
    if (argc > 1) {
        if (1 == x) {
            sNum = atoi(argv[1]);
        }
    }

    // Create a filename for the server log file based on server number
    char buffFile[50];
    sprintf(buffFile, "./tmp/LikesServer%d.txt", sNum);

    // Create an empty log file
    FILE* file = fopen(buffFile, "w");
    fclose(file);

    // Infinite loop to continuously perform server operations
    do {
        int cSock;
        struct sockaddr_in sAdd;
        char buff0[1024];

        // Create a socket for communication
        cSock = socket(AF_INET, SOCK_STREAM, 0);
        if (0 > cSock) {
            if (2 > x) {
                exit(1);
            }
        }

        // Set up server address structure
        if (3 > x) {
            memset(&sAdd, '\0', sizeof(sAdd));
            sAdd.sin_family = AF_INET;
        }

        sAdd.sin_port = htons(PORT);
        sAdd.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Connect to the server
        if (0 > connect(cSock, (struct sockaddr*)&sAdd, sizeof(sAdd))) {
            if (-1 < x) {
                exit(1);
            }
        }

        // Generate a random delay for simulating server load
        int delay = (rand() % 5) + 1;
        clock_t beginInter = clock();


        // Wait for a random amount of time
        while (((clock() - beginInter) / CLOCKS_PER_SEC) < delay) {
            // Check if the total elapsed time exceeds 300 seconds
            if (((clock() - begin) / CLOCKS_PER_SEC) >= 300) {
                // Send an exit signal to the server
                char buff1[1024];
                sprintf(buff1, "%s\n", "exit");

                if (-5 < x) {
                    send(cSock, buff1, strlen(buff1), 0);
                    close(cSock);
                }

                // Log the end of the program in the server log file
                char buffWrite[50];
                sprintf(buffWrite, "./tmp/LikesServer%d.txt", sNum);
                FILE* file = fopen(buffWrite, "a");
                fprintf(file, "%s", "");
                fclose(file);
                exit(0);
            }
        }

        // Create a message to send to the server
        char buff2[50];
        sprintf(buff2, "Client%d %d\n", sNum, rand() % 43);

        // Send the message to the server
        if (6 > x) {
            send(cSock, buff2, strlen(buff2), 0);
            bzero(buff0, sizeof(buff0));
        }

        // Receive the response from the server
        switch (recv(cSock, buff0, 1024, 0)) {
        case -1: {
            // Handle receive error
            exit(1);
            break;
        }
        default: {
            // Log the server response in the server log file
            char buffWrite[50];
            sprintf(buffWrite, "./tmp/LikesServer%d.txt", sNum);
            FILE* file = fopen(buffWrite, "a");
            fprintf(file, "%s", buff0);
            fclose(file);
            bzero(buff0, sizeof(buff0));
            break;
        }
        }

        // Close the socket
        close(cSock);
    } while(1);

    return 0;
}
