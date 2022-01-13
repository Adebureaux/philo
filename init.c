/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:09:07 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/13 11:36:08 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	assign_forks(t_board *board, t_philo *philo, int id)
{
	if (!id)
	{
		philo[id].l_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		philo[id].r_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo[id].l_fork || pthread_mutex_init(philo[id].l_fork, NULL)
			|| !philo[id].r_fork || pthread_mutex_init(philo[id].r_fork, NULL))
			return (1);
	}
	else if (id < board->number)
	{
		philo[id].l_fork = philo[id - 1].r_fork;
		philo[id].r_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo[id].r_fork || pthread_mutex_init(philo[id].r_fork, NULL))
			return (1);
	}
	else
	{
		philo[id].l_fork = philo[id - 1].r_fork;
		philo[id].r_fork = philo[0].l_fork;
	}
	return (0);
}

void	init_color(t_board *board, t_philo *philo)
{
	int		i;

	i = -1;
	ft_strcpy(board->color[0], DEF);
	ft_strcpy(board->color[1], YELLOW);
	ft_strcpy(board->color[2], GREEN);
	ft_strcpy(board->color[3], RED);
	ft_strcpy(board->color[4], BLUE);
	ft_strcpy(board->color[5], PURPLE);
	ft_strcpy(board->color[6], CYAN);
	while (++i < board->number)
		ft_strcpy(philo[i].color, board->color[i % 7]);
}

int	init_philo(t_board *board, t_philo *philo)
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*lock;
	int				i;

	i = -1;
	print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!print || pthread_mutex_init(print, NULL))
		return (1);
	lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!lock || pthread_mutex_init(lock, NULL))
		return (1);
	init_color(board, philo);
	while (++i < board->number)
	{
		philo[i].count_meal = 0;
		philo[i].print = print;
		if (assign_forks(board, philo, i))
			return (1);
	}
	board->lock = lock;
	return (0);
}

int	start_philo(t_board *board, t_philo *philo)
{
	int		i;

	i = -1;
	board->id = 0;
	board->rip = -1;
	board->full_number = 0;
	board->stop = 0;
	board->philo = philo;
	board->start_time = get_time();
	while (++i < board->number)
	{
		if (pthread_create(&(philo[i].philo), NULL, &routine, board))
			return (1);
	}
	i = -1;
	while (++i < board->number)
		pthread_join(philo[i].philo, NULL);
	return (0);
}

void	free_philo(t_board *board, t_philo *philo)
{
	int		i;

	i = -1;
	free(philo[0].print);
	free(board->lock);
	while (++i < board->number)
	{
		philo[0].print = NULL;
		if (!i)
		{
			free(philo[i].l_fork);
			free(philo[i].r_fork);
		}
		else if (i < board->number)
			free(philo[i].r_fork);
	}
	free(philo);
	free(board);
	philo = NULL;
	board = NULL;
}
