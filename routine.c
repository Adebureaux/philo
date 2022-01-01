/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2021/12/21 15:04:11 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec) * 1000 + (tv.tv_usec / 1000)));
}

size_t	try_eat(int id, int eat, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&(philo[id].l_fork));
	pthread_mutex_lock(&(philo[id].r_fork));
	time = get_time();
	printf("%zu philo%d has taken a fork\n", get_time() - time, id);
	usleep(eat);
	pthread_mutex_unlock(&(philo[id].l_fork));
	pthread_mutex_unlock(&(philo[id].r_fork));
	printf("%zu philo%d eating\n", get_time() - time, id);
	return (1);
}

void	*routine(void *arg)
{
	t_board	*board;
	t_philo	*philo;
	int		id;
	
	board = (t_board *)arg;
	philo = board->philo;
	id = board->id;
	while (42)
	{
		try_eat(id, board->eat, philo);
	}
	
	return (NULL);
}
