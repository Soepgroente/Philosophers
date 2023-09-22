/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:48:36 by vincent           #+#    #+#             */
/*   Updated: 2023/09/22 14:57:22 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000000 + time.tv_usec);
}

int	get_runtime(long start_time)
{
	int	time;
	
	time = (int) (get_time() - start_time) / 1000;
	return (time);
}

void	ft_sleep(t_philo *henk, long sleep_duration)
{
	long	timestamp;
	long	goal_time;

	timestamp = get_time();
	goal_time = timestamp + sleep_duration;
	while (timestamp < goal_time && check_if_alive(henk, &henk->lock, NONE) == true)
	{
		usleep(200);
		timestamp = get_time();
	}
}

void	print_forks(t_data *data, bool *forks)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		if (forks[i] == false)
			printf("[%d] available\n", i);
		else
			printf("[%d] taken\n", i);
		i++;
	}
}
