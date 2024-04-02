#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <syslog.h>
#include "daemon.h"

/**
 * daemon_init() - Initialize daemon process.
 *
 * Return: Error code on failure, otherwise 0.
 */
int daemon_init()
{
	int max_fd;
	int fd;
	pid_t pid;

	pid = fork();

	if (pid < 0)
		exit(EXIT_FAILURE);

	if (pid > 0)
		exit(EXIT_SUCCESS);

	if (setsid() < 0)
		exit(EXIT_FAILURE);

	pid = fork();

	if (pid < 0)
		exit(EXIT_FAILURE);

	if (pid > 0)
		exit(EXIT_SUCCESS);

	umask(0);

	chdir("/");

	for (max_fd = sysconf(_SC_OPEN_MAX); max_fd >= 0; max_fd--) {
		close(max_fd);
	}
	close(STDIN_FILENO);
	fd = open("/dev/null", O_RDWR);
	if (fd != 0)
		return -1;
	if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
		return -2;
	if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
		return -3;

	return 0;
}