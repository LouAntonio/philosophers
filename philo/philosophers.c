/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:36:19 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/16 14:35:17 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	error_on_alocate(void)
{
	printf("Error while alocating memmory\n");
	exit(1);
}

unsigned long	current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_main(int ac, char **av, t_main **main_program)
{
    (*main_program)->n_philo = atoi(av[1]);
    (*main_program)->t_die = atoi(av[2]);
    (*main_program)->t_eat = atoi(av[3]);
    (*main_program)->t_sleep = atoi(av[4]);
    (*main_program)->t_meals = 0;
    (*main_program)->is_dead = 0;
    (*main_program)->all_eaten = 0;
    (*main_program)->time = current_timestamp();
    if (ac == 6)
        (*main_program)->t_meals = atoi(av[5]);
}


int	main(int ac, char **av)
{
	t_main			*main_program;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_locker;
	if (ac == 5 || ac == 6)
	{
		check_args(av);
		main_program = (t_main *)malloc(sizeof(t_main));
        if (!main_program)
        	error_on_alocate();
		init_main(ac, av, &main_program);
		printf("Time: %ld\n", main_program->time);
		philo = (t_philo *)malloc(sizeof(t_philo) * main_program->n_philo);
		thread = (pthread_t *)malloc(sizeof(pthread_t) * main_program->n_philo);
		fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo || !thread)
        	error_on_alocate();
		pthread_mutex_init(&fork, NULL);
		pthread_mutex_init(&print_locker, NULL);
	}
	else
		printf("Error\nCheck the number of params\n");
}
