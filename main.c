/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 03:18:58 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/07 03:51:09 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*parse(int ac, char **av, t_board *board)
{
	if (ac != 5 && ac != 6)
		return ("philo: error: must have 4 or 5 arguments");
	board->number = ft_atoi(*(av + 1));
	if (board->number < 1)
		return ("philo: error: arg 1 must be 'number_of_philosophers'");
	board->die = ft_atoi(*(av + 2));
	if (board->die < 1)
		return ("philo: error: arg 2 must be 'time_to_die'");
	board->eat = ft_atoi(*(av + 3));
	if (board->eat < 1)
		return ("philo: error: arg 3 must be 'time_to_eat'");
	board->sleep = ft_atoi(*(av + 4));
	if (board->sleep < 1)
		return ("philo: error: arg 4 must be 'time_to_sleep'");
	board->limit = -1;
	if (ac == 6)
		board->limit = ft_atoi(*(av + 5));
	if (ac == 6 && board->limit < 1)
		return ("philo: error: arg 5 must be 'number_of_times_philosopher_must_eat'");
	return (NULL);
}

int	quit(t_board *board, t_philo *philo, char *err)
{
	if (board)
		free(board);
	if (philo)
		free(philo);
	printf("%s\n", err);
	return (-1);
}

int	main(int ac, char **av)
{
	t_board	*board;
	t_philo	*philo;

	board = malloc(sizeof(t_board));
	if (!board)
		return (quit(NULL, NULL, "philo: error: malloc error"));
	if (parse(ac, av, board))
		return (quit(board, NULL, parse(ac, av, board)));
	philo = malloc(sizeof(t_philo) * board->number);
	if (!philo)
		return (quit(board, NULL, "philo: error: can't malloc"));
	if (init_philo(board, philo))
		return (quit(board, philo, "philo: error: can't init_philo"));
	if (start_philo(board, philo))
		return (quit(board, philo, "philo: error: can't start_philo"));
	//free_philo(board, philo);
	return (1);
}
