/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:27:19 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/11 21:45:55 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_h(t_data *data)
{
	int	i;

	i = 0;
	data->time_start = get_time_in_ms();
	while (i < data->nb_philo)
	{
		data->philo[i].last_eat = data->time_start;
		data->philo[i].time_start = data->time_start;
		i++;
	}
}

int	veriff_all_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_alive);
	if (philo->data->all_alive == 0)
		return (pthread_mutex_unlock(&philo->data->lock_alive), 0);
	pthread_mutex_unlock(&philo->data->lock_alive);
	return (1);
}

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
	ft_set_h(data);
	pthread_create(&data->philo[0].philosophe, NULL, test_1_philo,
		&data->philo[0]);
	pthread_join(data->philo[0].philosophe, NULL);
	return (0);
}
