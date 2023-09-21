/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/17 14:48:36 by vincent       #+#    #+#                 */
/*   Updated: 2023/09/19 11:43:04 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_forks(t_data *data, bool *forks)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		if (forks[i] == false)
			printf("[%d] available\n", i);
		else
			printf("[%d] taken\n", i);
		i++;
	}
}

bool	on_your_marks(bool main_thread, t_data *data, pthread_mutex_t *lock)
{
	bool	start;

	pthread_mutex_lock(lock);
	if (main_thread == true)
	{
		data->ready = true;
		start = true;
	}
	else if (data->ready == true)
		start = true;
	else
		start = false;
	pthread_mutex_unlock(lock);
	return (start);
}