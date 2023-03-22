/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:48:10 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/22 10:50:31 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (4 < ac && ac < 7)
	{
		while (av[++i])
		{
			if (ft_atoi(av[i]) <= 0 && !ft_digit(ft_atoi(av[i])))
				return (print_error("Input error"));
		}
	}
	else
		return (print_error(ERR_USAGE));
	return (0);
}

void	get_args(int ac, char **av, t_data *data)
{
	data->nbr_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
}

int	init_data(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	if (!data->forks)
		return (print_error("malloc error"));
	data->philos = malloc(sizeof(t_info) * data->nbr_of_philo);
	if (!data->philos)
		return (print_error("malloc error"));
	data->last_time_eating = malloc (sizeof(size_t) * data->nbr_of_philo);
	if (!data->last_time_eating)
		return (print_error("malloc error"));
	return (0);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->change);
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
	free(data->last_time_eating);
	free(data);
}
