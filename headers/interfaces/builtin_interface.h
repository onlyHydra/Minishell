/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_interface.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:39:35 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 15:24:25 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_INTERFACE_H
# define BUILTIN_INTERFACE_H

# include "models/envir_struct.h"
# include <limits.h>

/*
 * Utility function to check if a string is a valid number for exit
 * @param str String to check
 * @return 0 if valid, -1 otherwise
 */
int		is_valid_numeric_argument(char *str);

/*
 * Checks if a command is a built-in command
 * @param cmd The command string to check
 * @return 1 if it's a built-in command, 0 otherwise
 */
int		is_builtin(const char *cmd);

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

#endif
