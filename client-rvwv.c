#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int BUFFER_SIZE = 8;
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(9010);

	int connection_status = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	if (connection_status == -1)
	{
		printf("\nError Connecting to Server\n");
		exit(1);
	}

	char buff[256];

	read(client_socket, buff, sizeof(buff));
	printf("\nmessage received from server : %s\n", buff);

	char mybuf1[BUFFER_SIZE], mybuf2[BUFFER_SIZE];
	struct iovec iov[2];
	iov[0].iov_base = mybuf1;
	iov[0].iov_len = BUFFER_SIZE;
	iov[1].iov_base = mybuf2;
	iov[1].iov_len = BUFFER_SIZE;

	while (1)
	{
		ssize_t n = readv(STDIN_FILENO, iov, 2);
		if (n < 0)
		{
			fprintf(stderr, "Failed to read input from stdin: %s\n", strerror(errno));
			return 1;
		}

		if (n == 0)
		{
			break;
		}

		if (writev(client_socket, iov, 2) < 0)
		{
			fprintf(stderr, "Failed to write to socket: %s\n", strerror(errno));
			return 1;
		}
	}

	close(client_socket);
}
