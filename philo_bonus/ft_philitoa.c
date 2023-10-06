/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_philitoa.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/24 19:59:58 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/03 18:14:43 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	get_length(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	string_lcopy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_philitoa(int n)
{
	char	*res;
	int		i;
	int		len;

	len = get_length(n);
	res = malloc((len + 6) * sizeof(char));
	if (res == NULL)
		return (NULL);
	string_lcopy(res, "/sem_", 5);
	i = len + 5;
	if (n == 0)
		res[i - 1] = '0';
	while (n > 0)
	{
		i--;
		res[i] = n % 10 + '0';
		n /= 10;
	}
	res[i + len] = '\0';
	return (res);
}
