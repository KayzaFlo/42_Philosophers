/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:11:16 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/15 16:52:41 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

sem_t	*semaphore;

void *routine(void *args)
{
	// char *str = "ah";

	sem_wait(semaphore);
	sleep(1);
	// write(1, str, 2);
	printf("Poke from thread %d\n", *(int*)args);
	sem_post(semaphore);
	free(args);
	return (NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t	th[4];
	int			i;

	semaphore = sem_open("/mysem", O_CREAT, 0666, 1);
	i = -1;
	while (++i < 4)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a))
			printf("Failed to create thread");
	}
	i = -1;
	while (++i < 4)
	{
		if (pthread_join(th[i], NULL))
			printf("Failed to join thread");
	}
	sem_close(semaphore);
	return 0;
}
