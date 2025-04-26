/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 03:03:47 by schiper           #+#    #+#             */
/*   Updated: 2025/04/25 18:02:19 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(TOKEN_STRUCT_H)
# define TOKEN_STRUCT_H
typedef enum e_token_type
{
	CMD,
	STR_LITERAL,
	REDIRECT_APPEND,
	APPEND_OUT,
	HEREDOC,
	ENV_VAR,
	AND,
	OR,
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
	struct s_token	*next;
}					t_token;

/**
 * Structure to combine parameters for process_segment
 * Struct for Input Handling
 */
typedef struct s_parse_params
{
	char			*input;
	t_token			**tokens;
	int				start;
	int				end;
	int				is_first;
	char			**envp;
	int				in_quote;
	char			quote_char;
	int				segment_start;
	int				segment_end;
	int				is_first_segment;
	int				exit_status;
}					t_parse_params;

typedef struct s_parsed_data
{
	t_token_type	*token;
	char			*data;
}					t_parsed_data;

/* Helper struct for tokenizer parse state */
/*
 * THis needs to be moved on Parser Header with First Occasion
 */
typedef struct s_parse_state
{
	int				i;
	int				start;
	int				in_word;
	int				error;
	int				is_first_token;
	int				in_quote;
	char			quote_char;
	t_token			**tokens;
}					t_parse_state;

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
 * @brief Advances the token pointer to the next token.
 *
 * This function moves the token pointer to the next token in the list,
 * effectively consuming the current token.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 */
void				advance_token(t_parsed_data **tokens);

/**
 * @brief Checks if the given token is an operator.
 *
 * This function determines whether the provided token represents an operator
 * (e.g., ||, &&, |).
 *
 * @param token A pointer to the token to check.
 * @return true or false based if the token is a operator
 */
int					is_operator_token(t_parsed_data *token);

t_token_type		decide_token_type(char *token, char **envp);
t_token_type		get_token_type(char c);
t_token_type		onechar_operator(char *token);
t_token_type		twochar_operator(char *token);
t_token	*process_tokenization_loop(char *input, t_parse_params *params);
t_token				*add_token(t_token **head, char *value, t_token_type type);

t_parsed_data		*allocate_parsed_data(t_token *tokens, int count);
t_parsed_data		*tokens_to_parsed_data(t_token *tokens);

#endif // TOKEN_STRUCT_H
