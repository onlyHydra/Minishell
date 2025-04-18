/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Apply pre-identified command flags to tokens
 * @param tokens: The token list
 * @param cmd_flags: Array of command flags
 */
void apply_command_flags(t_token *tokens, int *cmd_flags)
{
	t_token *current = tokens;
	// int token_idx = 0;
	int cmd_idx = 0;
	int in_cmd_position = 1; // Start at a command position
	
	while (current)
	{
		// If we're at a position where a command could appear
		if (in_cmd_position)
		{
			if (cmd_flags[cmd_idx])
				current->type = CMD;
			cmd_idx++;
			in_cmd_position = 0;
		}
		
		// Check if next token would be in command position
		if (current->type == PIPE || current->type == SEMICOLON)
			in_cmd_position = 1;
		
		current = current->next;
		// token_idx++;
	}
}

/**
 * Pre-process argv to identify commands before full tokenization
 * @param argv: The command line arguments
 * @return: Array of command types (1 for CMD, 0 for others)
 */
int *pre_identify_commands(char **argv)
{
    int i = 0;
    int *cmd_flags;
    
    if (!argv)
        return NULL;
    
    // Count arguments
    while (argv[i])
        i++;
    
    // Allocate flags array
    cmd_flags = malloc(sizeof(int) * (i + 1));
    if (!cmd_flags)
        return NULL;
    
    // Initialize all flags to 0 (not commands)
    for (int j = 0; j <= i; j++)
        cmd_flags[j] = 0;
    
    i = 0;
    while (argv[i])
    {
        // First arg or after pipe/semicolon is potentially a command
        if (i == 0 || is_operator_string(argv[i-1]))
        {
            // Check PATH and direct executable
            if (is_command_in_path(argv[i]) || access(argv[i], X_OK) == 0)
                cmd_flags[i] = 1; // Mark as command
        }
        i++;
    }
    
    return cmd_flags;
}

/**
 * Tokenize the argv input with command identification
 * @param argv: The command line arguments
 * @return: Parsed data array
 */
t_parsed_data *tokenize_data(char **argv)
{
    int *cmd_flags;
    int total_len;
    char *input_str;
    t_token *tokens;
    
    if (!argv || !argv[1])
        return NULL;
    
    // First identify commands before concatenation
    cmd_flags = pre_identify_commands(argv);
    if (!cmd_flags)
        return NULL;
    
    // Concatenate arguments
    total_len = calculate_total_length(argv);
    input_str = concatenate_arguments(argv, total_len);
    if (!input_str)
    {
        free(cmd_flags);
        return NULL;
    }
    
    // Tokenize the concatenated string
    tokens = tokenize_string(input_str);
    free(input_str);
    
    if (!tokens)
    {
        free(cmd_flags);
        return NULL;
    }
    
    // Apply command flags to tokens
    apply_command_flags(tokens, cmd_flags);
    free(cmd_flags);
    
    return tokens_to_parsed_data(tokens);
}


