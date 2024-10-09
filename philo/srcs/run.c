/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:42:35 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/09 09:09:11 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_actions(t_philo *philo)
{
	if (philo->main->n_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork", "\e[0;35m");
		while (!get_is_dead(*philo->main))
			usleep(philo->main->t_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	else
	{
		take_forks(philo);
		print_message(philo, "is eating", "\033[1;32m");
		pthread_mutex_lock(philo->message);
		philo->last_meal = current_timestamp();
		pthread_mutex_unlock(philo->message);
		usleep(philo->main->t_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_message(philo, "is sleeping", "\e[0;36m");
		usleep(philo->main->t_sleep * 1000);
		print_message(philo, "is thinking", "\033[0;37m");
	}
}

void	*philo_routine(void	*arg)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)arg;
	if (get_t_meals(*philo->main))
	{
		while (!get_is_dead(*philo->main))
		{
			if (i++ != get_t_meals(*philo->main))
				philo_actions(philo);
			else
				break ;
		}
	}
	else
		while (!get_is_dead(*philo->main))
			philo_actions(philo);
	pthread_mutex_lock(philo->message);
	philo->check = 0;
	pthread_mutex_unlock(philo->message);
	return (NULL);
}

void	check_death(t_main *main, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < main->n_philo)
		{
			if ((int)(current_timestamp() - (philo[i]).last_meal)
				> ((main->t_die) + 5))
			{
				pthread_mutex_lock(&philo->main->main_mutex);
				main->is_dead = 1;
				if (main->is_dead == 1)
				{
					pthread_mutex_unlock(&philo->main->main_mutex);
					if (philo[i].check == 1)
						print_death(&philo[i], "died", "\033[0;37m\033[41m");
					return ;
				}
				pthread_mutex_unlock(&philo->main->main_mutex);
			}
		}
	}
}

void	join_threads(pthread_t *thread, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
			perror("Error while joining threads");
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
			perror("Error while joining threads");
		i++;
	}
}
