/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 20:55:39 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/12 21:10:39 by vvan-der      ########   odam.nl         */
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

	x = 100 + henk->data->ph_num * 25;
	timestamp = get_time();
	goal = timestamp + sleep_duration;
	while (timestamp < goal && poke_henk(henk, &henk->life_lock) == true)
	{
		usleep(x);
		timestamp = get_time();
	}
}

void	print_message(t_philo *henk, pthread_mutex_t *print_lock, char *msg)
{
	pthread_mutex_lock(print_lock);
	if (poke_henk(henk, &henk->life_lock) == false)
	{
		pthread_mutex_unlock(print_lock);
		return ;
	}
	printf("%d %d %s", get_runtime(henk->t_start), henk->num + 1, msg);
	pthread_mutex_unlock(print_lock);
}

void	kill_henk(t_philo *henk, pthread_mutex_t *life_lock)
{
	pthread_mutex_lock(life_lock);
	henk->alive = false;
	pthread_mutex_unlock(life_lock);
}