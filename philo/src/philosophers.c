/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:54:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/02/16 16:56:33 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void    parse(int argc, char *argv[], t_philo_dat *datas)
{
    if (argc < 5 || argc > 6)
    {		
        printf(KYEL "🟡 Usage:" KWHT KBLD " ./client " KNRM
            KUND "number_of_philosophers" KNRM " "
            KUND "time_to_die" KNRM " "
            KUND "time_to_eat" KNRM " "
            KUND "time_to_sleep" KNRM " "
            KUND "[number_of_times_each_philosopher_must_eat]" KNRM "\n");
        exit (-1);
    }
    datas->count = ft_atoi(argv[1]);
    datas->time_to_die = ft_atoi(argv[2]);
    datas->time_to_eat = ft_atoi(argv[3]);
    datas->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        datas->nbr_to_eat = ft_atoi(argv[5]);
}

int main(int argc, char *argv[])
{
    t_philo_dat datas;

    parse(argc, argv, &datas);
    return (0);
}
