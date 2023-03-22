/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:23:14 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/22 08:23:15 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_info *philo)
{
	print_state(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 994);
}

void	ft_thinking(t_info *philo)
{
	print_state(philo, THINKING);
}

void	ft_eat(t_info *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->philo_nbr - 1]);
	pthread_mutex_lock(&philo->data->forks[philo->philo_nbr \
		% philo->data->nbr_of_philo]);
	print_state(philo, FORK);
	print_state(philo, FORK);
	print_state(philo, EATING);
	usleep(philo->data->time_to_eat * 994);
	pthread_mutex_lock(&philo->data->change);
	philo->data->last_time_eating[philo->philo_nbr - 1] = get_time();
	pthread_mutex_unlock(&philo->data->change);
	pthread_mutex_unlock(&philo->data->forks[philo->philo_nbr \
		% philo->data->nbr_of_philo]);
	pthread_mutex_unlock(&philo->data->forks[philo->philo_nbr - 1]);
}
