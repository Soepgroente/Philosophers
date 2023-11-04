/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 13:09:45 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/04 19:19:17 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		sem_post(data->start);
		i++;
	}
}

int	fork_process(t_data *data)
{
	t_philo	*sjon;

	data->processes = ft_calloc(data->ph_num * sizeof(pid_t));
	if (data->processes == NULL)
		return (-1);
	data->processes[data->num] = 0;
	data->t_start = get_time();
	while (data->num < data->ph_num)
	{
		data->processes[data->num] = fork();
		if (data->processes[data->num] == -1)
			return (kill_children(data->processes, data->num), -1);
		if (data->processes[data->num] == 0)
		{
			sjon = init_sjon(data);
			if (sjon == NULL)
				return (-1);
			free(data->processes);
			sjon_is_born(sjon);
		}
		data->num++;
	}
	start_simulation(data);
	return (0);
}
