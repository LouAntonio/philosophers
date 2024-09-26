/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:59:17 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/25 12:49:18 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_is_dead(t_main main_program)
{
	int	value;

	pthread_mutex_lock(&main_program.main_mutex);
	value = main_program.is_dead;
	pthread_mutex_unlock(&main_program.main_mutex);
	return (value);
}

int	get_eaten_enouth(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->main->main_mutex);
	value = philo->eaten_enouth;
	pthread_mutex_unlock(&philo->main->main_mutex);
	return (value);
}

int	get_t_meals(t_main main_program)
{
	int	value;

	pthread_mutex_lock(&main_program.main_mutex);
	value = main_program.t_meals;
	pthread_mutex_unlock(&main_program.main_mutex);
	return (value);
}
