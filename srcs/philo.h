/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:30:44 by nde-chab          #+#    #+#             */
/*   Updated: 2024/10/24 21:41:42 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		philosophe;
	int				id;
	int				bool_alive;
	long			last_eat;
	int				num_of_meal;
	int				time_to_eat;
	int				nb_philo;
	int				time_to_sleep;
	long			time_start;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	lock_last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	lock_eat;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	start;
	pthread_mutex_t	speak;
	pthread_mutex_t	lock_alive;
	long			time_start;
	int				all_alive;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_time;
	t_philo			philo[200];
}					t_data;

long				get_time_in_ms(void);
int					ft_atoi(const char *str);
int					ft_str_isdigit(char *str);
int					ft_verif_overflow(const char *str);
int					verif_argv(int ac, char **av);
void				init_data(int ac, char **av, t_data *data);
int					verif_argv(int ac, char **av);
int					for_1_philo(t_data *data);
void				*verif_alive(void *args);
void				creat_thread_mutex(t_data *data);
void				take_fork_pair(t_philo *philo);
void				take_fork_not_pair(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo, int bool);
void				eating(t_philo *philo);
void				ft_destroy_mutex(t_data *data);
void				start_waiting(t_philo *philo);
void				ft_usleep(int nb);
int					verif_meal(t_data *data);
void				stop_philo(t_data *data, int i, int bool);
int					veriff_all_alive(t_philo *philo);
void				ft_set_h(t_data *data);

#endif