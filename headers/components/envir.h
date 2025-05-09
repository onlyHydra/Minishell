/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:11:11 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 14:43:42 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIR_H
# define ENVIR_H

# include "libft.h"
# include "models/envir_struct.h"
# include "models/input_data_struct.h"
# include <stdlib.h>
# include <unistd.h>

/* ========= Environment Management ========= */

/**
 * @brief Initialize environment variables from envp
 * @param envp: Array of environment variables (NAME=VALUE format)
 * @return Pointer to the head of env_var list or NULL if failed
 */
t_env_var	*init_env_vars(char **envp);

/**
 * @brief Setup the environment variables from envp
 * @param envp: Array of environment variables (NAME=VALUE format)
 * @return Pointer to the head of env_var list or NULL if failed
 */
t_env_var	*setup_environment(char **envp);

/**
 * @brief Create a new env variable node
 * @param name: Variable name
 * @param value: Variable value
 * @param exported : Flag to mark exported(1) or not (0)
 * @return Pointer to new node or NULL if failed
 */
t_env_var	*create_env_var(char *name, char *value, int exported);

/**
 * @brief Add a new env variable node to the list
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name
 * @param value: Variable value
 * @param exported : Flag to mark exported(1) or not (0)
 * @return Pointer to the head of env_var list or NULL if failed
 */
t_env_var	*add_env_var(t_env_var **head, char *name, char *value,
				int exported);

/**
 * @brief Find an env variable by name
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name to find
 * @return Pointer to the variable or NULL if not found
 */
t_env_var	*find_env_var(t_env_var *head, const char *name);

/**
 * @brief Get the value of an env variable
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name
 * @return Value of the variable or NULL if not found
 */
char		*get_env_value(t_env_var *head, const char *name);

/**
 * @brief Update the value of an existing env variable or create new
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name
 * @param value: New value
 * @param exported : Flag to mark exported(1) or not (0)
 * @return 0 if successful, 1 if failed
 */
int			update_env_var(t_env_var **head, const char *name,
				const char *value, int exported);

/**
 * @brief Remove an env variable
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name to remove
 * @return 0 if successful, 1 if not found
 */
int			remove_env_var(t_env_var **head, const char *name);

/* ========= Environment Variable Expansion ========= */

/**
 * @brief Parse env variables in command input
 * @param input: Command input string
 * @param env_vars: Pointer to the head of env_var list
 * @return New string with expanded variables or NULL if failed
 */
char		*expand_env_vars(char *input, t_env_var *env_vars);

/**
 * @brief Handle special $ variables like $?
 * @param var_char: Character after $
 * @param exit_status: Current exit status
 * @return String value for the special variable or NULL
 */
char		*handle_dollar_var(char var_char, int exit_status);

/**
 * @brief Print the exit status (for $?)
 * @param exit_status: Current exit status
 * @return 0 on success, 1 on failure
 */
int			print_dollar_question(int exit_status);

/**
 * @brief Check if string starts with $?
 * @param str: String to check
 * @return 1 if string starts with $?, 0 otherwise
 */
int			is_dollar_question(const char *str);

/**
 * @brief Extract variable name from string
 * @param str: String starting with variable name
 * @return Variable name or NULL if failed
 */
char		*extract_var_name(char *str);

/**
 * @brief Get the expanded length of input with env vars
 * @param input: Input string
 * @param env_vars: Environment variables
 * @return Length of expanded string
 */
int			get_expanded_len(char *input, t_env_var *env_vars);

/* ========= Environment Command Handlers ========= */

/**
 * @brief Handle export command
 * @param env_vars: Pointer to the head of env_var list
 * @param args: Command arguments (NULL or name=value pairs)
 * @return Exit status (0 for success, 1 for error)
 */
int			cmd_export(t_env_var **env_vars, char **args);

/**
 * @brief Handle unset command
 * @param env_vars: Pointer to the head of env_var list
 * @param args: Command arguments (variable names to unset)
 * @return Exit status (0 for success, 1 for error)
 */
int			cmd_unset(t_env_var **env_vars, char **args);

/**
 * @brief Handle env command
 * @param env_vars: Pointer to the head of env_var list
 * @return Exit status (0 for success, 1 for error)
 */
int			cmd_env(t_env_var *env_vars);

#endif /* ENVIR_H */
