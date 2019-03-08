/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:31:10 by acarlson          #+#    #+#             */
/*   Updated: 2019/03/08 00:52:49 by john             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

struct sockaddr_in				g_client;

/*
** Bind the sock, assigning and address and port number to it.
*/

void	bind_sock(int sock, int addr, struct sockaddr_in server)
{
	struct sockaddr		*a;

	a = (struct sockaddr *)&server;
	server.sin_family = PF_INET;
	server.sin_addr.s_addr = addr;
	server.sin_port = htons(PORT);
	if (bind(sock, a, sizeof(server)) < 0)
	{
		ft_putstr_fd("Unable to bind sock\n", FT_STDERR_FILENO);
		exit(1);
	}
}

int	accept_conn(struct sockaddr_in *client, int sock_s)
{
	int		len;
	int		sock_c;

	len = sizeof(struct sockaddr_in);
	if ((sock_c = accept(sock_s, (struct sockaddr *)client, \
								(socklen_t*)&len)) < 0)
		return (BAD_CONN);
	return (sock_c);
}

void	read_client(int sock_c)
{
	int		read_size;
	char	msg[BUFF_SIZE];

	while ((read_size = recv(sock_c, msg, BUFF_SIZE, 0)) > 0)
	{
		if (!ft_strcmp(msg, "EOF\n"))
			break ;
		ft_putstr_fd("pong\n", sock_c);
		ft_putstr_fd("pong\n", sock_c);
		ft_bzero(msg, BUFF_SIZE);
	}
}

int			setup_server(void)
{
	int						sock_s;
	int						sock_c;
	struct sockaddr_in		server;
	struct sockaddr_in		client;

	if ((sock_s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exit(1);
	bind_sock(sock_s, INADDR_ANY, server);
	listen(sock_s, BACKLOG);
	while (1)
	{
		if ((sock_c = accept_conn(&client, sock_s)) != BAD_CONN)
		{
			read_client(sock_c);
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
	// close(STDIN_FILENO);
	// close(FT_STDOUT_FILENO_FILENO);
	// close(STDERR_FILENO);
	setup_server();
}
