/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stalking.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/30 17:25:48 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/16 12:06:52 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_everyone(t_data *data)
{

}

static bool	check_saturation(t_data *d)
{

}

static bool	stalk_table(t_data *d)
{

}

void	stalk_philos(t_data *d)
{
	if (d->num_eat < INT_MAX)
	{
		while (INFINITY)
		{
			if (stalk_table(d) == DEATH)
				return ;
			if (check_saturation(d) == true)
				return ;
			usleep(500);
		}
	}
	else
	{
		while (INFINITY)
		{
			if (stalk_table(d) == DEATH)
				return ;
			usleep(500);
		}
	}
}
