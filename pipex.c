#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t index;

	index = 0;
	while (s[index])
		index++;
	return (index);
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






int 	main(int argc, char *argv[], char *envp[])
{
	printf("%s\n", argv[0]);
	printf("%s\n", envp[0]);
	printf("%s\n", argv[1]);
	printf("%s\n", envp[1]);
	printf("%d\n", argc);
	int i;
	//char *str1[] = {"ls", "-la", 0};
	char *str;
	//char *str1 = argv[];
	//char *bin; 

	i = argc;
	i += 0;
	//str = argv[i];
	/*while (argv[1][i] != ' ')
	{
		bin[i] = argv[1][i];
		i++;
	}*/
	str = "/bin/ls";
	execve(str, argv, envp); //funciona se mandar o str1, mas nao se mandar o argv. pesquisar como adicionar um null ao fim de um array de arrays. Boa noite (:
	/*while (i < argc)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}*/
	
}
