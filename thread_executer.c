/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_executer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:56:02 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/22 10:40:09 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		data->last_time_eating[data->philos->philo_nbr - 1] = get_time();
		pthread_create(&data->philos[i].thread_id, NULL, \
				&thread_executer, &data->philos[i]);
		i++;
	}
}

void	thread_executer_suite(t_info	*philo)
{
	ft_sleep(philo);
	ft_thinking(philo);
	usleep(100);
}

void	*thread_executer(void *philo_data)
{
	t_info	*philo;

	philo = (t_info *)philo_data;
	if (philo->philo_nbr % 2 == 1)
		usleep(500);
	while (1)
	{
		ft_eat(philo);
		pthread_mutex_lock(&philo->data->change);
		philo->ate++;
		if (philo->data->number_of_times_each_philosopher_must_eat != -1)
		{
			if (philo->ate > \
					philo->data->number_of_times_each_philosopher_must_eat)
			{
				philo->data->die = ALIVE;
				pthread_mutex_unlock(&philo->data->change);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&philo->data->change);
		thread_executer_suite(philo);
	}
	return (NULL);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->die = DEAD;
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			print_error("mutex error");
		data->philos[i].data = data;
		data->philos[i].ate = 1;
		data->philos[i].philo_nbr = i + 1;
		i++;
	}
	data->currnt_time = get_time();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->change, NULL);
}

void	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo && data->die != DEAD)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}
