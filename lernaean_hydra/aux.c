/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:48:54 by acarlson          #+#    #+#             */
/*   Updated: 2019/03/07 14:13:04 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (-1);
	}
	return (0);
}
