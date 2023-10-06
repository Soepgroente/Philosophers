/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/03 18:15:04 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_semaphores(t_data *data, t_philo *sjon)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = ft_philitoa(sjon->num);
	str2 = ft_philitoa(sjon->num + data->ph_num);
	str3 = ft_philitoa(sjon->num + (data->ph_num * 2));
	sem_unlink(str1);
	sem_unlink(str2);
	sem_unlink(str3);
	free(str1);
	free(str2);
	free(str3);
}

static void	free_sjonnies(t_philo *sjon, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		sem_close(sjon[i].poke);
		sem_close(sjon[i].eat);
		sem_close(sjon[i].eat2);
		unlink_semaphores(sjon->data, &sjon[i]);
		i++;
	}
	free(sjon);
	sjon = NULL;
}

void	clean_up(t_data *data)
{
	if (data->philos != NULL)
	{
		free_sjonnies(data->philos, data->ph_num);
		data->philos = NULL;
	}
	if (data->forks != NULL)
	{
		sem_close(data->forks);
		data->forks = NULL;
	}
	if (data->print != NULL)
	{
		sem_close(data->print);
		data->print = NULL;
	}
	if (data->threads != NULL)
		free(data->threads);
}
