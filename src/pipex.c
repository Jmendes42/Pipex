/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 11:04:49 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 03:00:01 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	subVerificate(int control, char *argv)
{
	if (access(argv, F_OK) != 0)
	{
		ft_putstr_fd("Error - Infile not found\n", 1);
		return (-1);
	}
	if (access(argv, R_OK) != 0)
	{
		ft_putstr_fd("Error - Outfile not found\n", 1);
		return (-1);
	}
	return (0);
}

int	verificate(char *argv[], int control)
{
	char	*permition;

	if (control == 0)
	{
		if (subVerificate(control, argv[1]) != 0)
			return (-1);
	}
	else if (control == 1)
		permition = "Error - Outfile not found\n";
	else
		return (-1);
	return (0);
}

void	forker(int argc, char *argv[], char *envp[], int fd[2])
{
	int	fdi;

	if (verificate(argv, 0) != 0)
		return ;
	fdi = open(argv[1], O_RDONLY);
	if (fdi < 0)
	{
		ft_putstr_fd("Error - Infile didn't open", 1);
		return ;
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(fdi, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	command(argc, argv[2], envp);
}

void	forker1(int argc, char *argv[], char *envp[], int fd[2])
{
	int	fdi;

	if (verificate(argv, 1) != 0)
	{
		return ;
	}
	fdi = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fdi < 0)
	{
		ft_putstr_fd("Error - Outfile didn't open", 1);
		return ;
	}
	dup2(fdi, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	command(argc, argv[3], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	fd[2];
	int	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Wrong input\n", 1);
		return (-1);
	}
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		forker(argc, argv, envp, fd);
	wait(NULL);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		forker1(argc, argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
}
