/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:31:20 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/15 17:10:28 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_status(char *msg, t_philo *philo)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&philo->env->printing);
	timestamp = get_time() - philo->env->start_time;
	if (!philo->env->is_dead && !philo->env->is_satiated)
		printf("%lu %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->env->printing);
}

int	print_error(char *msg, int i)
{
	write(2, msg, ft_strlen(msg));
	return (i);
}
