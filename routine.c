/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/15 16:37:29 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fall_asleep(t_data *data, t_philo *henk)
{
	printf("%d %d is sleeping\n", data->time, henk->num);
	usleep(data->t_sleep * 1000);
}

int	eat_foods(t_data *data, t_philo *henk)
{
	printf("%d %d is eating\n", data->time, henk->num);
	pthread_mutex_lock(&henk->lock);
	henk->left_fork = AVAILABLE;
	henk->right_fork = AVAILABLE;
	henk->lf = false;
	henk->rf = false;
	pthread_mutex_unlock(&henk->lock);
	fall_asleep(data, henk);
}

int	get_forked(t_data *data, t_philo *henk)
{
	while (true)
	{
		if (henk->left_fork == AVAILABLE)
			take_fork(data, henk, LEFT);
		if (henk->lf == true && henk->right_fork == AVAILABLE)
			take_fork(data, henk, RIGHT);
		usleep(100);
	}
}

int	start_routine(t_data *data)
{
	t_philo	henk;

	pthread_mutex_init(&henk.lock, NULL);
	pthread_mutex_lock(&henk.lock);
	init_philo(data, &henk, data->x);
	data->x++;
	pthread_mutex_unlock(&henk.lock);
	while (data->ready == false)
		usleep(20);
	if (henk.num % 2 == 1)
		usleep(200);
	get_forked(data, &henk);
}
