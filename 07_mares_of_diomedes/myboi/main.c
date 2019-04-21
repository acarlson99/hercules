#include <stdio.h>
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
	free(str);
}

// mlp ascii art
// curl luigi
// listen to literally all available sockets
// mess with stty

int forkyboi() {
	int		pid;
	int		sid;
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0) {
		printf("PARENT PROCESS\n");
		while (1);
	}
	sid = setsid();
	if (sid < 0)
		exit(1);

	random_pname();

	while (1);
	// forkyboi();
	return (0);
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	sigset_t	mask;

	random_pname();
	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);	// ignore signals

	forkyboi();
}
