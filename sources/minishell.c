/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:31:05 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 21:33:34 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/input.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	return (read_loop(envp));
}
