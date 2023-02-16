/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:55:27 by fgeslin           #+#    #+#             */
/*   Updated: 2023/02/16 16:52:24 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
# include <pthread.h>

# define KNRM  "\x1B[m"
# define KBLD  "\x1B[1m"
# define KUND  "\x1B[4m"
# define KRST  "\x1B[5m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

typedef struct	s_philo_dat
{
    int count;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_to_eat;
}	t_philo_dat;

int	ft_atoi(const char *str);

#endif
