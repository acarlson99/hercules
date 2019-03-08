/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:48:54 by acarlson          #+#    #+#             */
/*   Updated: 2019/03/08 01:49:13 by john             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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

int			read_args(int argc, char **argv)
{
	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "-D"))
			return (1);
		ft_putstr_fd("Usage: ./hydra [-D]\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

void	ft_bzero(void *b, size_t len)
{
	while (len--)
		*((unsigned char *)b + len) = 0;
}

size_t		ft_strlen(const char *str)
{
	size_t		n;

	n = 0;
	while (str[n])
		++n;
	return (n);
}

void		ft_putstr_fd(char const *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
