/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_inits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:05:37 by amashhad          #+#    #+#             */
/*   Updated: 2025/07/05 21:44:20 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	reverse_destroy(t_data *data, int limit)
{
	while (limit > 0)
	{
		pthread_mutex_destroy(&data->forks[limit]);
		limit--;
	}
}

void	data_set(t_data *data, int i)
{
	if (i % 2 == 0)
	{
		data->philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].right_fork = &data->forks[i];
	}
	else
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
	}
	data->philos[i].id = i + 1;
	data->philos[i].last_meal = time_ms();
	data->philos[i].meals_eaten = 0;
	data->philos[i].data = data;
}

void	destroy_meals(t_data *data, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		pthread_mutex_destroy(&data->philos[i].meal_nb_lock);
		i++;
	}
}

int	init_meals(t_data *data, int i)
{
	if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
	{
		fputendl(2, "Error: init failed meal_lock");
		return (1);
	}
	if (pthread_mutex_init(&data->philos[i].meal_nb_lock, NULL) != 0)
	{
		fputendl(2, "Error: init failed meal_nb_lock");
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		return (1);
	}
	return (0);
}

int	meals_n_forks(t_data *data)
{
	int	i;
	int	chk;

	i = 0;
	chk = 0;
	while (i < data->num_philos)
	{
		chk = init_meals(data, i);
		if (chk == 1)
		{
			destroy_meals(data, i);
			return (1);
		}
		data_set(data, i);
		i++;
	}
	return (0);
}
