/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:04:33 by acarlson          #+#    #+#             */
/*   Updated: 2019/05/17 17:23:58 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  make socket
  bind socket to port
  listen on port
  accept connection
  parse request
  make socket
  connect socket to target
  send data to target
  get reply
  send reply to receiver
  close connections
*/

#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BACKLOG 5

int sock_s;
int sock_c;

void	cleanup(int a) {
	(void)a;
	close(sock_s);
	close(sock_c);
	exit(1);
}

int		main(int argc, char **argv)
{
	struct sockaddr_in	server;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "usage: ./proxy port_nbr\n");
		exit(1);
	}
	if ((sock_s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		dprintf(STDERR_FILENO, "Error opening socket");
		exit(1);
	}
	server.sin_family = PF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));
	if (bind(sock_s, (struct sockaddr *)&server, sizeof(server)))
	{
		close(sock_s);
		dprintf(STDERR_FILENO, "Unable to bind socket\n");
		exit(1);
	}
	signal(SIGINT, &cleanup);
	listen(sock_s, BACKLOG);
	while (1)
	{
		size_t len = sizeof(struct sockaddr);

		if ((sock_c = accept(sock_s, (struct sockaddr *)&server, (socklen_t *)&len)) < 0) {
			// stuck here always
			dprintf(STDERR_FILENO, "Unable to create socket\n");
			printf("CONT\n");
			continue ;
		}
		size_t msglen;
		char msg[2049] = { 0 };
		msg[2048] = '\0';
		// send to google
		while ((msglen = recv(sock_c, msg, 2048, 0)) > 0) {
			dprintf(sock_c, "%s", msg);
			printf("%s", msg);
			printf("%zu %d %d\n", msglen, msg[msglen - 1], msg[msglen - 2]);
			if (msg[msglen - 1] == '\0' && msg[msglen - 2] == '\0') {
				printf("BREAKING\n");
				break ;
			}
		}
		// receive from google
		/* while ((msglen = recv(sock_s, msg, 2048, 0)) > 0) { */
		/* 	dprintf(sock_s, "%s", msg); */
		/* 	printf("%s", msg); */
		/* 	printf("%zu %d %d\n", msglen, msg[msglen - 1], msg[msglen - 2]); */
		/* 	if (msg[msglen - 1] == '\0' && msg[msglen - 2] == '\0') { */
		/* 		printf("BREAKING\n"); */
		/* 		break ; */
		/* 	} */
		/* } */
		shutdown(sock_c, SHUT_RDWR);
		close(sock_c);
	}
}
