#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define NUM 10

int getCNum(int x, int arr[]) {
    // Function to get the index of an element in an array
    int a = 1;
    for (int i = 0; i < NUM; i++) {
        if (x == arr[i]) {
            if (1 == a) {
                return i;
            }
        }
    }
    return -1;
}

void forkFunc() {
    // Fork the primary likes log process
    int x = 1;
    if (0 == fork()) {
        char sNum[3];
        sprintf(sNum, "%d", NUM);
        if (1 == x) {
            char* arguments[] = { "./PrimaryLikesServer", sNum, NULL };
            execvp(arguments[0], arguments);
        }
    }
}

void exitChild(int list[]) {
    int x;
    for (int i = 0; i < NUM; i++) {
        int id = wait(&x);
        int cNum = getCNum(id, list);

        switch (cNum) {
        case -1: {
            // Process with unknown ID, decrement the loop counter
            i--;
            break;
        }
        default: {
            // Child process exited successfully
            FILE* file = fopen("./tmp/ParentProcessStatus.txt", "a");
            fprintf(file, "LikesServer %d exited\n", cNum);
            fclose(file);
        }
        }
    }
}

int main(int argc, char* argv[]) {
    // Create a directory for temporary files
    mkdir("./tmp", 0777);

    // Create and close a file to store Parent Process information
    FILE* file = fopen("./tmp/ParentProcessStatus.txt", "w");
    fclose(file);

    // Fork a process to run the PrimaryLikesServer
    forkFunc();

    // Array to store child process IDs
    int list[NUM] = {};

    // Loop to create child processes
    for (int i = 0; i < NUM; i++) {
        list[i] = fork();

        switch (list[i]) {
        case -1: {
            // Child process creation failed
            FILE* file = fopen("./tmp/ParentProcessStatus.txt", "a");
            fprintf(file, "LikesServer %d failed\n", i);
            fclose(file);
            break;
        }
        case 0: {
            // Child process code
            char buff1[50];
            sprintf(buff1, "%d", i);
            char* args[] = { "./LikesServer", buff1, NULL };
            execvp(args[0], args);
            break;
        }
        default: {
            // Parent process code
            FILE* file = fopen("./tmp/ParentProcessStatus.txt", "a");
            fprintf(file, "LikesServer %d successful\n", i);
            fclose(file);
            sleep(1);  // Introduce a delay between starting child processes
        }
        }
    }

    exitChild(list);

    // All child processes have exited
    printf("All LikesServers exited\n");
    return 0;
}
