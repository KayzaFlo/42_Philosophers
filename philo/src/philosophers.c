/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:54:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/02/23 14:25:59 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*philo(void *vargp)
{
	static int	s = 0;
	int			*myid;

	myid = (int *)vargp;
	printf("Thread ID: %d, Static: %d\n", *myid, ++s);
	return (NULL);
}

void	parse(int argc, char *argv[], t_philo_dat *datas)
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
	else
		datas->nbr_to_eat = -1;
}

void	init_threads(pthread_t **tid, int nb, pthread_mutex_t **fid)
{
	int	i;
	
	*fid = malloc((nb+1) * sizeof(**fid));
	*tid = malloc(nb * sizeof(**tid));
	if (!(*tid))
		exit (-1);
	i = 0;
	while (i++ < nb)
		pthread_mutex_init(&(*fid)[i], NULL);
	i = 0;
	while (i++ < nb)
		pthread_create(&(*tid)[i], NULL, &philo, (void *)&(*tid)[i]);
	i = 0;
	while (i++ < nb)
		pthread_join((*tid)[i], NULL);
	i = 0;
	while (i++ < nb)
		pthread_mutex_destroy(&(*fid)[i]);
	free(*fid);
	free(*tid);
}

int	main(int argc, char *argv[])
{
	t_philo_dat		datas;
	pthread_t		*threads_id;
	pthread_mutex_t	*forks_id;

	parse(argc, argv, &datas);
	init_threads(&threads_id, datas.count, &forks_id);
	return (0);
}
