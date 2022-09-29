/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 20:34:35 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 03:00:10 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*str3join(char *path, char *command, char *c)
{
	char	*str;
	char	*temp;

	printf("%s\n", path);
	if (path == NULL)
	{
		ft_putstr_fd("Error - Path to function not found", 1);
		return (NULL);
	}
	temp = ft_strjoin(path, c);
	str = ft_strjoin(temp, command);
	free(temp);
	return (str);
}

int	pathFinder(t_list *s_st, int argc, char *argv, char *envp[])
{
	s_st->str = "PATH=/usr/";
	s_st->arg = malloc(sizeof(char *) * argc - 1);
	if (!s_st->arg)
	{
		ft_putstr_fd("Error allocating memory", 1);
		return (-1);
	}
	s_st->index = 0;
	while (envp[s_st->index++])
	{
		if (!ft_strncmp(envp[s_st->index], s_st->str, sizeof(s_st->str)))
			break ;
	}
	s_st->path = ft_split(envp[s_st->index] + 6, ':');
	s_st->arg = ft_split(argv, ' ');
	return (0);
}

void	command(int argc, char *argv, char *envp[])
{
	t_list	s_st;

	if (pathFinder(&s_st, argc, argv, envp) != 0)
		return ;
	s_st.index = 0;
	while (s_st.path[s_st.index++])
	{
		s_st.str3 = str3join(s_st.path[s_st.index], s_st.arg[0], "/");
		if (s_st.str3 == NULL)
			break ;
		execve(s_st.str3, s_st.arg, NULL);
	}
	free(s_st.arg);
	exit(-1);
}
