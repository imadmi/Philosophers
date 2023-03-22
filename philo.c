/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:47:28 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/22 10:50:19 by imimouni         ###   ########.fr       */
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
		return (0);
	get_args(ac, av, data);
	init_data(data);
	init_mutex(data);
	ft_thread(data);
	check_death(data->philos);
	ft_join(data);
	ft_free(data);
	return (0);
}
