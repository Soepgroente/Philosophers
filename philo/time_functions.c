/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 20:55:39 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/15 19:20:05 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000000 + time.tv_usec);
}

int	get_runtime(long start_time)
{
	return ((int)(get_time() - start_time) / 1000);
}

void	power_naps(t_philo *henk, long sleep_duration)
{
	long	timestamp;
	long	goal;
	long	x;

	x = 100 + henk->data->ph_num * 5;
	timestamp = get_time();
	goal = timestamp + sleep_duration;
	while (timestamp < goal && poke_henk(henk) == true)
	{
		usleep(x);
		timestamp = get_time();
	}
}
