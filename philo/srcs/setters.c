/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:59:24 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/13 14:38:57 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	set_sleep(t_main *main, int value)
{
	pthread_mutex_lock(main->main_mutex);
	main->t_sleep = value;
	pthread_mutex_unlock(main->main_mutex);
}

void	set_dead(t_main *main, int value)
{
	pthread_mutex_lock(main->main_mutex);
	main->t_dead = value;
	pthread_mutex_unlock(main->main_mutex);
}
