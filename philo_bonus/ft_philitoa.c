/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_philitoa.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/24 19:59:58 by vincent       #+#    #+#                 */
/*   Updated: 2023/09/25 11:04:21 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s3 = malloc((i + j + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++j])
	{
		s3[i] = s2[j];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

char	*ft_philitoa(int n)
{
	char	*res;

	if (n == 0)
		return ("/sem_0");
	res = malloc(4 * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[3] = '\0';
	if (n > 99)
	{
		res[2] = (n % 10) + '0';
		n /= 10;
	}
	else
		res[2] = '\0';
	if (n > 9)
	{
		res[1] = (n % 10) + '0';
		n /= 10;
	}
	else
		res[1] = '\0';
	res[0] = n + '0';
	return (ft_strjoin("/sem_", res));
}
