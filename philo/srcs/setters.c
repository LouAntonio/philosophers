/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:59:24 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/25 12:48:56 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	set_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->main_mutex);
	philo->meals += 1;
	if (philo->meals == philo->main->t_meals)
		philo->eaten_enouth = 1;
	pthread_mutex_unlock(&philo->main->main_mutex);
}

void	set_eaten_enouth(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->main_mutex);
	philo->eaten_enouth = 1;
	pthread_mutex_unlock(&philo->main->main_mutex);
}
