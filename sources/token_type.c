
#include "header.h"

/**
 * return type for 1 character
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
 * This decides what kind of type the token has
 * @param token: the token with the value
 * @param envp: environment variables
 * @return: token_type
 */
t_token_type	decide_token_type(char *token, char **envp)
{
	if (!token || !*token)
		return (CMD);
	if (executable(token, envp) == 0)
		return (CMD);
	if (token[0] == '-')
		return (FLAG);
	if (ft_strlen(token) == 2)
		return (token_two(token));
	if (ft_strlen(token) == 1)
		return (token_one(token));
	return (STR_LITERAL);
}

/**
 * Get the token type based on the character
 * @param c: The character to check
 * @return: The token type enum value
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
	else
		return (CMD);
}
