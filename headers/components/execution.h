/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:15:20 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 19:18:06 by schiper          ###   ########.fr       */
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

# define SEG_COUNT 100

/**
 * Execute the export command
 * @param data Parsed command data
 * @param env_vars Environment variables list
 * @return Exit status of the command
 */
int		execute_export(char **data, t_env_var **env_vars);

/**
 * Execute the unset command
 * @param data Parsed command data
 * @param env_vars Environment variables list
 * @return Exit status of the command
 */
int		execute_unset(char **data, t_env_var **env_vars);

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

int		dfs_walk(t_node *root, t_exec_ctx *ctx, int pipe_flag);

int		create_pipe(int pipe_fds[2]);

void	close_pipe(int pipe_fds[2]);

int		execute_n_pipe(t_node *root, t_exec_ctx *ctx);

int		execute_command(t_node *node, t_exec_ctx *ctx, int pipe_flag);

int		execute_subshell(t_node *node, t_exec_ctx *ctx, int pipe_flag);

void	apply_redirections(t_redir *redir_list, t_exec_ctx *ctx);

void	apply_all_subshell_redirs(t_node *node, t_exec_ctx *ctx);

void	apply_redirs_for(t_node *segm, t_exec_ctx *ctx);

pid_t	fork_or_die(void);

int		collect_pipe_segments(t_node *root, t_node **segm, int max);

int		pre_check(t_node *node, t_exec_ctx *ctx, int pipe_flag);
void	body(int n, t_node *segments[SEG_COUNT], t_exec_ctx *ctx,
			pid_t pids[SEG_COUNT]);

void	preprocess_heredocs(t_redir *redir_list, t_exec_ctx *ctx);

/**
 * @brief Frees an AST node and all its children recursively.
 * @param node Pointer to the root node of the tree to free.
 */
void	free_ast(t_node **node);
/**
 * @brief Free array of arguments
 * @param args: Array of arguments
 */
void		free_args(char **args);

#endif /* EXECUTION_H */