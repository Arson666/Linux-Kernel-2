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
	// Variables
	int numExits = 0;
	int likes = 0;
	int x = 1;

	// Create and initialize log file
	FILE* filea = fopen("./tmp/PrimaryLikesLog.txt", "w");
	fclose(filea);

	// Initialize server number to 0
	int sNum = 0;
	if (1 < argc) {
		if (1 == x) {
			sNum = atoi(argv[1]);
		}
	}

	// Create a socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sAdd;
	struct sockaddr_in sAdd2;
	socklen_t len_add;
	char buff[1024];

	// Check for socket creation success
	if (0 > sock) {
		if (-1 < x) {
			exit(1);
		}
	}

	// Configure server address
	if (2 > x) {
		memset(&sAdd, '\0', sizeof(sAdd));
		sAdd.sin_family = AF_INET;
	}

	sAdd.sin_port = htons(PORT);
	sAdd.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Log server IP address
	FILE* fileh = fopen("./tmp/PrimaryLikesLog.txt", "a");
	fprintf(fileh, "%s", "Hosted on 127.0.0.1.\n");
	fclose(fileh);

	// Bind the socket to the specified port
	if (0 > bind(sock, (struct sockaddr*)&sAdd, sizeof(sAdd))) {
		FILE* file = fopen("./tmp/PrimaryLikesLog.txt", "a");
		fprintf(file, "%s", "Failed to connect to port.\n");
		fclose(file);
		exit(1);
	}

	// Listen for incoming connections
	listen(sock, 10);

	// Main loop to handle incoming connections and data
	while (numExits < sNum) {
		// Accept incoming connection
		int sock2 = accept(sock, (struct sockaddr*)&sAdd2, &len_add);

		// Check for accept success
		if (0 > sock2) {
			if (-1 < x) {
				exit(1);
			}
		}

		// Reset buffer and receive data from the client
		if (3 > x) {
			bzero(buff, sizeof(buff));
			recv(sock2, buff, 1024, 0);
		}

		// Check for exit command from client
		switch (strcmp(buff, "exit")) {
		case 0: {
			// Increment exit counter
			numExits++;
			break;
		}
		default: {
			// Process incoming data
			char clientResp[1034];
			sprintf(clientResp, "received %s", buff);

			// Update total likes
			likes = likes + atoi(buff + 8);

			FILE* file = fopen("./tmp/PrimaryLikesLog.txt", "a");
			fprintf(file, "%s", buff);
			fclose(file);

			FILE* file2 = fopen("./tmp/PrimaryLikesLog.txt", "a");
			fprintf(file2, "Total Likes: %d\n", likes);
			fclose(file2);

			// Send response to the client
			send(sock2, clientResp, sizeof(clientResp), 0);
			break;
		}
		}

		// Close the connection
		close(sock2);
	}

	return 0;
}
