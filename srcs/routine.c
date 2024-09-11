/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:37:29 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/11 19:14:15 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	veriff_all_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_alive);
	if (philo->data->all_alive == 0)
		return (pthread_mutex_unlock(&philo->data->lock_alive), 0);
	pthread_mutex_unlock(&philo->data->lock_alive);
	return (1);
}

int	eating(t_philo *philo)
{
	if (veriff_all_alive(philo))
	{
		pthread_mutex_lock(&philo->data->speak);
		if (veriff_all_alive(philo))
			printf("%ld %d is eating\n", get_time_in_ms() - philo->time_start,
				philo->id);
		pthread_mutex_unlock(&philo->data->speak);
		pthread_mutex_lock(&philo->lock_last_eat);
		philo->last_eat = get_time_in_ms();
		pthread_mutex_unlock(&philo->lock_last_eat);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_lock(&philo->lock_eat);
		philo->num_of_meal++;
		pthread_mutex_unlock(&philo->lock_eat);
		return (1);
	}
	else
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(&philo->right_fork), 0);
}

int	take_fork_not_pair(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	if (veriff_all_alive(philo))
	{
		pthread_mutex_lock(&philo->data->speak);
		if (veriff_all_alive(philo))
			printf("%ld %d has taken a fork\n", get_time_in_ms()
				- philo->time_start, philo->id);
		pthread_mutex_unlock(&philo->data->speak);
	}
	else
		return (pthread_mutex_unlock(&philo->right_fork), 0);
	pthread_mutex_lock(philo->left_fork);
	if (veriff_all_alive(philo))
	{
		pthread_mutex_lock(&philo->data->speak);
		if (veriff_all_alive(philo))
			printf("%ld %d has taken a fork\n", get_time_in_ms()
				- philo->time_start, philo->id);
		pthread_mutex_unlock(&philo->data->speak);
		return (1);
	}
	else
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(&philo->right_fork), 0);
}

int	take_fork_pair(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (veriff_all_alive(philo))
	{
		pthread_mutex_lock(&philo->data->speak);
		if (veriff_all_alive(philo))
			printf("%ld %d has taken a fork\n", get_time_in_ms()
				- philo->time_start, philo->id);
		pthread_mutex_unlock(&philo->data->speak);
	}
	else
		return (pthread_mutex_unlock(philo->left_fork), 0);
	pthread_mutex_lock(&philo->right_fork);
	if (veriff_all_alive(philo))
	{
		pthread_mutex_lock(&philo->data->speak);
		if (veriff_all_alive(philo))
			printf("%ld %d has taken a fork\n", get_time_in_ms()
				- philo->time_start, philo->id);
		pthread_mutex_unlock(&philo->data->speak);
		return (1);
	}
	else
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(&philo->right_fork), 0);
}

int	sleeping(t_philo *philo)
{
	long	time;

	if (veriff_all_alive(philo))
	{
		pthread_mutex_lock(&philo->data->speak);
		if (veriff_all_alive(philo))
			printf("%ld %d is sleeping\n", get_time_in_ms() - philo->time_start,
				philo->id);
		pthread_mutex_unlock(&philo->data->speak);
		time = get_time_in_ms();
		ft_usleep(philo->time_to_sleep);
		return (1);
	}
	else
		return (0);
}

int	thinking(t_philo *philo)
{
	if (veriff_all_alive(philo))
	{
		pthread_mutex_lock(&philo->data->speak);
		printf("%ld %d is thinking\n", get_time_in_ms() - philo->time_start,
			philo->id);
		pthread_mutex_unlock(&philo->data->speak);
		return (1);
	}
	else
		return (0);
}