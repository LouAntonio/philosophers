/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:42:35 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/04 16:38:39 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_actions(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork", "");
	if (philo->main->n_philo == 1)
	{
		while (!get_is_dead(*philo->main))
			usleep(philo->main->t_die * 1000);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "is eating", "");
	set_meal(philo);
	pthread_mutex_lock(philo->message);
	philo->last_meal = current_timestamp();
	pthread_mutex_unlock(philo->message);
	usleep(philo->main->t_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo, "is sleeping", "");
	usleep(philo->main->t_sleep * 1000);
	print_message(philo, "is thinking", "");
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
	philo->main->all_eaten += 1;
	philo->main->stop = 0;
	if (philo->main->all_eaten == philo->main->n_philo)
		philo->main->is_dead = 1;
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
				> (main->t_die))
			{
				pthread_mutex_lock(&philo->main->main_mutex);
				main->is_dead = 1;
				pthread_mutex_unlock(&philo->main->main_mutex);
				if (get_is_dead(*main) && philo[i].main->stop == 1)
					print_death(&philo[i], "died", "");
				return ;
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
