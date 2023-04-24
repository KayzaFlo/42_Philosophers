/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:54:41 by fgeslin           #+#    #+#             */
/*   Updated: 2023/03/24 12:24:05 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	wait_for_end(t_philo *philos, t_env *env)
{
	int	i;
	int	satiated_count;

	satiated_count = 0;
	while (satiated_count != env->count)
	{
		i = -1;
		satiated_count = 0;
		while (++i < env->count && !env->is_dead)
		{
			if ((int)(get_time() - philos[i].last_ate) > env->time_to_die)
			{
				// print_status("died", &philos[i]);
				env->is_dead = 1; //just set env.is_dead in main process not children
				return ;
			}
			if (env->max_eat_count && i < env->count)
				if (philos[i].ate_count >= env->max_eat_count)
					satiated_count++;
		}
	}
	printf("Each philosopher ate at least %d time(s).\n", env->max_eat_count);
	env->is_satiated = 1;
}

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static int		nbr = 0;
	static int		count = 0;
	static pid_t	client_pid = 0;

	(void)ucontext;
	if (info->si_pid)
		client_pid = info->si_pid;
	if (client_pid == getpid() || !client_pid)
	{
		printf(KRED "🔴 Error:" KWHT " Infinite PID call\n");
		exit (-1);
	}
	nbr <<= 1;
	nbr |= (sig == SIGUSR1);
	count = (count + 1) % 32;
	if (!count)
	{
		printf("(handler) sig: %d\n", nbr);
		fflush(stdout);
		nbr = 0;
	}
	kill(client_pid, SIGUSR2);
}

static void	init_sigs()
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit (-1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit (-1);
}

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	t_env			env;

	if (argc < 5 || argc > 6)
		return (print_error("🟡 Usage: " KWHT KBLD "./client " KNRM
				KUND "number_of_philosophers" KNRM " " KUND "time_to_die" KNRM
				" " KUND "time_to_eat" KNRM " " KUND "time_to_sleep" KNRM " "
				KUND "[nbr_of_times_each_philosopher_must_eat]" KNRM "\n", 0));
	if (!parse_params(argc, argv, &env))
		return (print_error("🟡 Usage: " KWHT "Incorrect parameters.\n", 0));
	philos = malloc(env.count * sizeof(*philos));
	if (!philos)
		return (print_error("🔴 Error in Alloc!\n", 1));
		
	init_sigs();

	if (process_create(philos, &env))
		return (1);
	wait_for_end(philos, &env);
	if (process_exit(philos, &env))
		return (1);
	free(philos);
	return (0);
}
