/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:11:16 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/23 15:41:39 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	process(sem_t *sem, int id)
{
	sem_wait(sem);
	printf("processing %d...\n", id);
	sleep(1);
	sem_post(sem);
}

int main(int argc, char const *argv[])
{
	int		a;
	int		*ptr_a;
	pid_t	child_pid[3];
	int		i;
	sem_t	*sem;

	a = 0;
	ptr_a = &a;
	sem = sem_open("/mysem", O_CREAT, 0666, 1);
	sem_unlink("/mysem");
	i = 0;
	while (i < 3)
	{
		printf("create process %d\n", i);
		child_pid[i] = fork();
		if (!child_pid[i])
			return (process(sem, i), 0);
		i++;
	}
	i = -1;
	usleep(1500000);
	while (++i < 3)
		// waitpid (child_pid[i], NULL, 0);
		kill(child_pid[i], SIGTERM); // or SIGKILL
	printf("closing...\n");
	sem_close(sem);
	return 0;
}
