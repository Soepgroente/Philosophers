/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 12:40:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/16 12:40:48 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000000 + time.tv_usec));
}

int	get_runtime(long t_start)
{
	return ((int)(get_time() - t_start) / 1000);
}

void	ft_sleep(t_philo *sjon, long sleep_duration)
{
	long	timestamp;
	long	goal;

	timestamp = get_time();
	goal = timestamp + sleep_duration;
	while (timestamp < goal && poke_sjon(sjon, sjon->poke) == true)
	{
		usleep(500);
		timestamp = get_time();
	}
}
