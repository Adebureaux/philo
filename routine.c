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

void	philo_speak(t_philo *philo, char *str, int id)
{
	pthread_mutex_lock(philo[id].print);
	printf(str, get_time() - philo[id].start_time, id);
	pthread_mutex_unlock(philo[id].print);
}

void	philo_live(t_board *board, t_philo *philo, int id)
{
	// Taking forks
	pthread_mutex_lock(philo[id].l_fork);
	pthread_mutex_lock(philo[id].r_fork);
	philo_speak(philo, "%lu %d has taken a fork\n", id);
	philo_speak(philo, "%lu %d has taken a fork\n", id);
	//take_forks(philo, id);

	// Eat
	philo_speak(philo, "%lu %d is eating\n", id);
	usleep(board->eat);

	// Puting forks back
	pthread_mutex_unlock(philo[id].r_fork);
	pthread_mutex_unlock(philo[id].l_fork);
	//philo[id].cur_time = get_time();

	// Sleep
	philo_speak(philo, "%lu %d is sleeping\n", id);
	usleep(board->sleep);

	// Think
	philo_speak(philo, "%lu %d is thinking\n", id);
}

void	*routine(void *arg)
{
	t_board	*board;
	t_philo	*philo;
	int		id;
	
	board = (t_board *)arg;
	philo = board->philo;
	id = board->id;
	while (LOOP)
		philo_live(board, philo, id);
	
	return (NULL);
}
