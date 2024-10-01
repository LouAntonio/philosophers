/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:42:35 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/01 12:02:52 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_actions(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken right fork", "\033[0;35m");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken left fork", "\033[0;35m");
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
			if (i != get_t_meals(*philo->main))
				philo_actions(philo);
			else
			{
				printf("END\n\033[0;37m");
				break ;
			}
			i++;
		}
	}
	else
		while (!get_is_dead(*philo->main))
			philo_actions(philo);
	philo->main->all_eaten += 1;
	return (NULL);
}

void	check_death(t_main *main_program, t_philo *philo)
{
	int	i;
	int	j;

	j = 0;
	while (!get_is_dead(*main_program))
	{
		i = -1;
		while (++i < main_program->n_philo)
		{
			if ((int)(current_timestamp() - (philo[i]).last_meal)
				> (main_program->t_die))
			{
				main_program->is_dead = 1;
				if (get_is_dead(*main_program))
					print_death(&philo[i], "is dead", "\033[0;37m\033[41m");
				return ;
			}
			if ((philo[i]).main->all_eaten == 1)
				j++;
		}
		if (j == main_program->n_philo)
			return ;
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
