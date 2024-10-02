/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:42:35 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/02 11:28:06 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_actions(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork", "\033[0;35m");
	if (philo->main->n_philo == 1)
	{
		usleep(philo->main->t_die * 1001);
		pthread_mutex_unlock(philo->right_fork);
		philo->main->is_dead = 1;
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork", "\033[0;35m");
	print_message(philo, "is eating", "\033[1;32m");
	set_meal(philo);
	philo->last_meal = current_timestamp();
	usleep(philo->main->t_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo, "is sleeping", "\033[0;36m");
	usleep(philo->main->t_sleep * 1000);
	print_message(philo, "is thinking", "\033[0;37m");
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
	philo->main->all_eaten += 1;
	printf("%d\n", philo->main->all_eaten);
	return (NULL);
}

void	check_death(t_main *main, t_philo *philo)
{
	int	i;

	while (!get_is_dead(*main))
	{
		i = -1;
		while (++i < main->n_philo)
		{
			if ((int)(current_timestamp() - (philo[i]).last_meal)
				> (main->t_die))
			{
				main->is_dead = 1;
				if (get_is_dead(*main) && main->all_eaten != main->n_philo)
				{
					print_death(&philo[i], "died", "\033[0;37m\033[41m");
					return ;
				}
			}
		}
		if (main->all_eaten == main->n_philo)
			return ;
	}
	return ;
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
