/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:24:12 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/07 13:47:46 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork", "");
	if (philo->main->n_philo == 1)
	{
		while (!get_is_dead(*philo->main))
			usleep(philo->main->t_die * 1000);
		pthread_mutex_lock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
}

void	right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork", "");
	if (philo->main->n_philo == 1)
	{
		while (!get_is_dead(*philo->main))
			usleep(philo->main->t_die * 1000);
		pthread_mutex_lock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
}

void	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
		left_fork(philo);
	else
		right_fork(philo);
}
