/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:37:29 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/12 13:45:25 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->speak);
	if (veriff_all_alive(philo))
		printf("%ld %d is eating\n", get_time_in_ms() - philo->time_start,
			philo->id);
	pthread_mutex_unlock(&philo->data->speak);
	pthread_mutex_lock(&philo->lock_last_eat);
	philo->last_eat = get_time_in_ms();
	pthread_mutex_unlock(&philo->lock_last_eat);
	if (veriff_all_alive(philo))
		ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_lock(&philo->lock_eat);
	philo->num_of_meal++;
	pthread_mutex_unlock(&philo->lock_eat);
}

void	take_fork_not_pair(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->data->speak);
	if (veriff_all_alive(philo))
		printf("%ld %d has taken a fork\n", get_time_in_ms()
			- philo->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->speak);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->speak);
	if (veriff_all_alive(philo))
		printf("%ld %d has taken a fork\n", get_time_in_ms()
			- philo->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->speak);
}

void	take_fork_pair(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->speak);
	if (veriff_all_alive(philo))
		printf("%ld %d has taken a fork\n", get_time_in_ms()
			- philo->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->speak);
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->data->speak);
	if (veriff_all_alive(philo))
		printf("%ld %d has taken a fork\n", get_time_in_ms()
			- philo->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->speak);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->speak);
	if (veriff_all_alive(philo))
		printf("%ld %d is sleeping\n", get_time_in_ms() - philo->time_start,
			philo->id);
	pthread_mutex_unlock(&philo->data->speak);
	if (veriff_all_alive(philo))
		ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->speak);
	if (veriff_all_alive(philo))
	{
		printf("%ld %d is thinking\n", get_time_in_ms() - philo->time_start,
			philo->id);
	}
	pthread_mutex_unlock(&philo->data->speak);
}
