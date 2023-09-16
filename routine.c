/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:18:22 by vvan-der          #+#    #+#             */
/*   Updated: 2023/09/16 17:13:16 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000000 + time.tv_usec);
}

void	ft_sleep(long sleep_duration)
{
	long	timestamp;
	long	goal_time;

	timestamp = get_time();
	goal_time = timestamp + sleep_duration;
	while (timestamp < goal_time)
	{
		timestamp = get_time();
		usleep(100);
	}
}

void	after_dinner_dip(t_data *data, t_philo *henk)
{
	if (henk->alive == true)
	{
		printf("%d %d is sleeping\n", data->time, henk->num);
		ft_sleep(data->t_sleep * 1000);
	}
	if (henk->alive == true)
		printf("%d %d is thinking\n", data->time, henk->num);
}

void	eat_foods(t_data *data, t_philo *henk)
{
	if (henk->alive == true)
	{
		henk->last_eaten = data->time;
		printf("%d %d is eating\n", data->time, henk->num);
		ft_sleep(data->t_eat * 1000);
		pthread_mutex_lock(&henk->lock);
		henk->left_fork = AVAILABLE;
		henk->right_fork = AVAILABLE;
		henk->num_eaten++;
		if (henk->num_eaten >= data->num_eat)
			henk->saturated = true;
		henk->lf = false;
		henk->rf = false;
		pthread_mutex_unlock(&henk->lock);
		after_dinner_dip(data, henk);
	}
}

void	*start_routine(void *d)
{
	t_data	*data;
	t_philo	*henk;

	data = (t_data *) d;
	while (data->ready == false)
		usleep(20);
	if (henk->num % 2 == 1)
		usleep(200);
	data->start_time = get_time();
	printf("Philosopher %d reporting!\n", henk->num);
	get_forked(data, henk);
	return (NULL);
}
