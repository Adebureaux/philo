/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:25:22 by adeburea          #+#    #+#             */
/*   Updated: 2022/03/09 02:21:31 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_speak(t_board *board, t_philo *philo, char *str, int id)
{
	pthread_mutex_lock(philo[id].print);
	pthread_mutex_lock(board->lock);
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
	if (board->rip == id)
		board->stop = 1;
	pthread_mutex_unlock(board->lock);
	pthread_mutex_unlock(philo[id].print);
}

int	usleep_custom(t_board *board, size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(board->lock);
		if (board->stop)
			return (pthread_mutex_unlock(board->lock) + 1);
		pthread_mutex_unlock(board->lock);
		usleep(DELAY);
	}
	return (0);
}

int	philo_eat(t_board *board, t_philo *philo, int id)
{
	pthread_mutex_lock(philo[id].l_fork);
	pthread_mutex_lock(philo[id].r_fork);
	philo_speak(board, philo, "has taken a fork\n", id);
	if (board->number != 1)
		philo_speak(board, philo, "has taken a fork\n", id);
	else
		usleep_custom(board, board->die + 1);
	philo_speak(board, philo, "is eating\n", id);
	pthread_mutex_lock(board->lock);
	philo[id].last_meal = get_time();
	philo[id].count_meal++;
	if (philo[id].count_meal >= board->limit)
		board->full_number++;
	pthread_mutex_unlock(board->lock);
	if (usleep_custom(board, board->eat))
	{
		pthread_mutex_unlock(philo[id].l_fork);
		pthread_mutex_unlock(philo[id].r_fork);
		return (1);
	}
	pthread_mutex_unlock(philo[id].l_fork);
	pthread_mutex_unlock(philo[id].r_fork);
	return (0);
}

int	check_death(t_board *board, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < board->number)
	{
		pthread_mutex_lock(board->lock);
		if (board->stop)
			return (pthread_mutex_unlock(board->lock) + 1);
		if (get_time() - philo[i].last_meal >= (size_t)board->die)
		{
			board->rip = i;
			pthread_mutex_unlock(philo[i].print);
			pthread_mutex_unlock(board->lock);
			philo_speak(board, philo, "died\n", i);
			return (1);
		}
		if (board->limit != -1 && board->full_number == board->number)
		{
			board->stop = 1;
			return (pthread_mutex_unlock(board->lock) + 1);
		}
		pthread_mutex_unlock(board->lock);
	}
	return (0);
}

int	philo_live(t_board *board, t_philo *philo, int id)
{
	if (philo_eat(board, philo, id))
		return (1);
	philo_speak(board, philo, "is sleeping\n", id);
	if (usleep_custom(board, board->sleep))
		return (1);
	philo_speak(board, philo, "is thinking\n", id);
	if (board->limit != -1 && philo[id].count_meal >= board->limit)
		return (1);
	return (0);
}
