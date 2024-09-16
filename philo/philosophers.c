/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:36:19 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/16 10:12:33 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	init_main(int ac, char *av, t_main *main_program)
{
	main_program->n_philo = atoi(av[1]);
	main_program->t_die = atoi(av[2]);
	main_program->t_eat = atoi(av[3]);
	main_program->t_sleep = atoi(av[4]);
	main_program->t_meals = 0;
	main_program->t_meals = 0;
	main_program->t_meals = 0;
	main_program->t_meals = 0;
	if (ac == 6)
		main_program->t_meals = atoi(av[5]);
}

int	main(int ac, char **av)
{
	t_main			*main_program;
	t_philo			*philo;
	pthread			*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_locker;

	if (ac == 5 || ac == 6)
	{
		check_args(av);
		init_main(ac, av, &main_program);
		philo = (t_philo *)malloc(sizeof(t_philo) * main_program->n_philo);
		thread = (pthread *)malloc(sizeof(pthread) * main_program->n_philo);
		pthread_mutex_init(&fork, NULL);
		pthread_mutex_init(print_locker, NULL);
	}
	else
		printf("Error\nCheck the number of params\n");
}
