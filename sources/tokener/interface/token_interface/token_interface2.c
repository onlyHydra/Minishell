/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:15:25 by schiper           #+#    #+#             */
/*   Updated: 2025/04/29 18:40:06 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Post-processes tokens to correctly identify commands
 * This is called after all tokens are created
 * @param tokens: The linked list of tokens
 * @param envp: Environment variables
 */
void	post_process_command_tokens(t_token *tokens, char **envp)
{
	t_token	*current;
	int		expecting_command;

	current = tokens;
	expecting_command = 1;
	while (current)
	{
		// After certain operators, we expect a command
		if (expecting_command && current->type == STR_LITERAL)
			if (is_string_command(current->value, envp))
				current->type = CMD;
		// Reset expectation after each token based on its type
		if (current->type == PIPE || current->type == REDIRECT_IN
			|| current->type == REDIRECT_OUT || current->type == APPEND_OUT
			|| current->type == HEREDOC || current->type == AND
			|| current->type == OR || current->type == SEMICOLON)
			expecting_command = 1;
		else
			expecting_command = 0;
		current = current->next;
	}
}

/**
 * This decides what kind of type the token has
 * @param token: the token with the value
 * @param envp: environment variables
 * @return: token_type
 */
t_token_type	decide_token_type(char *token, char **envp)
{
	if (is_string_command(token, envp))
		return (CMD);
	if (!token || !*token)
		return (STR_LITERAL);
	if (token[0] == '-')
		return (FLAG);
	if (ft_strlen(token) == 2)
		return (twochar_operator(token));
	if (ft_strlen(token) == 1)
		return (onechar_operator(token));
	if (has_env_vars(token))
		return (ENV_VAR);
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
	else if (c == '(')
		return (LPAREN);
	else if (c == ')')
		return (RPAREN);
	return (STR_LITERAL);
}

/**
 * @brief returns Type for 1 char operators like |,>,<,;
 * @param token : string to the char we handle at the moment
 * @return: token type
 */
t_token_type	onechar_operator(char *token)
{
	if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '>')
		return (REDIRECT_OUT);
	else if (token[0] == '<')
		return (REDIRECT_IN);
	else if (token[0] == ';')
		return (SEMICOLON);
	else if (token[0] == '(')
		return (LPAREN);
	else if (token[0] == ')')
		return (RPAREN);
	return (STR_LITERAL);
}
/**
 * returns type for 2 character operators '>>','<<','&&','||'
 * @param token : string to the char we handle at the moment
 * @return: token type
 */
t_token_type	twochar_operator(char *token)
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
