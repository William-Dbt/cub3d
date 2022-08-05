/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlb <xlb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 10:08:52 by xle-baux          #+#    #+#             */
/*   Updated: 2022/08/05 23:22:39 by xlb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_info	get_infos(char **lines);
static t_info	get_type_id(t_info info ,char **line);
static char		**read_map(char *map);

t_info	parser(char *map)
{
    char    **lines;
	t_info	info;

    lines = read_map(map);
	info = get_infos(lines);

	


	int i = 0;
	while (lines[i])
	{
		printf("%s", lines[i++]);
	}



	return (info);
}

static t_info	get_infos(char **line)
{
	int		i;
	char	**split_line;
	t_info	info;

	i = 0;
	info = init_info_struct();
	while (line[i] && is_empty_line(line[i]) == TRUE)
		i++;
	while (line[i])
	{
		split_line = ft_split(line[i], ' ');
		info = get_type_id(info, split_line);
		free_split_char(split_line);
		while (line[i] && is_empty_line(line[i]) == TRUE)
			i++;
	}
	return (info);
}

static t_info	get_type_id(t_info info ,char **line)
{
	int len;

	len = 0;
	while (line[len])
		len++;
	if (len != 2)
		return (printf("get_type_id ERROR\n"), info);
	if (ft_strncmp(line[0], "NO", 2) == 0 && info.no_texture != NULL)
		info.no_texture = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "SO", 2) == 0 && info.so_texture != NULL)
		info.so_texture = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "WE", 2) == 0 && info.we_texture != NULL)
		info.we_texture = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "EA", 2) == 0 && info.ea_texture != NULL)
		info.ea_texture = ft_strdup(line[1]);
	return (info);
}

static char **read_map(char *map)
{
	int		i;
    int     fd;
    char    **line;

	i = 0;
    line = (char **)malloc(sizeof(char *) * (count_map_lines(map) + 1));
	if (!line)
		return (NULL);
    fd = open(map, O_RDONLY);
    if (fd == -1)
        return (NULL);
    while (1)
    {
        line[i] = get_next_line(fd);
        if (!line[i++])
            break ;
    }
    return (line);
}