/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:06:28 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/09 09:09:21 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_philo(t_philo *philo, t_main *main,
	pthread_mutex_t *fork, pthread_mutex_t *print_locker)
{
	int	i;

	i = 0;
	pthread_mutex_init(print_locker, NULL);
	while (i < (*main).n_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = current_timestamp();
		philo[i].check = 1;
		philo[i].message = print_locker;
		philo[i].left_fork = &fork[i];
		philo[i].right_fork = &fork[(i + 1) % main->n_philo];
		philo[i].main = main;
		i++;
	}
}

void	init_main(int ac, char **av, t_main *main)
{
	main->n_philo = ft_atoi(av[1]);
	main->t_die = ft_atoi(av[2]);
	main->t_eat = ft_atoi(av[3]);
	main->t_sleep = ft_atoi(av[4]);
	main->t_meals = 0;
	main->is_dead = 0;
	main->time = current_timestamp();
	if (ac == 6)
		main->t_meals = ft_atoi(av[5]);
}

int	init_mutexes(t_main *main, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < main->n_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (perror("Error while initializating mutex"), 1);
		i++;
	}
	if (pthread_mutex_init(&main->main_mutex, NULL) != 0)
		return (perror("Error while initializating mutex"), 1);
	return (0);
}

int	init_threads(t_main *main, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < main->n_philo)
	{
		if (pthread_create(&thread[i], NULL, &philo_routine, &philo[i]) != 0)
			return (perror("Error while creating threads"), 1);
		usleep(100);
		i++;
	}
	return (0);
}

int	allocate_resources(t_philo **philo, pthread_t **thread,
	pthread_mutex_t **fork, int n_philo)
{
	*philo = (t_philo *)malloc(sizeof(t_philo) * n_philo);
	*thread = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
	*fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!(*philo) || !(*thread) || !(*fork))
		return (printf("Error while alocating memmory\n"), 1);
	return (0);
}
