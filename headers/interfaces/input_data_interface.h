/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_data_interface.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:55:09 by schiper           #+#    #+#             */
/*   Updated: 2025/04/29 15:59:59 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(INPUT_DATA_INTERFACE_H)
# define INPUT_DATA_INTERFACE_H

# include "models/input_data_struct.h"

/**
 * @brief Free's the t_parse_state struct that was allocated
 * @param state : struct to the  be freed
 */
void	free_state_struct(t_parse_state *state);
/**
 * @brief Free's the t_parse_params struct that was allocated
 * @param params : struct to the be freed
 */
void	free_params_struct(t_parse_params *params);
/**
 * @brief : Free's parsed_data up to a mentioned index
 * @param parsed_data : pointer to t_parsed_data struct used for parsing
 * @oaran up_to_index : valid position in parsed_date >=0 and <= len_of(parsed_data)
 */
void	free_parsed_data_up_to(t_parsed_data *parsed_data, int up_to_index);

/**
 * @brief : Free's parsed_data on error state
 * @param parsed_data : pointer to t_parsed_data struct used for parsing
 * @param index : valid position in parsed_data >= 0 and <= len_of(parsed_data)
 * @param free_token : flag to signal free-ing tokens .
 */
void	free_parsed_data_on_error(t_parsed_data *parsed_data, int index,
			int free_token);

#endif // INPUT_DATA_INTERFACE_H
