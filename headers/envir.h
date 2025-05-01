/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:45:21 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 02:27:59 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include "libft.h"
# include "minishell.h"
# include <stdlib.h>
# include <unistd.h>

/**
 * Structure for environment variables
 * name: variable name
 * value: variable value
 * exported: flag to indicate if variable is exported (1) or shell-only (0)
 * next: next variable in the list
 */
typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					exported;
	struct s_env_var	*next;
}						t_env_var;

/**
 * @brief Initialize environment variables from envp
 * @param envp: Array of environment variables (NAME=VALUE format)
 * @return Pointer to the head of env_var list or NULL if failed
 */
t_env_var				*init_env_vars(char **envp);

/**
 * @brief Create a new env variable node
 * @param name: Variable name
 * @param value: Variable value

	* @param exported: Flag to indicate if variable is exported (1) or shell-only (0)
 * @return Pointer to new node or NULL if failed
 */
t_env_var				*create_env_var(char *name, char *value, int exported);

/**
 * @brief Add a new env variable node to the list
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name
 * @param value: Variable value

	* @param exported: Flag to indicate if variable is exported (1) or shell-only (0)
 * @return Pointer to the head of env_var list or NULL if failed
 */
t_env_var				*add_env_var(t_env_var **head, char *name, char *value,
							int exported);

/**
 * @brief Find an env variable by name
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name to find
 * @return Pointer to the variable or NULL if not found
 */
t_env_var				*find_env_var(t_env_var *head, const char *name);

/**
 * @brief Get the value of an env variable
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name
 * @return Value of the variable or NULL if not found
 */
char					*get_env_value(t_env_var *head, const char *name);

/**

	* @brief Update the value of an existing env variable or create new if not exists
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name
 * @param value: New value

	* @param exported: Flag to indicate if variable is exported (1) or shell-only (0)
 * @return 0 if successful, 1 if failed
 */
int						update_env_var(t_env_var **head, const char *name,
							const char *value, int exported);

/**
 * @brief Remove an env variable
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name to remove
 * @return 0 if successful, 1 if not found
 */
int						remove_env_var(t_env_var **head, const char *name);

/**
 * @brief Convert env_var list to char** array for execve
 * @param head: Pointer to the head of env_var list
 * @return Array of strings in NAME=VALUE format, NULL terminated
 */
char					**env_var_to_array(t_env_var *head);

/**
 * @brief Free all env variables
 * @param head: Pointer to the head of env_var list
 */
void					free_env_vars(t_env_var *head);

/**
 * @brief Parse env variables in command input
 * @param input: Command input string
 * @param env_vars: Pointer to the head of env_var list
 * @param exit_status: Last command exit status for $? expansion
 * @return New string with expanded variables or NULL if failed
 */
char					*expand_env_vars(char *input, t_env_var *env_vars,
							int exit_status);

/**
 * @brief Handle export command
 * @param env_vars: Pointer to the head of env_var list
 * @param args: Command arguments (NULL or name=value pairs)
 * @return Exit status (0 for success, 1 for error)
 */
int						cmd_export(t_env_var **env_vars, char **args);

/**
 * @brief Handle unset command
 * @param env_vars: Pointer to the head of env_var list
 * @param args: Command arguments (variable names to unset)
 * @return Exit status (0 for success, 1 for error)
 */
int						cmd_unset(t_env_var **env_vars, char **args);

/* ========= env_expansion.c ========= */
char					*expand_env_vars(char *input, t_env_var *env_vars,
							int exit_status);

/* ========= env_specials.c ========= */
char					*handle_special_var(char var_char, int exit_status);

/* ========= env_extract.c ========= */
char					*extract_var_name(const char *str);
int						is_valid_var_char(char c);

/* ========= env_export.c ========= */
int						cmd_export(t_env_var **env_vars, char **args);

/* ========= env_unset.c ========= */
int						cmd_unset(t_env_var **env_vars, char **args);

/* ========= env_env.c ========= */
int						cmd_env(t_env_var *env_vars);

/* ========= env_validation.c ========= */
int						is_valid_var_name(const char *name);

/* ========= Other required utility functions (likely defined elsewhere) ========= */
char					*get_env_value(t_env_var *env_vars, const char *name);
t_env_var				*find_env_var(t_env_var *env_vars, const char *name);
int						update_env_var(t_env_var **env_vars, const char *name,
							const char *value, int exported);
int						remove_env_var(t_env_var **env_vars, const char *name);
void					free_args(char **args);
char					**get_args_from_data(t_parsed_data *data);
int						get_expanded_len(char *input, t_env_var *env_vars,
							int exit_status);

#endif /* ENV_VAR_H */
