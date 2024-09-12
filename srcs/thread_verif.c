/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_verif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:19:44 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/12 13:48:49 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time_start = get_time_in_ms();
	data->all_alive = 1;
	if (ac == 6)
		data->nb_of_time = ft_atoi(av[5]);
	else
		data->nb_of_time = -1;
	while (i < data->nb_philo && i < 200)
	{
		data->philo[i].nb_philo = data->nb_philo;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].bool_alive = 1;
		data->philo[i].num_of_meal = 0;
		data->philo[i].last_eat = data->time_start;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i++].time_to_eat = data->time_to_eat;
	}
}

void	creat_mutex(t_data *data, int *i)
{
	pthread_mutex_init(&data->philo[*i].lock_eat, NULL);
	pthread_mutex_init(&data->philo[*i].right_fork, NULL);
	pthread_mutex_init(&data->philo[*i].lock_last_eat, NULL);
	*i += 1;
	if (*i < data->nb_philo)
		data->philo[*i].left_fork = &data->philo[*i - 1].right_fork;
}

void	*verif_alive(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->philo[i].lock_last_eat);
		if (get_time_in_ms() - data->philo[i].last_eat > data->time_to_die)
		{
			stop_philo(data, i, 0);
			break ;
		}
		pthread_mutex_unlock(&data->philo[i].lock_last_eat);
		if (verif_meal(data) == 1)
		{
			stop_philo(data, i, 1);
			break ;
		}
		i++;
		if (i >= data->nb_philo)
			i = 0;
		usleep(1);
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->start);
	thinking(philo);
	start_waiting(philo);
	while (veriff_all_alive(philo))
	{
		if (philo->id % 2 == 0)
			take_fork_pair(philo);
		else
			take_fork_not_pair(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	creat_thread_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		creat_mutex(data, &i);
	data->philo[0].left_fork = &data->philo[i - 1].right_fork;
	pthread_mutex_init(&data->speak, NULL);
	pthread_mutex_init(&data->lock_alive, NULL);
	pthread_mutex_init(&data->start, NULL);
	i = 0;
	pthread_mutex_lock(&data->start);
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].philosophe, NULL, routine,
			&data->philo[i]);
		i++;
	}
	ft_set_h(data);
	pthread_mutex_unlock(&data->start);
	verif_alive(data);
	i = 0;
	while (i < data->nb_philo)
		pthread_join(data->philo[i++].philosophe, NULL);
	return (ft_destroy_mutex(data));
}
