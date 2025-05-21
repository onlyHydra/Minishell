/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_data_struct.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:42:48 by schiper           #+#    #+#             */
/*   Updated: 2025/05/21 21:29:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(INPUT_DATA_STRUCT_H)
# define INPUT_DATA_STRUCT_H

# include "token_struct.h"

typedef struct s_parse_state
{
	int			i;
	int			start;
	int			in_word;
	int			is_first_token;
	int			in_quote;
	char		quote_char;
	int			error;
	int			expect_filename;
	char		*filepath;
	char		**envp;
	t_token		**tokens;
	int			exit_status;
}				t_parse_state;

typedef struct s_parse_params
{
	char		*input;
	int			segment_start;
	int			segment_end;
	int			is_first_segment;
	char		*filepath;
	t_token		**tokens;
	char		**envp;
	int			exit_status;
}				t_parse_params;

#endif // INPUT_DATA_STRUCT_H
