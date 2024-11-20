/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cakose <cakose@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:14:07 by cakose            #+#    #+#             */
/*   Updated: 2024/11/20 14:21:14 by cakose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **av, char **env, int *fd)
{
	int		file_in;

	file_in = open(av[1], O_RDONLY);
	if (file_in == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error("Error opening infile");
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error("dup2 failed to redirect stdout");
	if (dup2(file_in, STDIN_FILENO) == -1)
		error("dup2 failed to redirect stdin");
	close(fd[0]);
	close(fd[1]);
	close(file_in);
	execute(av[2], env);
}

void	parent(char **av, char **env, int *fd)
{
	int		file_out;

	file_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_out == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error("Error opening outfile");
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error("dup2 failed to redirect stdin");
	if (dup2(file_out, STDOUT_FILENO) == -1)
		error("dup2 failed to redirect stdout");
	close(fd[1]);
	close(fd[0]);
	close(file_out);
	execute(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;

	if (ac != 5)
		exit_program(1);
	if (pipe(fd) == -1)
		exit_program(-1);
	pid = fork();
	if (pid == -1)
		exit_program(-1);
	if (pid == 0)
		child(av, env, fd);
	pid2 = fork();
	if (pid2 == -1)
		exit_program(-1);
	if (pid2 == 0)
		parent(av, env, fd);
	close(fd[0]);
	close(fd[1]);
	if (waitpid(pid, NULL, 0) == -1)
		error("Failed to wait for child process");
	if (waitpid(pid2, NULL, 0) == -1)
		error("Failed to wait for parent process");
	return (0);
}
