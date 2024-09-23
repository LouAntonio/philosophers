/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:42:35 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/23 13:54:58 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
			if ((current_timestamp() - (philo[i]).last_meal)
				> (main_program->t_die + 4))
			{
				main_program->is_dead = 1;
				printf("\e[1;31m%ldms philo %d is dead\n",
					current_timestamp() - philo->main->time, i + 1);
				exit(0);
			}
			i++;
		}
		usleep(100);
	}
}

void	join_threads(pthread_t *thread, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			perror("Error while joining threads");
			exit(1);
		}
		i++;
	}
}

void	destroy_mutexes(pthread_mutex_t *fork, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_destroy(&fork[i]) != 0)
		{
			perror("Error while joining threads");
			exit(1);
		}
		i++;
	}
}
