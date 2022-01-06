/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/06 02:40:36 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_speak(t_board *board, t_philo *philo, char *str, int id)
{
	pthread_mutex_lock(philo[id].print);
	if (!board->stop)
	{
		ft_putstr(philo[id].color);
		ft_putnbr(get_time() - board->start_time);
		write(1, " ", 1);
		ft_putnbr((size_t)id + 1);
		write(1, " ", 1);
		ft_putstr(str);
		ft_putstr("\033[0m");
	}
	if (!board->stop && board->rip == id)
		board->stop = 1;
	pthread_mutex_unlock(philo[id].print);
}

int		philo_live(t_board *board, t_philo *philo, int id)
{
	// Taking forks
	if (board->rip == -1 && philo[id].last_meal && get_time() - philo[id].last_meal > (size_t)board->die)
	{
		board->rip = id;
		philo_speak(board, philo, "died\n", id);
		return (1);
	}
	pthread_mutex_lock(philo[id].l_fork);
	pthread_mutex_lock(philo[id].r_fork);
	philo_speak(board, philo, "has taken a fork\n", id);
	philo_speak(board, philo, "has taken a fork\n", id);

	// Eat
	philo_speak(board, philo, "is eating\n", id);
	usleep_custom(board->eat);
	philo[id].count_meal++;
	if (philo[id].count_meal >= board->limit)
		board->full_number++;
	philo[id].last_meal = get_time();
	// Puting forks back
	pthread_mutex_unlock(philo[id].l_fork);
	pthread_mutex_unlock(philo[id].r_fork);
	if (board->limit != -1 && board->full_number >= board->number)
		return (1);
	if (board->rip != -1)
		return (1);

	// Sleep
	philo_speak(board, philo, "is sleeping\n", id);
	usleep_custom(board->sleep);

	// Think
	philo_speak(board, philo, "is thinking\n", id);
	if (board->limit != -1 && philo[id].count_meal >= board->limit)
		return (1);
	if (board->rip != -1)
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_board	*board;
	t_philo	*philo;
	int		id;
	
	board = (t_board *)arg;
	id = board->id;
	philo = board->philo;
	while (42)
	{
		if (philo_live(board, philo, id))
			break;

	}
	return (NULL);
}
