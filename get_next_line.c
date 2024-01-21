/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaalvare <jaalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:28:41 by jaalvare          #+#    #+#             */
/*   Updated: 2024/01/21 15:36:01 by jaalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_check_save(char *save)
{
	char	*mark;
	char	*line;

	mark = ft_strchr_gnl(save, '\n');
	if (mark)
	{
		line = ft_substr_gnl(save, 0, mark - save + 1);
		if (!line)
			return (0);
		return (line);
	}
	else
		return (0);
}

static char	*ft_keep_save(char *save)
{
	char	*len_start;
	size_t	len_save;
	char	*new_save;

	len_start = ft_strchr_gnl(save, '\n');
	if (!len_start)
		return (0);
	len_save = ft_strlen(len_start);
	new_save = ft_substr_gnl(len_start, 1, len_save);
	if (save)
		free (save);
	if (!new_save)
		return (0);
	return (new_save);
}

static char	*ft_third_part(char **save, char **line, char *buf, char **temp)
{
	char	*mark;

	*save = ft_strjoin_gnl(*save, buf);
	if (!*save)
		return (0);
	mark = ft_strchr_gnl(buf, '\n');
	if (mark)
	{
		*temp = ft_strchr_gnl(*save, '\n');
		*line = ft_substr_gnl(*save, 0, *temp - *save + 1);
		if (!*line)
			return (ft_free_gnl(save));
		return (*line);
	}
	return ((char *) 1);
}

static char	*ft_get_read(int fd, char *buf, char **save, int nb_bytes)
{
	char			*line;
	char			*temp;

	while (nb_bytes > 0)
	{
		nb_bytes = read(fd, buf, BUFFER_SIZE);
		if (nb_bytes == -1)
			return (ft_free_gnl(save));
		buf[nb_bytes] = 0;
		if (nb_bytes == 0)
		{
			if (!ft_strlen(*save))
				return (ft_free_gnl(save));
			else
				return (temp = *save, *save = NULL, temp);
		}
		line = ft_third_part(save, &line, buf, &temp);
		if (line != 0 && line != (char *) 1)
			return (line);
		if (!line)
			return (0);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	char			*line;
	static char		*save;
	int				nb_bytes;

	nb_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!save)
	{
		save = malloc(1);
		if (!save)
			return (0);
		save[0] = 0;
	}
	else
	{
		save = ft_keep_save(save);
		if (save == 0)
			return (0);
		line = ft_check_save(save);
		if (line)
			return (line);
	}
	return (ft_get_read(fd, buf, &save, nb_bytes));
}
