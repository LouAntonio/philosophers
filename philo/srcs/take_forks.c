/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:24:12 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/07 16:20:04 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	left_first(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork", "\e[0;35m");
	pthread_mutex_lock(philo->right_fork);
}

void	right_first(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork", "\e[0;35m");
	pthread_mutex_lock(philo->left_fork);
}

void	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
		left_first(philo);
	else
		right_first(philo);
}
