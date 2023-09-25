/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/17 14:48:36 by vincent       #+#    #+#                 */
/*   Updated: 2023/09/25 11:14:37 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000000 + time.tv_usec);
}

int	get_runtime(long t_start)
{
	int	time;

	time = (int)(get_time() - t_start) / 1000;
	return (time);
}

void	ft_sleep(t_philo *henk, long sleep_duration)
{
	long	timestamp;
	long	goal;

	(void)henk;
	timestamp = get_time();
	goal = timestamp + sleep_duration;
	while (timestamp < goal)
	{
		usleep(500);
		timestamp = get_time();
	}
}
