/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/17 14:48:36 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/09 15:20:30 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000000 + time.tv_usec);
}

int	get_runtime(long t_start)
{
	return ((int)(get_time() - t_start) / 1000);
}

void	ft_sleep(t_philo *henk, long sleep_duration)
{
	long	timestamp;
	long	goal;
	int		x;

	x = 50 + henk->data->ph_num * 5;
	timestamp = get_time();
	goal = timestamp + sleep_duration;
	while (timestamp < goal && poke_henk(henk, &henk->life_lock, NONE) == true)
	{
		usleep(x);
		timestamp = get_time();
	}
}

void	print_message(t_philo *henk, pthread_mutex_t *print_lock, char *msg)
{
	pthread_mutex_lock(print_lock);
	if (poke_henk(henk, &henk->life_lock, NONE) == false)
	{
		pthread_mutex_unlock(print_lock);
		return ;
	}
	printf("%d %d %s", get_runtime(henk->t_start), henk->num + 1, msg);
	pthread_mutex_unlock(print_lock);
}
