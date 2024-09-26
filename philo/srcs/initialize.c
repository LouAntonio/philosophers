/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:06:28 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/23 13:53:45 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_philo(t_philo *philo, t_main *main_program,
	pthread_mutex_t *fork, pthread_mutex_t *print_locker)
{
	int	i;

	i = 0;
	while (i < (*main_program).n_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = current_timestamp();
		philo[i].meals = 0;
		philo[i].eaten_enouth = 0;
		philo[i].message = print_locker;
		philo[i].left_fork = &fork[i];
		philo[i].right_fork = &fork[(i + 1) % main_program->n_philo];
		philo[i].main = main_program;
		i++;
	}
}

void	init_main(int ac, char **av, t_main *main_program)
{
	main_program->n_philo = ft_atoi(av[1]);
	main_program->t_die = ft_atoi(av[2]);
	main_program->t_eat = ft_atoi(av[3]);
	main_program->t_sleep = ft_atoi(av[4]);
	main_program->t_meals = 0;
	main_program->is_dead = 0;
	main_program->all_eaten = 0;
	main_program->time = current_timestamp();
	if (ac == 6)
		main_program->t_meals = ft_atoi(av[5]);
}

void	init_mutexes(t_main *main_program, pthread_mutex_t *fork,
	pthread_mutex_t print_locker)
{
	int	i;

	i = 0;
	while (i < main_program->n_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			perror("Error while initializating mutex");
			exit(1);
		}
		i++;
	}
	if (pthread_mutex_init(&main_program->main_mutex, NULL) != 0)
	{
		perror("Error while initializating mutex");
		exit(1);
	}
	if (pthread_mutex_init(&print_locker, NULL) != 0)
	{
		perror("Error while initializating mutex");
		exit(1);
	}
}

void	init_threads(t_main *main_program, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < main_program->n_philo)
	{
		if (pthread_create(&thread[i], NULL, &philo_routine, &philo[i]) != 0)
		{
			perror("Error while creating threads");
			exit(1);
		}
		usleep(100);
		i++;
	}
}

void	allocate_resources(t_philo **philo, pthread_t **thread,
	pthread_mutex_t **fork, int n_philo)
{
	*philo = (t_philo *)malloc(sizeof(t_philo) * n_philo);
	*thread = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
	*fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!(*philo) || !(*thread) || !(*fork))
		error_on_alocate();
}
