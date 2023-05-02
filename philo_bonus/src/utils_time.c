/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:01:27 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/21 15:29:22 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <sys/time.h>

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	ft_msleep(uint64_t duration, t_env *env)
{
	uint64_t	start;

	start = get_time();
	while (!env->is_dead && !env->is_satiated)
	{
		if (get_time() - start >= duration)
			break ;
	}
}
