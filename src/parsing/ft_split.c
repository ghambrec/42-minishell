
#include "../../inc/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
}

static int	calc_len_substr(size_t strlen, size_t start, size_t len)
{
	size_t	substrlen;

	if (start >= strlen)
	{
		return (0);
	}
	if (len < strlen - start)
	{
		substrlen = len;
	}
	else
	{
		substrlen = strlen - start;
	}
	return (substrlen);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	strlen;
	size_t	substrlen;
	size_t	i;
	char	*substr;

	if (!str)
		return (NULL);
	strlen = ft_strlen(str);
	substrlen = calc_len_substr(strlen, start, len);
	substr = (char *)malloc((substrlen + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	if (start >= strlen)
	{
		substr[0] = '\0';
		return (substr);
	}
	i = 0;
	while (i < substrlen && str[start])
	{
		substr[i] = str[start];
		start++;
		i++;
	}
	return (substr[i] = '\0', substr);
}

static int	is_separator(char c, char separator)
{
	if (c == '\0' || c == separator)
		return (1);
	return (0);
}

static int	count_words(const char *str, char sep)
{
	int	i;
	int	split_count;

	i = 0;
	split_count = 0;
	while (str[i])
	{
		if (!is_separator(str[i], sep) && is_separator(str[i + 1], sep))
		{
			split_count++;
		}
		i++;
	}
	return (split_count);
}

static void	free_splits(char **splits, int cur_iter)
{
	while (cur_iter >= 0)
	{
		free(splits[cur_iter]);
		cur_iter--;
	}
	free(splits);
}

static char	*append_word(const char *str, int *word_start, char c)
{
	int		word_len;
	char	*result;

	word_len = 0;
	while (!is_separator(str[*word_start + word_len], c))
		word_len++;
	result = ft_substr(str, *word_start, word_len);
	*word_start += word_len;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**splits;
	int		word_start;
	int		cur_split;

	splits = (char **)malloc((count_words(s, c) + 1) * sizeof(*splits));
	if (!splits)
		return (NULL);
	word_start = 0;
	cur_split = 0;
	while (s[word_start])
	{
		if (is_separator(s[word_start], c))
			word_start++;
		else
		{
			splits[cur_split] = append_word(s, &word_start, c);
			if (!splits[cur_split])
			{
				free_splits(splits, cur_split);
				return (NULL);
			}
			cur_split++;
		}
	}
	return (splits[cur_split] = NULL, splits);
}