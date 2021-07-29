/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipextest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 05:08:14 by jmendes           #+#    #+#             */
/*   Updated: 2021/07/29 05:26:39 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (0);
	while (s1[index] == s2[index] && index < n - 1 && s1[index] != '\0')
		index++;
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}

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
	while (envp[index])
	{
		if (!ft_strncmp(envp[index], str, sizeof(str)))
			break ;
		index++;
	}
	path = ft_split(envp[index] + 6, ':');
	arg = ft_split(argv, ' ');
	arg[2] = NULL;
	index = 0;
	while (path[index])
	{
		str3 = str3join(path[index], arg[0], "/");
		execve(str3, arg, NULL);
		index++;
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
	int	test;

	if (argc != 5)
		return (0);
	if (pipe(fd) == -1)
		printf("ERROR");
	pid1 = fork();
	if (pid1 < 0)
		printf("ERROR");
	if (pid1 == 0)
	{
		test = open(argv[1], O_RDONLY);
		if (test < 0)
			return (0);
		dup2(fd[1], STDOUT_FILENO);
		dup2(test, 0);
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
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("DONE\n");
}
