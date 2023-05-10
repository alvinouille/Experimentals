
#include "new.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

int	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		length;

	i = 0;
	j = 0;
	length = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * length + 1);
	if (!str)
		return (NULL);
	if (s1)
	{
		while (s1[j])
			str[i++] = s1[j++];
	}
	j = 0;
	if (s2)
	{
		while (s2[j])
			str[i++] = s2[j++];
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_line(char *keep)
{
	int		i;
	char	*str;

	i = 0;
	if (!keep[i])
		return (NULL);
	while (keep[i] && keep[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (keep[i] && keep[i] != '\n')
	{
		str[i] = keep[i];
		i++;
	}
	if (keep[i] == '\n')
	{
		str[i] = keep[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_keep_memory(char *keep)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!keep[i])
	{
		free(keep);
		return (NULL);
	}
	str = malloc((ft_strlen(keep) - i + 1));
	if (!str)
	{
		free(keep);
		return (NULL);
	}
	i++;
	while (keep[i])
		str[j++] = keep[i++];
	str[j] = '\0';
	free(keep);
	return (str);
}

char	*ft_strjoin_modif(char *keep, char *buff, size_t i, size_t j)
{
	char	*str;

	if (!keep)
	{
		keep = malloc(1);
		if (!keep)
			return (NULL);
		keep[0] = '\0';
	}
	if (!buff)
		return (free(keep), NULL);
	str = malloc(ft_strlen(keep) + ft_strlen(buff) + 1);
	if (!str)
		return (free(keep), NULL);
	while (keep[++i])
		str[i] = keep[i];
	while (buff[j])
		str[i++] = buff[j++];
	str[ft_strlen(keep) + ft_strlen(buff)] = '\0';
	return (free(keep), str);
}

char	*loopin(int fd, char **keep)
{
	char	*buff;
	size_t	size;

	buff = malloc((BUFFER_SIZE + 1));
	if (!buff)
	{
		if (*keep)
			free(*keep);
		return (NULL);
	}
	size = 1;
	while (!ft_strchr((*keep), '\n') && size != 0)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == (size_t)-1)
		{
			free(*keep);
			free(buff);
			return (NULL);
		}
		buff[size] = '\0';
		(*keep) = ft_strjoin_modif((*keep), buff, -1, 0);
	}
	free(buff);
	return (*keep);
}

char	*get_next_line(int fd, int flag)
{
	char		*line;
	static char	*keep;

	if (flag == 1)
	{
		if (keep)
			free(keep);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (loopin(fd, &keep))
	{
		line = ft_line(keep);
		if (!line)
			return (free(keep), NULL);
		keep = ft_keep_memory(keep);
		if (!keep)
			return (free(line), NULL);
		return (line);
	}
	else
		return (NULL);
}

char	*gnl(int fd)
{
	char	*str;
	char	*tmp;

	str = NULL;
	while (1)
	{
		tmp = get_next_line(fd, 0);
		if (!tmp)
			break ;
		str = ft_strjoin(str, tmp);
		if (!str)
		{
			get_next_line(fd, 1);
			close(fd);
			ft_putstr_fd("Malloc failed !\n", 2);
			exit(2);
		}
		free(tmp);
	}
	if (!tmp && !str)
	{
		close(fd);
		exit(1);
	}
	return (free(tmp), close(fd), str);
}

static char	**free_tabb(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	nb;
	int	trigger;

	i = 0;
	trigger = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] != c && trigger == 0)
		{
			trigger = 1;
			nb++;
		}
		else if (str[i] == c)
			trigger = 0;
		i++;
	}
	return (nb);
}

static int	length_words(const char *str, char c)
{
	int	i;

	i = 0;
	while ((str[i] != c && str[i]) || (str[i] != c && c == 0))
		i++;
	return (i);
}

static char	**splitting(char **tab, char const *s, char c)
{
	int	k;
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = malloc(sizeof(char) * (length_words(&s[i], c) + 1));
			if (!tab[j])
				return (free_tabb(tab, j));
			k = 0;
			while (s[i] != c && s[i])
				tab[j][k++] = s[i++];
			tab[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char **tab;

	if (!s)
		return (0);
	if (count_words(s, c) == 0)
		return (0);
	tab = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	return (splitting(tab, s, c));
}