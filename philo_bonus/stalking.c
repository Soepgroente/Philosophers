/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stalking.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/30 17:25:48 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/30 11:50:36 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* static void	kill_everyone(t_data *data)
{

}

static bool	check_saturation(t_data *d)
{

}

static bool	stalk_table(t_data *d)
{

} */

int	wait_for_death(t_data *data)
{
	pthread_t	thread;

	if (data->max_eat != INT_MAX)
	{
		if (pthread_create(&thread, NULL, ) != 0)
			return (-1);
}
