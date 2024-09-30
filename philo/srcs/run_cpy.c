/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:42:35 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/27 09:40:07 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_actions(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taking right right", "\e[0;35m");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taking left fork", "\e[0;35m");
	print_message(philo, "is eating", "\033[1;32m");
	set_meal(philo);
	philo->last_meal = current_timestamp();
	usleep(philo->main->t_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo, "is sleeping", "\e[0;36m");
	usleep(philo->main->t_sleep * 1000);
	print_message(philo, "is thinking", "\033[0;37m");
}

void	*philo_routine(void	*arg)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)arg;
	if (!get_t_meals(*philo->main))
		i = 1;
	while (!get_is_dead(*philo->main) && i != get_t_meals(*philo->main))
	{
		if (!get_eaten_enouth(philo))
			philo_actions(philo);
		else
			i++;
	}
	philo->main->all_eaten += 1;
}

void	check_death(t_main *main_program, t_philo *philo)
{
	int	i;
	int	dead;

	dead = 0;
	while (!get_is_dead(*main_program)
		&& (main_program->n_philo - main_program->all_eaten))
	{
		i = 0;
		while (i < main_program->n_philo)
		{
			if ((current_timestamp() - (philo[i]).last_meal)
				> (main_program->t_die))
			{
				main_program->is_dead = 1;
				print_message(philo, "is dead", "\033[0;37m\033[41m");
				break ;
			}
			i++;
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
