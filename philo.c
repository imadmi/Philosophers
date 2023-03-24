/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:47:28 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/24 22:19:09 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char *av[])
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (0);
	if (check_args(ac, av))
	{
		ft_free(data);
		return (free(data), 0);
	}
	get_args(ac, av, data);
	if (init_data(data))
		return (free(data), 0);
	if (init_mutex(data))
		return (ft_free(data), 0);
	if (ft_thread(data))
		return (ft_free(data), 0);
	check_death(data->philos);
	if (ft_join(data))
		return (ft_free(data), 0);
	ft_free(data);
	return (0);
}
