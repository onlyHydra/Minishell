/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:15:20 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/03 19:26:06 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "envir.h"
# include "models/exec_ctx.h"
# include "models/graph_struct.h"
# include "models/token_struct.h"
# include <sys/wait.h>
# include <unistd.h>

/**
 * Execute the export command
 * @param data Parsed command data
 * @param env_vars Environment variables list
 * @return Exit status of the command
 */
int		execute_export(t_parsed_data *data, t_env_var **env_vars);

/**
 * Execute the unset command
 * @param data Parsed command data
 * @param env_vars Environment variables list
 * @return Exit status of the command
 */
int		execute_unset(t_parsed_data *data, t_env_var **env_vars);

/**
 * Execute the env command
 * @param env_vars Environment variables list
 * @return Exit status of the command
 */
int		execute_env(t_env_var *env_vars);

/**
 * Handle environment-related commands (export, unset, env)
 * @param data Parsed command data
 * @param env_vars Environment variables list
 * @return Exit status of the command or -1 if not an env command
 */
int		handle_env_commands(t_parsed_data *data, t_env_var **env_vars);

/**
 * Execute the exit command
 * @param data Parsed command data
 * @param env_vars Environment variables list
 * @return Exit status of the command
 */
int		run_execve(char *filepath, char **argv, char **envp);

int		apply_redirections(t_redir *redir_list);

int		dfs_walk(t_node *root, t_exec_ctx *ctx);

int		create_pipe(int pipe_fds[2]);

void	close_pipe(int pipe_fds[2]);

int		execute_pipe(t_node *root, t_exec_ctx *ctx);

int		execute_command(t_node *node, t_exec_ctx *ctx);

int		execute_subshell(t_node *node, t_exec_ctx *ctx);

#endif /* EXECUTION_H */