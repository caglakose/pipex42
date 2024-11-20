/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakose <cakose@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:16:57 by cakose            #+#    #+#             */
/*   Updated: 2024/11/20 14:22:14 by cakose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(const char *msg)
{
	if (msg)
		perror(msg);
	perror("\033[31mError\033[0m");
	exit(1);
}

void	free2(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	cleanup_and_error(char **cmd, char *path, const char *msg)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		cmd = NULL;
	}
	if (path)
	{
		free(path);
		path = NULL;
	}
	if (msg)
		perror(msg);
	exit(1);
}

void	execute(char *av, char **env)
{
	char	**cmd;
	char	*path;

	cmd = NULL;
	path = NULL;
	if (av == NULL || av[0] == '\0')
		cleanup_and_error(NULL, NULL, "Command string is empty or null");
	cmd = ft_split(av, ' ');
	if (!cmd || !*cmd)
		cleanup_and_error(cmd, NULL, "Error while splitting command string");
	path = get_path(cmd[0], env);
	if (!path)
		cleanup_and_error(cmd, NULL, "Command not found");
	if (execve(path, cmd, env) == -1)
		cleanup_and_error(cmd, path, "Execution failed");
}
