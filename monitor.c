/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:14:58 by amashhad          #+#    #+#             */
/*   Updated: 2025/07/05 22:01:34 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_flag(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_lock);
	result = data->death_flag;
	pthread_mutex_unlock(&data->death_lock);
	return (result);
}

void	set_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->death_flag = 1;
	pthread_mutex_unlock(&data->death_lock);
}

void	is_dead(t_data *data, int i, int *full_philos)
{
	pthread_mutex_lock(&data->philos[i].meal_lock);
	if (time_ms() - data->philos[i].last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_lock);
		printf("%lldms philo.%d died\n",
			time_ms() - data->start_time, data->philos[i].id);
		set_death_flag(data);
		pthread_mutex_unlock(&data->print_lock);
	}
	pthread_mutex_unlock(&data->philos[i].meal_lock);
	pthread_mutex_lock(&data->philos[i].meal_nb_lock);
	if (data->meal_cnt != -1 && data->philos[i].meals_eaten >= data->meal_cnt)
		(*full_philos)++;
	pthread_mutex_unlock(&data->philos[i].meal_nb_lock);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		full_philos;

	data = (t_data *)arg;
	while (!death_flag(data))
	{
		i = 0;
		full_philos = 0;
		while (i < data->num_philos && !data->death_flag)
		{
			is_dead(data, i, &full_philos);
			i++;
		}
		if (data->meal_cnt != -1 && full_philos == data->num_philos)
			set_death_flag(data);
		usleep(100);
	}
	return (NULL);
}
