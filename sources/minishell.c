/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:31:05 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/16 15:32:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv, char **envp)
{
	t_parsed_data	*parsed_data;

	if (argc)
	{
		parsed_data = tokenize_data(argv);
		if (parsed_data)
		{
			printf("Tokenization successful!\n");
			for (int i = 0; parsed_data[i].token; i++)
			{
				printf("Token %d: Type = %d, Value = '%s'\n", i,
					*(parsed_data[i].token), parsed_data[i].data);
			}
			for (int i = 0; parsed_data[i].token; i++)
			{
				free(parsed_data[i].token);
				free(parsed_data[i].data);
			}
			free(parsed_data);
		}
		else
			printf("Tokenization failed or no input provided.\n");
	}
	if (envp)
		return (1);
	return (0);
}
