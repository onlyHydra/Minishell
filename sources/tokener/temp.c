/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:58:39 by schiper           #+#    #+#             */
/*   Updated: 2025/05/10 16:05:46 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "temp.h"
#include "libft.h"

int	handle_whitespace(const char *input, t_parse_state *state, char **envp)
{
	if (ft_is_whitespace(input[state->i]))
	{
		if (state->in_word)
		{
			process_token(input, state, envp);
			state->in_word = 0;
		}
		state->i++;
		return (1);
	}
	return (0);
}

int	handle_parsing_ops(const char *input, t_parse_state *state, char **envp)
{
	if (input[state->i] == '&' && input[state->i + 1] == '&')
		return (process_operator_token(state, "&&", AND, 2));
	if (input[state->i] == '|' && input[state->i + 1] == '|')
		return (process_operator_token(state, "||", OR, 2));
	if (input[state->i] == '|')
		return (process_operator_token(state, "|", PIPE, 1));
	if (input[state->i] == '>' && input[state->i + 1] == '>')
		return (process_operator_token(state, ">>", REDIRECT_APPEND, 2));
	if (input[state->i] == '<' && input[state->i + 1] == '<')
		return (process_operator_token(state, "<<", HEREDOC, 2));
	if (input[state->i] == '>')
		return (process_operator_token(state, ">", REDIRECT_OUT, 1));
	if (input[state->i] == '<')
		return (process_operator_token(state, "<", REDIRECT_IN, 1));
	return (0);
}

int	process_operator_token(t_parse_state *state, char *op, t_token_type type,
		int len)
{
	t_token	*token;

	if (state->in_word)
		process_token(NULL, state, state->envp);
	token = malloc(sizeof(t_token));
	token->value = ft_strndup(op, len);
	token->type = type;
	token->next = NULL;
	token->filepath = NULL;
	token->split_values = NULL;
	add_token_to_list(state->tokens, token);
	state->i += len;
	state->in_word = 0;
	if (type == REDIRECT_IN || type == REDIRECT_OUT || type == REDIRECT_APPEND
		|| type == HEREDOC)
		state->expect_filename = 1;
	return (1);
}

int	handle_quoted_text(const char *input, t_parse_state *state)
{
	t_token	*token;

	if ((input[state->i] == '\'' || input[state->i] == '"') && !state->in_quote)
	{
		state->in_quote = 1;
		state->quote_char = input[state->i];
		state->start = ++state->i;
		while (input[state->i] && input[state->i] != state->quote_char)
			state->i++;
		if (input[state->i] == '\0')
		{
			state->error = 1;
			return (1);
		}
		token = malloc(sizeof(t_token));
		token->value = ft_strndup(&input[state->start], state->i
				- state->start);
		token->type = STR_LITERAL;
		token->next = NULL;
		token->filepath = NULL;
		token->split_values = NULL;
		add_token_to_list(state->tokens, token);
		state->i++;
		state->in_quote = 0;
		state->in_word = 0;
		return (1);
	}
	return (0);
}

int	handle_regular_text(const char *input, t_parse_state *state, char **envp)
{
	if (!ft_is_whitespace(input[state->i]) && !ft_isoperator(input[state->i]))
	{
		if (!state->in_word)
			state->start = state->i;
		state->in_word = 1;
		state->i++;
		return (1);
	}
	return (0);
}

void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*cur;

	cur = *tokens;
	if (!cur)
	{
		*tokens = new_token;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new_token;
}

void	process_token(const char *input, t_parse_state *state, char **envp)
{
	if (!input || state->start >= state->i)
		return;
	t_token *token = malloc(sizeof(t_token));
	token->value = ft_strndup(&input[state->start], state->i - state->start);
	token->type = (state->expect_filename) ? FILENAME : CMD;
	token->next = NULL;
    is_string_command();
	token->filepath = NULL;
	token->split_values = NULL;
	add_token_to_list(state->tokens, token);
	state->in_word = 0;
	state->expect_filename = 0;
}
