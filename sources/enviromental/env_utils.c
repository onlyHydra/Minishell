/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:59:29 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/06 15:07:02 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "models/input_data_struct.h"

/**
 * Check if a character is valid for a variable name
 * Valid chars: alphanumeric and underscore
 */
int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * Free string array used for args
 */
void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * Check if a string starts with a $ character
 *  and is an environment variable
 * @param str: String to check
 * @return: 1 if it's an environment variable, 0 otherwise
 */
int	is_environment_variable(const char *str)
{
	return (str && str[0] == '$' && str[1] && str[1] != ' ' && str[1] != '\t');
}

/**
 * Count the number of arguments in parsed_data (excluding the command)
 */
static int	count_args(t_parsed_data *data)
{
	int				count;
	t_parsed_data	*current;

	count = 0;
	current = data;
	while (current && current->data)
	{
		current++;
		count++;
	}
	return (count);
}

/**
 * Convert parsed_data arguments to string array for env commands
 * Skip the command name itself
 */
char	**get_args_from_data(t_parsed_data *data)
{
	int				count;
	char			**args;
	int				i;
	t_parsed_data	*current;

	count = count_args(data);
	i = 0;
	if (count <= 1)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * count);
	if (!args)
		return (NULL);
	current = data + 1;
	while (current && current->data && i < count - 1)
	{
		args[i] = ft_strdup(current->data);
		if (!args[i])
			return (free_args(args), NULL);
		current++;
		i++;
	}
	args[i] = NULL;
	return (args);
}
