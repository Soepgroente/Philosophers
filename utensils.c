/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utensils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:56:38 by vvan-der          #+#    #+#             */
/*   Updated: 2023/09/16 16:49:56 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forked(t_data *data, t_philo *henk)
{
	while (henk->alive == true)
	{
		if (henk->left_fork == AVAILABLE)
			take_fork(data, henk, LEFT);
		if (henk->lf == true && henk->right_fork == AVAILABLE)
			take_fork(data, henk, RIGHT);
		usleep(100);
	}
}

void	take_fork(t_data *data, t_philo *henk, bool fork)
{
	puts("HI");
	if (henk->alive == true)
	{
		pthread_mutex_lock(&henk->lock);
		printf("%d %d has taken a fork\n", data->time, henk->num);
		if (fork == LEFT)
		{
			data->forks[henk->num] = TAKEN;
			henk->lf = true;
			pthread_mutex_unlock(&henk->lock);
		}
		else
		{
			if (henk->num != data->ph_num - 1)
				data->forks[henk->num + 1] = TAKEN;
			else
				data->forks[0] = TAKEN;
			henk->rf = true;
			pthread_mutex_unlock(&henk->lock);
			eat_foods(data, henk);
		}
	}
}