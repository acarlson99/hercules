/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:31:10 by acarlson          #+#    #+#             */
/*   Updated: 2019/03/07 17:30:10 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>	// TODO: remove

int			create_socket(void)
{
	int		s;

	printf("Creating socket\n");
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exit(1);
	return (s);
}

void		listen_loop(int socket, int daemon)
{
	struct sockaddr_in				server;
	struct sockaddr_in				client;

	(void)socket;
	(void)daemon;
	(void)server;
	(void)client;
	// listen on port PORT
	// accept connection
	// pong back
	// drop connection
	while (1)
	{
	}
}

int			main(int argc, char **argv)
{
	static pid_t		pid;
	static pid_t		sid;
	int					daemon;
	int					socket;

	if ((daemon = read_args(argc, argv)) < 0)
		exit(1);
	socket = create_socket();
	if (daemon)
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid > 0)
			exit(0);
		sid = setsid();
		if (sid < 0)
			exit(1);
	}
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDERR_FILENO);
	listen_loop(socket, daemon);
}
