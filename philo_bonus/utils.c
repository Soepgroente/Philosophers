/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/22 18:17:26 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/22 18:37:06 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_children(pid_t *pids, int amount)
{
	int	i;

	i = 0;
	while (i < amount && pids[i] != 0)
	{
		if (kill(pids[i], SIGKILL) == -1);
			printf("Process with id: %d failed to close\n", pids[i]);
		i++;
	}
}

void	*ft_calloc(size_t size)
{
	char	*tmp;

	tmp = malloc(size);
	if (tmp == NULL)
		return (NULL);
	tmp = memset(tmp, '\0', size);
	return (tmp);
}