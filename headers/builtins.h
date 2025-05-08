/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:00:00 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 14:46:06 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "envir.h"
# include "execution.h"
# include "minishell.h"
# include <limits.h>
# include "models/envir_struct.h"

/*
 * Checks if a command is a built-in command
 * @param cmd The command string to check
 * @return 1 if it's a built-in command, 0 otherwise
 */
int		is_builtin(const char *cmd);

/*
 * Execute a built-in command
 * @param data Parsed command data
 * @param env_vars Environment variables list
 * @return Exit status of the command or -1 if not a built-in
 */
int		execute_builtin(char **argv, t_env_var **env_vars);

/*
 * Implements the echo built-in command
 * @param data Parsed command data
 * @param fds File descriptors [0: input, 1: output]
 * @return Exit status (0 for success)
 */
int		builtin_echo(char **argv, int fds[2]);

/*
 * Implements the cd built-in command
 * @param data Parsed command data
 * @param env_vars Environment variables list
 * @return Exit status (0 for success, 1 for error)
 */
int		builtin_cd(char **argv, t_env_var **env_vars);

/*
 * Implements the pwd built-in command
 * @param env_vars Environment variables list
 * @return Exit status (0 for success, 1 for error)
 */
int		builtin_pwd(t_env_var **env_vars);

/*
 * Implements the exit built-in command
 * @param data Parsed command data
 * @param exit_flag Pointer to exit flag
 * @return Exit status code
 */
int		builtin_exit(char **argv, int *exit_flag);

/*
 * Utility function to check if a string is a valid number for exit
 * @param str String to check
 * @return 0 if valid, -1 otherwise
 */
int		is_valid_numeric_argument(char *str);

/*
 * Utility function to check if a string has only the -n flag (e.g. -n, -nnn)
 * @param arg String to check
 * @return 0 if it's a -n flag, -1 otherwise
 */
int		is_dash_n_flag(const char *arg);

/*
 * Utility function to print echo arguments
 * @param fds File descriptors [0: input, 1: output]
 * @param args Arguments to print
 */
void	print_echo_args(int fds[2], char **args);

/*
 * Updates the OLDPWD and PWD environment variables after cd
 * @param env_vars Environment variables list
 */
void	update_dirs(t_env_var **env_vars);

/*
 * Changes to the user's home directory
 * @param env_vars Environment variables list
 * @return Exit status (0 for success, 1 for error)
 */
int		change_to_home_directory(t_env_var **env_vars);

/**
 * main built in handler
 *
 */
int		handle_builtin(char **argv, t_env_var **env_vars, int *exit_status);

char	*resolve_path(char *path);
char	*join_path(char *base, char *component);
char	*resolve_relative_path(char *path, char **envp);
char	*get_current_directory(char **envp);
char	*ft_strjoin3(char *s1, char *s2, char *s3);

#endif /* BUILTINS_H */
