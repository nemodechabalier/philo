/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:30:28 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/11 16:37:31 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_verif_overflow(const char *str)
{
	long	i;
	long	result;

	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > INT_MAX)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	return (result * sign);
}

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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
		data->philo[i].time_start = data->time_start;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].bool_alive = 1;
		data->philo[i].num_of_meal = 0;
		data->philo[i].last_eat = data->time_start;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i++].time_to_eat = data->time_to_eat;
	}
}

int	verif_argv(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_str_isdigit(av[i]) == 0 || ft_verif_overflow(av[i]) == 0
			|| ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}