/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:06:57 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/01 12:30:59 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

// MAIN STRUCTURE
typedef struct s_main
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_meals;
	int				is_dead;
	int				all_eaten;
	unsigned long	time;
	pthread_mutex_t	main_mutex;
}					t_main;

// PHILOSOPHER STRUCTURE
typedef struct s_philo
{
	int				id;
	unsigned long	last_meal;
	int				meals;
	int				eaten_enouth;
	pthread_mutex_t	*message;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_main			*main;
}					t_philo;

// UTILS
int				ft_atoi(char *str);
int				check_args(int ac, char **av);
unsigned long	current_timestamp(void);
void			print_death(t_philo *philo, char *message, char *color);
void			print_message(t_philo *philo, char *message, char *color);

// INITIALIZATION
void			init_main(int ac, char **av, t_main *main);
int				init_threads(t_main *main,
					t_philo *philo, pthread_t *thread);
int				init_mutexes(t_main *main, pthread_mutex_t *fork,
					pthread_mutex_t print_locker);
int				allocate_resources(t_philo **philo, pthread_t **thread,
					pthread_mutex_t **fork, int n_philo);
void			init_philo(t_philo *philo, t_main *main,
					pthread_mutex_t *fork, pthread_mutex_t *print_locker);

// RUN
void			*philo_routine(void	*arg);
void			join_threads(pthread_t *thread, int n_philo);
void			check_death(t_main *main, t_philo *philo);
void			destroy_mutexes(pthread_mutex_t *fork, int n_philo);

// GETTERS AND SETTERS
int				get_is_dead(t_main main);
int				get_eaten_enouth(t_philo *philo);
int				get_t_meals(t_main main);
void			set_meal(t_philo *philo);

#endif