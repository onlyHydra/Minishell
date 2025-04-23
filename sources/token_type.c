/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:14 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/23 22:53:15 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * returns type for 2 character
 * @return: token type
 */
t_token_type	token_one(char *token)
{
	if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '>')
		return (REDIRECT_OUT);
	else if (token[0] == '<')
		return (REDIRECT_IN);
	else if (token[0] == ';')
		return (SEMICOLON);
	return (STR_LITERAL);
}

/**
 * @param c: character to check
 * @return: right token type
 */
t_token_type	get_token_type(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (REDIRECT_OUT);
	else if (c == '<')
		return (REDIRECT_IN);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '"')
		return (DOUBLE_QUOTE);
	else if (c == '-')
		return (FLAG);
	else if (c == ';')
		return (SEMICOLON);
	else
		return (STR_LITERAL);
}

/**
 * returns type for 2 character
 * @return: token type
 */
t_token_type	token_two(char *token)
{
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND_OUT);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp(token, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(token, "||", 2) == 0)
		return (OR);
	return (STR_LITERAL);
}

/**
 * Checks if a token is a built-in command that needs special handling
 * @param token: Command to check
 * @return: 1 if it's a built-in command, 0 if not
 */
int	is_builtin_command(char *token)
{
	int	siz_tok;

	siz_tok = ft_strlen(token);
	if (!token)
		return (0);
	// Check for exact matches of built-in commands
	if (ft_strncmp(token, "echo", siz_tok) == 0 || ft_strncmp(token, "cd",
			siz_tok) == 0 || ft_strncmp(token, "pwd", siz_tok) == 0
		|| ft_strncmp(token, "export", siz_tok) == 0 || ft_strncmp(token,
			"unset", siz_tok) == 0 || ft_strncmp(token, "env", siz_tok) == 0
		|| ft_strncmp(token, "exit", siz_tok) == 0)
	{
		return (1);
	}
	return (0);
}

/**
 * This decides what kind of type the token has
 * @param token: the token with the value
 * @param envp: environment variables
 * @return: token_type
 */
t_token_type	decide_token_type(char *token)
{
	if (!token || !*token)
		return (STR_LITERAL);
	if (is_builtin_command(token))
		return (CMD);
	if (token[0] == '-')
		return (FLAG);
	if (ft_strlen(token) == 2)
		return (token_two(token));
	if (ft_strlen(token) == 1)
		return (token_one(token));
	return (STR_LITERAL);
}
