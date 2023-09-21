/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utensils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 12:56:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/19 10:54:36 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_left_fork(t_data *data, t_philo *henk)
{
	if (henk->alive == true)
	{
		*henk->left_fork = TAKEN;
		// *henk->right_fork = TAKEN;
		henk->lf = true;
		// henk->rf = true;
		printf("%d %d has taken a (left) fork\n", data->time, henk->num);
		// printf("%d %d has taken a (right) fork\n", data->time, henk->num);
		// printf("Fork (left)  by philo %d: %d, address: %p\n", henk->num, *henk->left_fork, henk->left_fork);
		// printf("Fork (right) by philo %d: %d, address: %p\n", henk->num, *henk->right_fork, henk->right_fork);
		eat_foods(data, henk);
	}
}

void	take_right_fork(t_data *data, t_philo *henk)
{
	if (henk->alive == true)
	{
		*henk->right_fork = TAKEN;
		printf("%d %d has taken a (right) fork\n", data->time, henk->num);
		// printf("Fork (right) by philo %d: %d, address: %p\n", henk->num, *henk->right_fork, henk->right_fork);
		henk->rf = true;
		eat_foods(data, henk);
	}
}

void	get_forked(t_data *data, t_philo *henk)
{
	while (henk->alive == true)
	{
		if (henk->lf == false && *henk->left_fork == AVAILABLE)
			take_left_fork(data, henk);
		if (henk->lf == true && *henk->right_fork == AVAILABLE)
			take_right_fork(data, henk);
		usleep(100);
	}
}
