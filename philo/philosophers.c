/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:36:19 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/23 13:24:42 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	error_on_alocate(void)
{
	printf("Error while alocating memmory\n");
	exit(1);
}

void	*philo_routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_is_dead(*philo->main))
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taking right right", "\e[0;35m");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taking left fork", "\e[0;35m");
		print_message(philo, "is eating", "\033[1;32m");
		philo->last_meal = current_timestamp();
		usleep(philo->main->t_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_message(philo, "is sleeping", "\e[0;36m");
		usleep(philo->main->t_sleep * 1000);
		print_message(philo, "is thinking", "\033[0;31m");
	}
}

void	check_death(t_main *main_program, t_philo *philo)
{
	int	i;

	while (!get_is_dead(*main_program))
	{
		i = 0;
		while (i < main_program->n_philo)
		{
			if ((current_timestamp() - (philo[i]).last_meal) > (main_program->t_die + 4))
			{
				main_program->is_dead = 1;
				printf("\e[1;31m%ldms philo %d is dead\n", current_timestamp() - philo->main->time, i + 1);
				exit(0);
			}
			i++;
		}
		usleep(100);
	}
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

		philo = (t_philo *)malloc(sizeof(t_philo) * main_program.n_philo);
		thread = (pthread_t *)malloc(sizeof(pthread_t) * main_program.n_philo);
		fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * main_program.n_philo);
		if (!philo || !thread)
	    	error_on_alocate();

		init_philo(philo, &main_program, fork, &print_locker);
		init_mutexes(&main_program, fork, print_locker);
		init_threads(&main_program, philo, thread);
		check_death(&main_program, philo);
		int i = 0;
		while (i < main_program.n_philo)
		{
			if (pthread_join(thread[i], NULL) != 0)
			{
				perror("Error while joining threads");
				exit(1);
			}
			i++;
		}
		i = 0;
		while (i < main_program.n_philo)
		{
			if (pthread_mutex_destroy(&fork[i]) != 0)
			{
				perror("Error while joining threads");
				exit(1);
			}
			i++;
		}
	}
	else
		printf("Error\nCheck the number of params\n./philosophers [n_philo] [t_die] [t_eat] [t_sleep] [n_meals (optional)]\n");
}
