/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/12 12:50:15 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_routine(t_data *data)
{
	t_philo	p;

	pthread_mutex_lock(&data->mutex);
	init_philo(data, &p, data->x);
	data->x++;
	pthread_mutex_unlock(&data->mutex);
}