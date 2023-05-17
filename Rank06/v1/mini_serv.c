#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct client {
	int id;
	char msg[100000];
} t_client;

t_client clients[1024];

int max = 0, next_id = 0;
fd_set active, ready_read, ready_write;
char buf_read[424242], buf_write[424242];

void exit_error(char *str)
{
	write(2, str, strlen(str));
	exit(1);
}

void send_all(int es)
{
	for(int i = 0; i <= max; i++)
	{
		if (FD_ISSET(i, &ready_write) && i != es)
			send(i, buf_write, strlen(buf_write), 0);
	}
}

int create_server_socket(struct sockaddr_in addr)
{
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
		exit_error("Fatal error\n");

	bzero(&clients, sizeof(clients));
	FD_ZERO(&active);

	max = server_socket;
	FD_SET(server_socket, &active);

	if ((bind(server_socket, (const struct sockaddr *)&addr, sizeof(addr))) < 0)
		exit_error("Fatal error\n");
	if (listen(server_socket, 128) < 0)
		exit_error("Fatal error\n");

	return server_socket;
}

int handle_new_client(int server_socket, struct sockaddr_in addr, socklen_t addr_len)
{
	int client_socket = accept(server_socket, (struct sockaddr *)&addr, &addr_len);
	if (client_socket < 0)
		return -1;
	max = (client_socket > max) ? client_socket : max;
	clients[client_socket].id = next_id++;
	FD_SET(client_socket, &active);
	sprintf(buf_write, "server: client %d just arrived\n", clients[client_socket].id);
	send_all(client_socket);
	return 0;
}

void handle_client_message(int fd)
{
	int read = recv(fd, buf_read, sizeof(buf_read) - 1, 0);
	if (read > 0) {
		buf_read[read] = '\0';
	}
	if (read <= 0)
	{
		sprintf(buf_write, "server: client %d just left\n", clients[fd].id);
		send_all(fd);
		FD_CLR(fd, &active);
		close(fd);
	}
	else
	{
		for (int i = 0, j = strlen(clients[fd].msg); i < read; i++, j++)
		{
			clients[fd].msg[j] = buf_read[i];
			if (clients[fd].msg[j] == '\n')
			{
				clients[fd].msg[j] = '\0';
				sprintf(buf_write, "client %d: %s\n", clients[fd].id, clients[fd].msg);
				send_all(fd);
				bzero(&clients[fd].msg, strlen(clients[fd].msg));
				j = -1;
			}
		}
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		exit_error("Wrong number of arguments\n");
	int port = atoi(argv[1]);

	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = (1 << 24) + 127;
	addr.sin_port = htons(port);

	int server_socket = create_server_socket(addr);

	while(1)
	{
		ready_read = ready_write = active;
		if (select(max + 1, &ready_read, &ready_write, NULL, NULL) < 0)
			continue;

		for(int fd = 0; fd <= max; fd++)
		{
			if (FD_ISSET(fd, &ready_read) && fd == server_socket)
			{
				if (handle_new_client(server_socket, addr, addr_len) < 0)
					continue;
				break;
			}
			if (FD_ISSET(fd, &ready_read) && fd != server_socket)
			{
				handle_client_message(fd);
				break;
			}
		}
	}
}