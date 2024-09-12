/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mutex_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:39:24 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/12 13:55:29 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int nb)
{
	long	time;

	time = get_time_in_ms();
	while (get_time_in_ms() - time < nb)
	{
		usleep(1);
	}
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].lock_eat);
		pthread_mutex_destroy(&data->philo[i].right_fork);
		pthread_mutex_destroy(&data->philo[i++].lock_last_eat);
	}
	pthread_mutex_destroy(&data->start);
	pthread_mutex_destroy(&data->lock_alive);
	pthread_mutex_destroy(&data->speak);
}

void	start_waiting(t_philo *philo)
{
	if (philo->nb_philo % 2)
	{
		if (philo->id != 1 && philo->id % 2)
			ft_usleep(philo->time_to_eat / 2);
		else if (philo->id % 2 == 0)
			ft_usleep((philo->time_to_eat / 2) + 1);
	}
	else
	{
		if (philo->id % 2 == 0)
			ft_usleep(philo->time_to_eat / 2);
	}
}

int	verif_meal(t_data *data)
{
	int	i;

	i = 0;
	if (data->nb_of_time == -1)
		return (0);
	else
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philo[i].lock_eat);
			if (data->nb_of_time > data->philo[i].num_of_meal)
				return (pthread_mutex_unlock(&data->philo[i].lock_eat), 0);
			pthread_mutex_unlock(&data->philo[i].lock_eat);
			i++;
		}
	}
	return (1);
}

void	stop_philo(t_data *data, int i, int bool)
{
	pthread_mutex_lock(&data->speak);
	pthread_mutex_lock(&data->lock_alive);
	data->all_alive = 0;
	pthread_mutex_unlock(&data->lock_alive);
	if (bool == 0)
		printf("%ld %d died\n", get_time_in_ms() - data->time_start, i + 1);
	else
		printf("%ld all philo ate\n", get_time_in_ms() - data->time_start);
	pthread_mutex_unlock(&data->speak);
	if (bool == 0)
		pthread_mutex_unlock(&data->philo[i].lock_last_eat);
}
