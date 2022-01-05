/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/05 02:42:23 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	usleep_custom(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

void	philo_speak(t_philo *philo, char *str, int id)
{
	pthread_mutex_lock(philo[id].print);
	ft_putstr(philo[id].color);
	ft_putnbr(get_time() - philo[id].start_time);
	write(1, " ", 1);
	ft_putnbr((size_t)id);
	write(1, " ", 1);
	ft_putstr(str);
	ft_putstr("\033[0m");
	pthread_mutex_unlock(philo[id].print);
}

void	philo_live(t_board *board, t_philo *philo, int id)
{
	// Taking forks
	pthread_mutex_lock(philo[id].l_fork);
	pthread_mutex_lock(philo[id].r_fork);
	philo_speak(philo, "has taken a fork\n", id);
	philo_speak(philo, "has taken a fork\n", id);

	// Eat
	philo_speak(philo, "is eating\n", id);
	usleep_custom(board->eat);

	// Puting forks back
	pthread_mutex_unlock(philo[id].r_fork);
	pthread_mutex_unlock(philo[id].l_fork);

	// Sleep
	philo_speak(philo, "is sleeping\n", id);
	usleep_custom(board->sleep);

	// Think
	philo_speak(philo, "is thinking\n", id);
}

void	*routine(void *arg)
{
	t_board	*board;
	t_philo	*philo;
	int		id;
	
	board = (t_board *)arg;
	philo = board->philo;
	id = board->id;
	philo[id].start_time = get_time();
	while (LOOP)
		philo_live(board, philo, id);
	return (NULL);
}
