/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:41:10 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 14:56:54 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIR_INTERFACE_H
# define ENVIR_INTERFACE_H

# include "models/envir_struct.h"
# include "models/input_data_struct.h"

/* ========= Helper Functions ========= */

/**
 * @brief Extract environment variable value from string
 * @param str: String containing environment variable
 * @param envp: Environment variables array
 * @return Value of environment variable or NULL if not found
 */
char	*extract_env_value(char *str, char **envp);

/**
 * @brief Get arguments from parsed data
 * @param data: Parsed data
 * @return Array of arguments
 */
char	**get_args_from_data(t_parsed_data *data);

/**
 * @brief Check if string is an environment variable
 * @param str: String to check
 * @return 1 if string is an environment variable, 0 otherwise
 */
int		is_environment_variable(const char *str);

/**
 * @brief Convert env_var list to char** array for execve
 * @param head: Pointer to the head of env_var list
 * @return Array of strings in NAME=VALUE format, NULL terminated
 */
char	**env_var_to_array(t_env_var *head);

/**
 * @brief Free all env variables
 * @param head: Pointer to the head of env_var list
 */
void	free_env_vars(t_env_var **head);

/**
 * @brief Create a copy of environment variables array
 * @param envp: Environment variables array
 * @return Copy of environment variables array
 */
char	**copy_envp(char **envp);

/**
 * @brief Update environment variables array
 * @param env_vars: Environment variables list
 * @param envp: Pointer to environment variables array
 * @return 0 on success, 1 on failure
 */
int		update_envp(t_env_var *env_vars, char ***envp);

/**
 * @brief Convert environment variables list to array
 * @param var: Environment variables list
 * @return Environment variables array
 */
char	**envp_to_char(t_env_var *var);

#endif