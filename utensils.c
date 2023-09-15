/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utensils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 12:56:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/14 13:02:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_data *data, t_philo *henk, bool fork)
{
	pthread_mutex_lock(&henk->lock);
	printf("%d %d has taken a fork\n", data->time, henk->num);
	if (fork == LEFT)
	{
		henk->left_fork = TAKEN;
		henk->lf = true;
		pthread_mutex_unlock(&henk->lock);
	}
	else
	{
		henk->right_fork = TAKEN;
		henk->rf = true;
		pthread_mutex_unlock(&henk->lock);
		eat_foods(data, henk);
	}
}