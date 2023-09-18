/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/18 12:21:57 by vvan-der      ########   odam.nl         */
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
		usleep(200);
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
		// print_forks(data, data->forks);
		ft_sleep(data->t_eat * 1000);
		// pthread_mutex_lock(&henk->lock);
		*henk->left_fork = AVAILABLE;
		*henk->right_fork = AVAILABLE;
		// print_forks(data, data->forks);
		henk->num_eaten++;
		if (henk->num_eaten >= data->num_eat)
			henk->saturated = true;
		henk->lf = false;
		henk->rf = false;
		// pthread_mutex_unlock(&henk->lock);
		after_dinner_dip(data, henk);
	}
}

void	*start_routine(void *input)
{
	t_data	*data;
	t_args	*args;
	t_philo	*henk;

	args = (t_args *) input;
	data = args->data_struct;
	henk = &data->philos[args->num];
	while (data->ready == false)
		usleep(20);
	if (henk->num % 2 == 1)
		usleep(2000);
	printf("Philosopher %d reporting!\n", henk->num);
	get_forked(data, henk);
	return (NULL);
}
