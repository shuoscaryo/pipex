/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_comentado.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:09:57 by orudek            #+#    #+#             */
/*   Updated: 2023/08/15 20:13:15 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

static void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
	{
	printf(BLUE "[FT_FREE_ARRAY] " GREEN "Null pointer: no need\n"RESET);
		return ;
	}
	printf(BLUE "[FT_FREE_ARRAY] " GREEN "Strings freed: "RESET);
	while(array[i] != NULL)
	{
		printf(CYAN"\tPosition %d\n"RESET, i);
		free(array[i++]);
	}
	printf(BLUE "[FT_FREE_ARRAY] " GREEN "String pointer freed\n"RESET);
	free(array);
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (cmd->path)
		free(cmd->path);
	ft_free_array(cmd->command);
}

char	ft_free_pipex(t_pipex *pipex)
{
	printf(BLUE "[FT_FREE_PIPEX] "GREEN"Closing infile: "RESET);	
	if (pipex->infile)
	{
		printf("ok\n");
		close(pipex->infile);
	}
	else
		printf("no need\n");
	printf(BLUE "[FT_FREE_PIPEX] "GREEN"Closing outfile: "RESET);
	if (pipex->outfile)
	{
		printf("ok\n");
		close(pipex->outfile);
	}
	else
		printf("no need\n");
	printf(BLUE "[FT_FREE_PIPEX] "GREEN"Closing Pipe:\n"RESET);
	printf(CYAN"\tRead end: "RESET);
	if (pipex->pipe[0])
	{
		printf("ok\n");
		close(pipex->pipe[0]);
	}
	else
		printf("no need\n");
	printf(CYAN"\tWrite end: "RESET);
	if (pipex->pipe[1])
	{
		printf("ok\n");
		close(pipex->pipe[1]);
	}
	else
		printf("no need\n");
	printf(BLUE "[FT_FREE_PIPEX] "GREEN "Freeing path: "RESET "%p\n",pipex->path);
	ft_free_array(pipex->path);
	printf(GREEN"Freeing commands\n"RESET);
	ft_free_cmd(&pipex->commands[0]);
	ft_free_cmd(&pipex->commands[1]);
	printf(GREEN"Setting all to NULL\n"RESET);
	pipex->commands[0].command = NULL;
	pipex->commands[0].path = NULL;
	pipex->commands[1].command = NULL;
	pipex->commands[1].path = NULL;
	pipex->path = NULL;
	return (0);
}

static char	**ft_get_path(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

static char	ft_get_command(char *argv, char **path_list, t_cmd *cmd)
{
	char	*path;

	path = NULL;
	cmd->command = ft_split(argv, ' ');
	if (cmd->command == NULL)
		return (0);
	printf(BLUE "[FT_GET_COMMAND] " GREEN "Got command:\n" RESET);
	int i =0;
	while(cmd->command[i])
	{
		printf(CYAN"\t%d."RESET" \"%s\"\n", i,cmd->command[i]);
		i++;
	}
	while(*path_list != NULL)
	{
		path = ft_strjoin("/", cmd->command[0]);
		path = ft_strjoin(*path_list, path);
		printf(BLUE "[FT_GET_COMMAND] " GREEN "Trying path: " RESET"\"%s\"\n",path);
		if (access(path, F_OK) == 0)
		{
			cmd->path = path;
			printf(BLUE "[FT_GET_COMMAND] " GREEN "Correct path saved as: "RESET"\"%s\"\n",cmd->path);
			return (1);
		}
		path_list++;
	}
	if (path)
		free(path);
	return (0);
}

static char	ft_init(int argc, char **argv, char **envp, t_pipex *pipex)
{
	//check that there are 4 arguments
	printf(BLUE "[FT_INIT] "GREEN"5 arguments: "RESET);
	if (argc != 5)
	{
		printf("fail\n");
		return (0);
	}
	printf("OK\n");
	//try to open both files
	printf(BLUE "[FT_INIT] "GREEN "Infile open fd: " RESET);
	pipex->infile = open(argv[1], O_RDONLY, 0666);
	if (pipex->infile == -1)
	{
		printf("fail\n");	
		return (0);
	}
	printf("OK (id: %d)\n", pipex->infile);
	printf(BLUE "[FT_INIT] "GREEN "Outfile open fd: " RESET);
	pipex->outfile = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0666);
	if (pipex->outfile == -1)
	{
		printf("fail\n");
		return (0);
	}
	printf("OK (id: %d)\n",pipex->outfile);
	printf(BLUE "[FT_INIT] "GREEN "Outfile open fd: "RESET"%d\n", pipex->outfile);
	//save path on strings
	printf(BLUE "[FT_INIT] "GREEN "PATH saved: " RESET);
	pipex->path = ft_get_path(envp);
	if (pipex->path == NULL)
	{
		printf("fail\n");
		return (0);
	}
	printf("ok\n");
	int i = 0;
	while(pipex->path[i])
	{
		printf(CYAN "\t%d."RESET" \"%s\"\n", i, pipex->path[i]);
		i++;
	}
	//check if commands are accesible
	if (!ft_get_command(argv[2], pipex->path, &pipex->commands[0])
		|| !ft_get_command(argv[3], pipex->path, &pipex->commands[1]))
		return (0);
	for (int j = 0; j < 2; j++)
	{
		printf(BLUE "[FT_INIT] "GREEN "Command %d saved:\n" RESET, j);
		printf(CYAN"\tPATH =" RESET " %s\n", pipex->commands[j].path);
		i = 0;
		while(pipex->commands[j].command[i])
		{
			printf(CYAN"\t%d." RESET " \"%s\"\n", i, pipex->commands[j].command[i]);
			i++;
		}
	}
	//if everything nice return 1
	return (1);
}

void ft_child1(t_pipex pipex, char **envp)
{
	printf(BLUE"[FT_CHILD1] " GREEN "Starting child1\n"RESET);
	printf(BLUE "[FT_CHILD1] " GREEN "Saved command:\n"RESET);
	printf(BLUE "[FT_CHILD1] "CYAN "\tPATH = " RESET "\"%s\"\n", pipex.commands[0].path);
	int i = 0;
	while (pipex.commands[0].command[i] != NULL)
	{
		printf(BLUE "[FT_CHILD1] "CYAN "\t%d. " RESET "\"%s\"\n", i, pipex.commands[0].command[i]);
		i++;
	}
	dup2(pipex.infile, 0);
	close(pipex.pipe[0]);
	dup2(pipex.pipe[1], 1);
	execve(pipex.commands[0].path, pipex.commands[0].command, envp);
}

void ft_child2(t_pipex pipex, char **envp)
{
	printf(BLUE"[FT_CHILD2] " GREEN "Starting child2\n");
	printf(BLUE "[FT_CHILD2] " GREEN "Saved command:\n");
	printf(BLUE "[FT_CHILD2] "CYAN "\tPATH = " RESET "\"%s\"\n", pipex.commands[1].path);
	int i = 0;
	while (pipex.commands[1].command[i] != NULL)
	{
		printf(BLUE "[FT_CHILD2] "CYAN "\t%d. " RESET "\"%s\"\n", i, pipex.commands[1].command[i]);
		i++;
	}
	dup2(pipex.outfile, 1);
	close(pipex.pipe[1]);
	dup2(pipex.pipe[0], 0);
	execve(pipex.commands[1].path, pipex.commands[1].command, envp);
}

void print_pipex(const t_pipex *pipex)
{
	printf(RED"Pipex values:\n" RESET);
	printf(YELLOW"\tpipe[0]: "RESET"%d\n",pipex->pipe[0]);
	printf(YELLOW"\tpipe[1]: "RESET"%d\n",pipex->pipe[1]);
	printf(YELLOW"\tinfile: "RESET"%d\n",pipex->infile);
	printf(YELLOW"\toutfile: "RESET"%d\n",pipex->outfile);
	printf(YELLOW"\tPATH: "RESET"%p\n",pipex->path);
	if  (pipex->path != NULL)
	for (int i = 0; pipex->path[i] != NULL; i++)
		printf(CYAN"\t\t%d. " RESET "\"%s\"\n",i , pipex->path[i]);
	for (int j = 0; j < 2; j++)
	{
		printf(YELLOW"\tcommand[%d]:\n"RESET,j);
		printf(CYAN"\t\tpath. "RESET"(%p) \"%s\"\n",pipex->commands[j].path, pipex->commands[j].path);
		printf(CYAN"\t\tcommand: "RESET "%p\n", pipex->commands[j].command);
		if (pipex->commands[j].command !=NULL)
		for (int i = 0; pipex->commands[j].command[i] != NULL; i++)
			printf("\t\t\t%d. \"%s\"\n",i, pipex->commands[j].command[i]);
	}
}

void	ft_pipex_init(t_pipex *pipex)
{
	pipex->path = 0;
	pipex->commands[0].path = 0;
	pipex->commands[0].command = 0;
	pipex->commands[1].path = 0;
	pipex->commands[1].command = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		id1;
	int		id2;

	ft_pipex_init(&pipex);
	print_pipex(&pipex);
	printf(BLUE "[MAIN] "GREEN "Begin main\n"RESET);
	if (!ft_init(argc, argv, envp, &pipex))
		return (ft_free_pipex(&pipex));
	if (pipe(pipex.pipe) == -1)
		return (ft_free_pipex(&pipex));
	printf(GREEN"Pipe created:\n");
	printf(CYAN"\tWrite. " RESET"\"%d\"\n", pipex.pipe[1]);
	printf(CYAN"\tRead. " RESET"\"%d\"\n", pipex.pipe[0]);
	id1 = fork();
	if (id1 == -1)
		return (ft_free_pipex(&pipex));
	if (id1 == 0)
		ft_child1(pipex, envp);
	id2 = fork();
	if (id2 == -1)
		return (ft_free_pipex(&pipex));
	if (id2 == 0)
		ft_child2(pipex, envp);
	printf(GREEN "Waiting for children\n" RESET);
	close (pipex.pipe[0]);
	close (pipex.pipe[1]);
	waitpid(id1, NULL, 0);
	printf(GREEN "Child1 finished\n" RESET);
	waitpid(id2, NULL, 0);
	printf(GREEN "Child2 finished\n" RESET);
	return (0);
}
