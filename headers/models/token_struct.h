/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 03:03:47 by schiper           #+#    #+#             */
/*   Updated: 2025/05/02 19:08:34 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(TOKEN_STRUCT_H)
# define TOKEN_STRUCT_H
# include <stdio.h>

typedef enum e_token_type
{
	CMD,
	STR_LITERAL,
	FILENAME,
	REDIRECT_APPEND,
	HEREDOC,
	ENV_VAR,
	AND,
	OR,
	WILDCARD = '*',
	LPAREN = '(',
	RPAREN = ')',
	FLAG = '-',
	PIPE = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	SEMICOLON = ';',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
}					t_token_type;

typedef struct s_token
{
	char			*value;
	char			**split_values;
	t_token_type	type;
	char			*filepath;
	struct s_token	*next;
}					t_token;

typedef struct s_parsed_data
{
	t_token_type	*token;
	char			*data;
	char			*filepath;
}					t_parsed_data;

/* Token Navigation */
/*tokener_helper1.c*/

/**
 * @brief Peeks at the next token without advancing the token pointer.
 *
 * This function allows the parser to inspect the next token in the list
 * without consuming it.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the next token, or NULL if no tokens are available.
 */
t_parsed_data		*peek_token(t_parsed_data **tokens);

/**
 * @brief Peeks at the next token label without advancing the token pointer.
 *
 * This function allows the parser to inspect the next token label in the list
 * without consuming it.
 *
 * @param data A double pointer to the list of parsed tokens.
 * @return A pointer to the token label, or NULL if no labels are available.
 */
t_token_type		*peek_token_label(t_parsed_data **data);

/**
 * @brief Advances the token pointer to the next token.
 *
 * This function moves the token pointer to the next token in the list,
 * effectively consuming the current token.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 */
void				advance_token(t_parsed_data **tokens);
int					is_operator_token(t_parsed_data *token);
int					is_redir_token_type(t_token_type type);
int					is_label_argv(t_token_type *type);

// t_token_type		decide_token_type(char *token, char **envp);
t_token_type		get_token_type(char c);
t_token_type		onechar_operator(char *token);
t_token_type		twochar_operator(char *token);

t_token				*add_token(t_token **head, char *value, t_token_type type);

t_parsed_data		*tokens_to_parsed_data(t_token *tokens);
t_token				*process_input(char *input, char **envp);

#endif // TOKEN_STRUCT_H
