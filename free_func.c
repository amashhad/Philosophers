/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:01:41 by amashhad          #+#    #+#             */
/*   Updated: 2025/07/05 21:02:10 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_loop_philo(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->philos[i].meal_lock);
			pthread_mutex_destroy(&data->philos[i].meal_nb_lock);
			i++;
		}
		free(data->philos);
	}
}

int	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->num_philos)
		{
			if (data->forks_init[i] == 1)
				pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		if (data->forks_init)
			free(data->forks_init);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	free_loop_philo(data);
	return (1);
}
