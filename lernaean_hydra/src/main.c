/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:31:10 by acarlson          #+#    #+#             */
/*   Updated: 2019/03/08 03:03:35 by john             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	setup_server(int sock, int addr, struct sockaddr_in server)
{
	struct sockaddr		*saddr;

	saddr = (struct sockaddr *)&server;
	server.sin_family = PF_INET;
	server.sin_addr.s_addr = addr;
	if (bind(sock, saddr, sizeof(server)) < 0)
	{
		ft_putstr_fd("Unable to bind socket\n", STDERR_FILENO);
		ft_putstr_fd("Port is occupied\n", STDERR_FILENO);
		exit(1);
	}
}

int	setup_client(struct sockaddr_in *client, int sock_s)
{
	size_t	len;
	int		sock_c;

	len = sizeof(struct sockaddr_in);
	if ((sock_c = accept(sock_s,\
					(struct sockaddr *)client, (socklen_t*)&len)) < 0)
		return (BAD_CONN);
	return (sock_c);
}

int			run_server(void)
{
	int						sock_s;
	int						sock_c;
	struct sockaddr_in		server;
	struct sockaddr_in		client;

	if ((sock_s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exit(1);
	server.sin_port = htons(PORT);
	setup_server(sock_s, INADDR_ANY, server);
	listen(sock_s, BACKLOG);
	while (1)
	{
		if ((sock_c = setup_client(&client, sock_s)) >= 0)
		{
			ft_putstr_fd("pong\n", sock_c);
			ft_putstr_fd("pong\n", sock_c);
			shutdown(sock_c, SHUT_RDWR);
		}
	}
	return (0);
}

int			main(int argc, char **argv)
{
	static pid_t		pid;
	static pid_t		sid;
	int					daemon;

	if ((daemon = read_args(argc, argv)) < 0)
		exit(1);
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
	run_server();
}
