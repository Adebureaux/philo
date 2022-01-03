/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:22 by adeburea          #+#    #+#             */
/*   Updated: 2021/12/21 15:06:21 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*parse(int ac, char **av, t_board *board)
{
	if (ac != 5 && ac != 6)
		return ("must have 4 or 5 arguments");
	board->number = ft_atoi(*(av + 1));
	if (board->number < 1)
		return ("arg 1 must be 'number_of_philosophers'");
	board->die = ft_atoi(*(av + 2)) * 1000;
	if (board->die < 1)
		return ("arg 2 must be 'time_to_die'");
	board->eat = ft_atoi(*(av + 3)) * 1000;
	if (board->eat < 1)
		return ("arg 3 must be 'time_to_eat'");
	board->sleep = ft_atoi(*(av + 4)) * 1000;
	if (board->sleep < 1)
		return ("arg 4 must be 'time_to_sleep'");
	board->limit = -1;
	if (ac == 6)
		board->limit = ft_atoi(*(av + 5));
	if (ac == 6 && board->limit < 1)
		return ("arg 5 must be 'number_of_times_each_philosopher_must_eat'");
	return (NULL);
}

int	assign_forks(t_board *board, t_philo *philo, int id)
{
	if (!id)
	{
		philo[id].l_fork = malloc(sizeof(pthread_mutex_t *));
		philo[id].r_fork = malloc(sizeof(pthread_mutex_t *));
		if (!philo[id].l_fork || pthread_mutex_init(philo[id].l_fork, NULL)
			|| !philo[id].r_fork || pthread_mutex_init(philo[id].r_fork, NULL))
			return (1);
	}
	else if (id < board->number)
	{
		philo[id].l_fork = philo[id - 1].r_fork;
		philo[id].r_fork = malloc(sizeof(pthread_mutex_t *));
		if (!philo[id].r_fork || pthread_mutex_init(philo[id].r_fork, NULL))
			return (1);
	}
	else
	{
		philo[id].l_fork = philo[id - 1].r_fork;
		philo[id].r_fork = philo[0].l_fork;
	}
	pthread_mutex_unlock(philo[id].l_fork);
	pthread_mutex_unlock(philo[id].r_fork);
	return (0);
}

int	init_philo(t_board *board, t_philo *philo)
{
	pthread_mutex_t	*print;
	int				i;

	i = -1;
	print = malloc(sizeof(pthread_mutex_t *));
	if (!print || pthread_mutex_init(print, NULL))
		return (1);
	while (++i < board->number)
	{
		philo[i].eat_count = 0;
		philo[i].print = print;
		if (assign_forks(board, philo, i))
			return (1);
	}
	pthread_mutex_unlock(print);
	board->philo = philo;
	return (0);
}

int	start_philo(t_board *board, t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < board->number)
	{
		board->id = i;
		philo[i].start_time = get_time();
		if (pthread_create(&(philo[i].philo), NULL, &routine, board))
			return (1);
	}
	i = -1;
	while (++i < board->number)
		pthread_join(philo[i].philo, NULL);
	return (0);
}


int	main(int ac, char **av)
{
	t_board	*board;
	t_philo	*philo;

	board = malloc(sizeof(t_board));
	if (!board)
		return (printf("malloc error\n"));
	if (parse(ac, av, board))
		return (printf("%s: error: %s\n", av[0], parse(ac, av, board)));
	philo = malloc(sizeof(t_philo) * board->number);
	if (!philo)
		return (printf("philo: error: can't malloc\n"));
	if (init_philo(board, philo))
		return (printf("philo: error: can't init_philo\n"));
	if (start_philo(board, philo))
		return (printf("philo: error: can't create start_philo\n"));
	return (1);
}
