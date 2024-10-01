/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:36:19 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/01 12:03:16 by lantonio         ###   ########.fr       */
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

void	run_and_exit(t_main *main_program, t_philo *philo,
	pthread_t *thread, pthread_mutex_t *fork)
{
	check_death(main_program, philo);
	join_threads(thread, main_program->n_philo);
	destroy_mutexes(fork, main_program->n_philo);
	free(philo);
	free(thread);
	free(fork);
}

int	main(int ac, char **av)
{
	t_main			main_program;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_locker;

	if (check_args(ac, av))
	{
		if (is_all_pos(av))
		{
			init_main(ac, av, &main_program);
			if (!allocate_resources(&philo, &thread, &fork, main_program.n_philo))
			{
				init_philo(philo, &main_program, fork, &print_locker);
				if (!init_mutexes(&main_program, fork, print_locker)
					&& !init_threads(&main_program, philo, thread))
					run_and_exit(&main_program, philo, thread, fork);
			}
		}
	}
	else
		ac_error();
}
