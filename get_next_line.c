/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avenonat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:17:39 by avenonat          #+#    #+#             */
/*   Updated: 2019/10/08 17:17:47 by avenonat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_new_line(char **s, char **line, int fd, int text)
{
	char	*temp;
	int		len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		temp = ft_strdup(s[fd] + len + 1);
		free(s[fd]);
		s[fd] = temp;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	else if (s[fd][len] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*s[255];
	char		buffer[BUFF_SIZE + 1];
	char		*temp;
	int			text;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((text = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[text] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strnew(1);
		temp = ft_strjoin(s[fd], buffer);
		free(s[fd]);
		s[fd] = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (text < 0)
		return (-1);
	else if (text == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
		return (0);
	return (ft_new_line(s, line, fd, text));
}

int		main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*line;
	
	i = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line) == 1)
	{
		ft_putstr(line);
		ft_putchar('\n');
	}
	close(fd);
	return (0);
	}
}
