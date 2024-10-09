/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:36:19 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/09 13:51:49 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

int	is_all_pos(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		if (ft_atoi(av[i]) < 1)
			return (0);
	return (1);
}

void	ac_error(void)
{
	printf("Error\nCheck the number of params\n./philosophers [n_philo]");
	printf(" [t_die] [t_eat] [t_sleep] [n_meals (optional)]\n");
}

void	run_and_exit(t_main *main, t_philo *philo,
	pthread_t *thread, pthread_mutex_t *fork)
{
	check_death(main, philo);
	join_threads(thread, main->n_philo);
	destroy_mutexes(fork, main->n_philo);
	free(philo);
	free(thread);
	free(fork);
}

int	main(int ac, char **av)
{
	t_main			main;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_locker;

	if (check_args(ac, av))
	{
		if (is_all_pos(av))
		{
			init_main(ac, av, &main);
			allocate_resources(&philo, &thread, &fork, main.n_philo);
			init_philo(philo, &main, fork, &print_locker);
			init_mutexes(&main, fork);
			init_threads(&main, philo, thread);
			run_and_exit(&main, philo, thread, fork);
		}
	}
	else
		ac_error();
}
