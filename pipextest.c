#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

size_t	ft_strlen(const char *s)
{
	size_t index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

static int	count(char const *s, char c)
{
	unsigned int index;
	unsigned int count;

	index = 0;
	count = 0;
	while (s[index])
	{
		while (s[index] == c)
			index++;
		if (s[index] != '\0')
			count++;
		while (s[index] && s[index] != c)
			index++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	index;
	size_t	index_len;

	index_len = ft_strlen(s);
	index = 0;
	if (len > (index_len - start))
		len = index_len - start;
	if (start >= index_len)
	{
		sub = (char *)malloc(sizeof(*sub));
		*sub = 0;
		return (sub);
	}
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	while (s[start + index] != '\0' && len > 0)
	{
		sub[index] = s[start + index];
		index++;
		len--;
	}
	sub[index] = '\0';
	return (sub);
}

char		**ft_split(char const *s, char c)
{
	unsigned int	index;
	unsigned int	index_a;
	unsigned int	index_tab;
	char			**tab;

	index_a = 0;
	index_tab = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!(tab))
		return (NULL);
	tab[count(s, c)] = 0;
	while (*s && *s == c)
		s++;
	while (s[index_a])
	{
		index = index_a;
		while (s[index_a] && s[index_a] != c)
			index_a++;
		tab[index_tab++] = ft_substr(s, index, index_a - index);
	while (s[index_a] && s[index_a] == c)
			index_a++;
	}
	return (tab);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	index;
	unsigned int	index_b;
	char			*str;

	index = 0;
	index_b = 0;
	str = (char *)malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (str == NULL)
		return (NULL);
	while (s1[index])
	{
		str[index] = s1[index];
		index++;
	}
	while (s2[index_b])
	{
		str[index + index_b] = s2[index_b];
		index_b++;
	}
	str[index + index_b] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t index;

	index = 0;
	if (n == 0)
		return (0);
	while (s1[index] == s2[index] && index < n - 1 && s1[index] != '\0')
		index++;
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}

char	*str3join(char *path, char *command, char *c)
{
	char *str;
	char *temp;


	temp = ft_strjoin(path, c);
	str = ft_strjoin(temp, command);
	free(temp);
	return (str);
}

int	command(int argc, char *argv, char *envp[])
{
	int index;
	char **path;
	char *str3;
	char *str = "PATH=/usr/";
	char **arg;
	
	arg = malloc(sizeof(char *) * argc - 1);
	index = 0;
	while (envp[index])
	{
		if (!ft_strncmp(envp[index], str, sizeof(str)))
			break;
		index++;
	}
	path = ft_split(envp[index] + 6, ':');
	arg = ft_split(argv, ' ');
	arg[2] = NULL;
	index = 0;
	while(path[index])
	{
		str3 = str3join(path[index], arg[0], "/");
		execve(str3, arg, NULL); 
		index++;
	}
	exit(0);
	free(arg);
	return(0);
}

int 	main(int argc, char *argv[], char *envp[])
{
	int fd[2];
	int fdi;
	int pid1;
	int pid2;
	int test;
 
	if (argc != 5)
		return(0);
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
		//printf("%d\n", test);
	}
	pid2 = fork(); 
	if (pid2 < 0)
		return(0);
	if (pid2 == 0)
	{
		fdi = open( argv[4], O_WRONLY | O_TRUNC);
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
//esta a funcionar corretamente, so as quando tento enviar para o infile e que da erro, nomeadamente o primeiro comando nao funciona
