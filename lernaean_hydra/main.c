/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:31:10 by acarlson          #+#    #+#             */
/*   Updated: 2019/03/07 12:42:47 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

int			ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
		{
			return ((unsigned char)*s1 - (unsigned char)*s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

int			create_socket(void)
{
	int		s;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exit(1);
	return (s);
}

void		listen_loop(int pid, int sid, int d)
{
	(void)pid;
	(void)sid;
	(void)d;
	while (1);
}

int			read_args(int argc, char **argv)
{
	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "-D"))
			return (1);
		return (-1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	pid_t		pid;
	pid_t		sid;
	int			d;

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
	listen_loop(pid, sid, d);
}
