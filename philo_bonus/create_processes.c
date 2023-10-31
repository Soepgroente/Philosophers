/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 13:09:45 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/31 13:39:34 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	fork_process(t_data *data)
{
	pid_t	id;
	t_philo	*sjon;

	id = 0;
	data->processes = ft_calloc(data->ph_num * sizeof(pid_t));
	if (data->processes == NULL)
		return (-1);
	while (data->num < data->ph_num)
	{
		id = fork();
		if (id == -1)
			return (kill_children(data->processes, data->num), -1);
		if (id == 0)
		{
			sjon = init_sjon(data);
			if (sjon == NULL)
				return (-1);
			free(data->processes);
			return (sjon_is_born(sjon));
		}
		data->processes[data->num] = id;
		data->num++;
	}
	usleep(15000);
	sem_post(data->start);
	return (0);
}