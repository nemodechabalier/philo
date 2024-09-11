/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:19:44 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/11 18:58:32 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test_1_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	printf("%d %d has taken a fork\n", 0, philo->id);
	while (get_time_in_ms() - philo->last_eat < philo->data->time_to_die)
	{
	}
	printf("%ld %d died\n", get_time_in_ms() - philo->time_start, philo->id);
	return (NULL);
}

int	for_1_philo(t_data *data)
{
	pthread_create(&data->philo[0].philosophe, NULL, test_1_philo,
		&data->philo[0]);
	pthread_join(data->philo[0].philosophe, NULL);
	return (0);
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
	}
	return (NULL);
}

void	*test_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	start_waiting(philo);
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			if (take_fork_pair(philo) == 0)
				break ;
		}
		else
		{
			if (take_fork_not_pair(philo) == 0)
				break ;
		}
		if (eating(philo) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
		if (thinking(philo) == 0)
			break ;
	}
	return (NULL);
}

int	on_test_des_chose(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->philo[i].lock_eat, NULL);
		pthread_mutex_init(&data->philo[i].right_fork, NULL);
		pthread_mutex_init(&data->philo[i++].lock_last_eat, NULL);
		if (i < data->nb_philo)
			data->philo[i].left_fork = &data->philo[i - 1].right_fork;
	}
	data->philo[0].left_fork = &data->philo[i - 1].right_fork;
	pthread_mutex_init(&data->speak, NULL);
	pthread_mutex_init(&data->lock_alive, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].philosophe, NULL, test_philo,
			&data->philo[i]);
		i++;
	}
	verif_alive(data);
	i = 0;
	while (i < data->nb_philo)
		pthread_join(data->philo[i++].philosophe, NULL);
	return (ft_destroy_mutex(data), 0);
}
