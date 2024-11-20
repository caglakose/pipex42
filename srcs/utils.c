/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakose <cakose@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:14:16 by cakose            #+#    #+#             */
/*   Updated: 2024/11/20 13:56:06 by cakose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*if_path_exist(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	**split_paths(char **env)
{
	int	i;

	i = 0;
	if (if_path_exist(env) == NULL)
		return (NULL);
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (i == 0)
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

char	*find_cmd_path(char *cmd, char **paths)
{
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	paths = split_paths(env);
	if (!paths)
		return (NULL);
	path = find_cmd_path(cmd, paths);
	if (!path)
		return (free2(paths), NULL);
	free2(paths);
	return (path);
}

void	exit_program(int error_code)
{
	if (error_code == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(1);
}
