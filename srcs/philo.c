/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:30:38 by nde-chab          #+#    #+#             */
/*   Updated: 2024/09/11 18:59:44 by nde-chab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf("nb_philo time_to_die time_to_eat time_to_sleep\n"));
	if (verif_argv(ac, av) == 0)
		return (printf("error args\n"));
	init_data(ac, av, &data);
	if (data.nb_philo > 200)
		return (printf("max philo = 200\n"), 0);
	if (data.nb_philo == 1)
		return (for_1_philo(&data));
	else
		return (on_test_des_chose(&data));
	
}
