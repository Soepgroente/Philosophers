/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 12:40:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/02 15:42:12 by vincent       ########   odam.nl         */
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

void	special_naps(t_philo *sjon)
{
	long	timestamp;
	long	goal;
	long	lifetime;

	timestamp = get_time();
	lifetime = sjon->t_die - (get_time() - sjon->last_eaten);
	if (lifetime > sjon->t_eat * 3)
		return ;
	goal = timestamp + lifetime - sjon->t_eat;
	while (timestamp < goal)
	{
		usleep(200);
		timestamp = get_time();
	}
}

void	power_naps(t_philo *sjon, long sleep_duration)
{
	long	timestamp;
	long	goal;

	timestamp = get_time();
	goal = timestamp + sleep_duration;
	while (timestamp < goal && poke_sjon(sjon) == true)
	{
		usleep(500);
		timestamp = get_time();
	}
}
