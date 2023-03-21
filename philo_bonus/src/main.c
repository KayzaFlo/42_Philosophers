/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:11:16 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/21 15:21:21 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

sem_t	*semaphore;

void *routine2(void *args)
{
	sem_wait(semaphore);
	sleep(1);
	printf("Poke from thread %d\n", *(int*)args);
	sem_post(semaphore);
	free(args);
	return (NULL);
}

void	init()
{
	pthread_t	th[4];
	int			i;
	
	semaphore = sem_open("/mysem", O_CREAT, 0666, 1);
	sem_unlink("/mysem");
	sem_getvalue(semaphore, &i);
	printf("%d\n", i);
	i = -1;
	while (++i < 4)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine2, a))
			printf("Failed to create thread");
	}
	i = -1;
	while (++i < 4)
	{
		if (pthread_join(th[i], NULL))
			printf("Failed to join thread");
	}
	// sem_close(semaphore);
}

int main(int argc, char const *argv[])
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid)
	{
		while (child_pid == waitpid (-1, NULL, 0))
			continue ;
		sem_close(semaphore);
	}
	else
		init();
	return 0;
}
