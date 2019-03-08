/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:31:10 by acarlson          #+#    #+#             */
/*   Updated: 2019/03/07 16:21:21 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			create_socket(void)
{
	int		s;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exit(1);
	return (s);
}

void		listen_loop(struct sockaddr_in *server, struct sockaddr_in *client)
{
	(void)server;
	(void)client;
	while (1);
}

int			main(int argc, char **argv)
{
	pid_t					pid;
	pid_t					sid;
	int						d;
	struct sockaddr_in		server;
	struct sockaddr_in		client;

	(void)server;
	(void)client;
	if ((d = read_args(argc, argv)) < 0)
		exit(1);
	pid = 0;
	sid = 0;
	if (d)
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
	listen_loop(&server, &client);
}
