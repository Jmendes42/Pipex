/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 11:04:49 by jmendes           #+#    #+#             */
/*   Updated: 2021/07/30 11:06:38 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*str3join(char *path, char *command, char *c)
{
	char	*str;
	char	*temp;

	temp = ft_strjoin(path, c);
	str = ft_strjoin(temp, command);
	free(temp);
	return (str);
}

void	command(int argc, char *argv, char *envp[])
{
	int		index;
	char	**path;
	char	*str3;
	char	*str;
	char	**arg;

	str = "PATH=/usr/";
	arg = malloc(sizeof(char *) * argc - 1);
	index = 0;
	while (envp[index++])
	{
		if (!ft_strncmp(envp[index], str, sizeof(str)))
			break ;
	}
	path = ft_split(envp[index] + 6, ':');
	arg = ft_split(argv, ' ');
	arg[2] = NULL;
	index = 0;
	while (path[index++])
	{
		str3 = str3join(path[index], arg[0], "/");
		execve(str3, arg, NULL);
	}
	exit(0);
	free(arg);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	fd[2];
	int	fdi;
	int	pid1;
	int	pid2;

	if (argc != 5)
		return (0);
	if (pipe(fd) == -1)
		write(1, "ERROR PIPE FUCTION", 18);
	pid1 = fork();
	if (pid1 < 0)
		write(1, "ERROR FORK FUCTION", 19);
	if (pid1 == 0)
	{
		fdi = open(argv[1], O_RDONLY);
		if (fdi < 0)
			return (0);
		dup2(fd[1], STDOUT_FILENO);
		dup2(fdi, 0);
		close(fd[0]);
		close(fd[1]);
		command(argc, argv[2], envp);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (0);
	if (pid2 == 0)
	{
		fdi = open(argv[4], O_WRONLY | O_TRUNC);
		dup2(fdi, 1);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		command(argc, argv[3], envp);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	printf("DONE\n");
}
