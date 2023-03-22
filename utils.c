/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:55:19 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/22 11:02:20 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = sign * -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	if(str[i]  && (str[i] < '0' || str[i] > '9'))
		return (print_error("err"));
	return (num * sign);
}

int	print_error(char *str)
{
	printf("\033[1m\033[31m%s\n", str);
	return (-1);
}

void	print_state(t_info *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu\t%d %s\n", get_time() - philo->data->currnt_time, \
		philo->philo_nbr, str);
	pthread_mutex_unlock(&philo->data->print);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
