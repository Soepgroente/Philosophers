/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/12 20:48:28 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_routine(t_data *data)
{
	t_philo	henk;

	pthread_mutex_init(&henk.mutex, NULL);
	pthread_mutex_lock(&henk.mutex);
	init_philo(data, &henk, data->x);
	data->x++;
	pthread_mutex_unlock(&henk.mutex);
}
