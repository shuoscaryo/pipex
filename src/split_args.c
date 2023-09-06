/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:41:56 by orudek            #+#    #+#             */
/*   Updated: 2023/09/06 22:51:30 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_num_words(char *s, char c)
{
	size_t	count;
	size_t	is_word;
	size_t	flag;

	flag = 0;
	is_word = 0;
	count = 0;
	while (*s)
	{
		if (*s == '"')
			flag = !flag;
		if (!is_word && *s != c)
		{
			is_word = 1;
			count++;
		}
		else if (is_word && !flag && *s == c)
			is_word = 0;
		s++;
	}
	return (count);
}

static int	ft_get_word_len(char *str, char c)
{
	int	i;
	int	len;
	int	flag;

	i = 0;
	len = 0;
	flag = 0;
	while (str[i] && (str[i] != c || flag))
	{
		if (str[i++] == '"')
			flag = !flag;
		else
			len++;
	}
	return (len);
}

static char	*ft_get_word(char **s, char c)
{
	size_t	i;
	char	*out;
	size_t	len;

	while (**s == c)
		(*s)++;
	len = ft_get_word_len(*s, c);
	out = malloc(len + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (*(*s) == '"')
			(*s)++;
		out[i++] = *((*s)++);
	}
	if (*(*s) == '"')
		(*s)++;
	out[i] = 0;
	return (out);
}

static char	**ft_array_free(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (NULL);
}

char	**ft_split_args(char *s, char c)
{
	char	**words;
	size_t	num_words;
	size_t	i;

	num_words = ft_get_num_words(s, c);
	words = malloc((sizeof(char *) * (num_words + 1)));
	if (words == NULL)
		return (NULL);
	i = 0;
	while (i < num_words)
	{
		words[i] = ft_get_word(&s, c);
		if (!words[i])
			return (ft_array_free(words));
		i++;
	}
	words[i] = 0;
	return (words);
}
