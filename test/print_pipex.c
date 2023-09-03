
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#include <stdio.h>

void ft_print_pipex(t_pipex	*pipex)
{
	printf(RED "Pipex (" YELLOW "%p" RED ") values:\n" RESET, pipex);
	printf(RED "\tpipe[0]: " YELLOW "%d\n" RESET, pipex->pipe[0]);
	printf(RED "\tpipe[1]: " YELLOW "%d\n" RESET, pipex->pipe[1]);
	printf(RED "\tpid[0]:\n" RESET);
	printf(RED "\t\tid: " YELLOW "%d\n" RESET, pipex->pid[0].id);
	printf(RED "\t\tstatus: " YELLOW "%d\n" RESET, pipex->pid[0].status);
	printf(RED "\tpid[1]:\n" RESET);
	printf(RED "\t\tid: " YELLOW "%d\n" RESET, pipex->pid[1].id);
	printf(RED "\t\tstatus: " YELLOW "%d\n" RESET, pipex->pid[1].status);
	printf(RED "\tinfile: " YELLOW "%d\n" RESET,pipex->infile);
	printf(RED "\toutfile: " YELLOW "%d\n" RESET,pipex->outfile);
	printf(RED "\tpath: " YELLOW "(%p)\n" RESET,pipex->path);
	for (int i = 0; pipex->path && pipex->path[i]; i++)
		printf(RED "\t\t%2d: " YELLOW "(%p) \"%s\"\n" RESET,i, pipex->path[i], pipex->path[i]);
	printf(RED "\tcommand:\n" RESET);
	printf(RED "\t\tpath: " YELLOW "(%p) \"%s\"\n" RESET, pipex->command.path, pipex->command.path);
	printf(RED "\t\tcmd: " YELLOW "(%p)\n" RESET,pipex->command.cmd);
	for (int i = 0; pipex->command.cmd && pipex->command.cmd[i]; i++)
		printf(RED "\t\t%2d: " YELLOW "(%p) \"%s\"\n" RESET,i, pipex->command.cmd[i], pipex->command.cmd[i]);
	printf("\n");
}