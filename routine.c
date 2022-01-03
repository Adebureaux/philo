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

	if (gettimeofday(&tv, NULL))
		return (0);
	return (((tv.tv_sec) * 1000 + (tv.tv_usec / 1000)));
}

void	usleep_custom(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

void	philo_live(t_board *board, t_philo *philo, int id)
{
	pthread_mutex_lock(philo[id].l_fork);
	pthread_mutex_lock(philo[id].print);
	printf("%lu %d has taken a fork\n", get_time() - philo[id].start_time, id);
	pthread_mutex_unlock(philo[id].print);
	pthread_mutex_lock(philo[id].r_fork);
	pthread_mutex_lock(philo[id].print);
	printf("%lu %d has taken a fork\n", get_time() - philo[id].start_time, id);
	pthread_mutex_unlock(philo[id].print);
	pthread_mutex_lock(philo[id].print);
	printf("%lu %d is eating\n", get_time() - philo[id].start_time, id);
	pthread_mutex_unlock(philo[id].print);
	usleep_custom(board->eat);
	pthread_mutex_unlock(philo[id].l_fork);
	pthread_mutex_unlock(philo[id].r_fork);
	//philo->time_last_eat = get_time();
	pthread_mutex_lock(philo[id].print);
	printf("%lu %d is sleeping\n", get_time() - philo[id].start_time, id);
	pthread_mutex_unlock(philo[id].print);
	usleep_custom(board->sleep);
	pthread_mutex_lock(philo[id].print);
	printf("%lu %d is thinking\n", get_time() - philo[id].start_time, id);
	pthread_mutex_unlock(philo[id].print);
}

void	*routine(void *arg)
{
	t_board	*board;
	t_philo	*philo;
	int		id;
	
	board = (t_board *)arg;
	philo = board->philo;
	id = board->id;
	if (!(id % 2) && id != 1)
		usleep_custom(board->eat / 2);
	while (42)
	{
		philo_live(board, philo, id);
	}
	
	return (NULL);
}
