/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:36:19 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/23 13:50:17 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	error_on_alocate(void)
{
	printf("Error while alocating memmory\n");
	exit(1);
}

int	main(int ac, char **av)
{
	t_main			main_program;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_locker;

	if (ac == 5 || ac == 6)
	{
		check_args(av);
		init_main(ac, av, &main_program);
		allocate_resources(&philo, &thread, &fork, main_program.n_philo);
		init_philo(philo, &main_program, fork, &print_locker);
		init_mutexes(&main_program, fork, print_locker);
		init_threads(&main_program, philo, thread);
		check_death(&main_program, philo);
		join_threads(thread, main_program.n_philo);
		destroy_mutexes(fork, main_program.n_philo);
	}
	else
	{
		printf("Error\nCheck the number of params\n./philosophers [n_philo]");
		printf(" [t_die] [t_eat] [t_sleep] [n_meals (optional)]\n");
	}
}
