/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:31:20 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/24 11:58:45 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_status(char *msg, t_env *env, int i)
{
	unsigned long	timestamp;

	timestamp = get_time() - env->start_time;
	// if (!philo->env->is_dead && !philo->env->is_satiated)
		printf("%lu %d %s\n", timestamp, i, msg);

}

int	print_error(char *msg, int i)
{
	write(2, msg, ft_strlen(msg));
	return (i);
}
