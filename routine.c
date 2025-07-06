/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:16:35 by amashhad          #+#    #+#             */
/*   Updated: 2025/07/06 09:52:27 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	safe_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (!death_flag(philo->data))
		printf("%lldms philo.%d %s\n",
			time_ms() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	nill_case(t_philo *philo)
{
	long	start_time;

	start_time = time_ms();
	pthread_mutex_lock(philo->left_fork);
	safe_print(philo, "has taken a left fork");
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	safe_print(philo, "has died");
	pthread_mutex_lock(&philo->data->death_lock);
	philo->data->death_flag = 1;
	pthread_mutex_unlock(&philo->data->death_lock);
	return (1);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	safe_print(philo, "has taken a left fork");
	pthread_mutex_lock(philo->right_fork);
	safe_print(philo, "has taken a right fork");
	safe_print(philo, "is eating");
	if (!death_flag(philo->data))
		ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_lock(&philo->meal_nb_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_nb_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->data->num_philos == 1)
	{
		nill_case(philo);
		return (NULL);
	}
	while (!death_flag(philo->data))
	{
		eat(philo);
		if (philo->data->meal_cnt != -1
			&& philo->meals_eaten >= philo->data->meal_cnt)
			break ;
		safe_print(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo->data);
		safe_print(philo, "is thinking");
	}
	return (NULL);
}
