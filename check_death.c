/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:03:01 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/22 10:41:09 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death_suite(int death, t_info *philo, size_t curr_time, int counter)
{
	if (death == DEAD)
	{
		pthread_mutex_lock(&philo[counter \
			% philo->data->nbr_of_philo].data->print);
		printf("%zu\t%d ", get_time() - curr_time, \
			philo[counter % philo->data->nbr_of_philo].philo_nbr);
		print_error("died ☠️");
		return (1);
	}
	return (0);
}

void	check_death(t_info *philo)
{
	size_t	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->change);
		if (get_time() - philo[i % philo->data->nbr_of_philo].\
			data->last_time_eating[philo->philo_nbr - 1] \
			> (size_t)philo[i % philo->data->nbr_of_philo].data->time_to_die)
		{
			if (check_death_suite(philo[i % philo->data->nbr_of_philo] \
				.data->die, philo, philo[i % philo->data->nbr_of_philo] \
				.data->currnt_time, i))
				return ;
			pthread_mutex_unlock(&philo->data->change);
			return ;
		}
		i++;
		pthread_mutex_unlock(&philo->data->change);
		usleep(1000);
	}
}
