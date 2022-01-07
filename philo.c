/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:22 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/07 03:04:23 by adeburea         ###   ########.fr       */
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
	board->die = ft_atoi(*(av + 2));
	if (board->die < 1)
		return ("arg 2 must be 'time_to_die'");
	board->eat = ft_atoi(*(av + 3));
	if (board->eat < 1)
		return ("arg 3 must be 'time_to_eat'");
	board->sleep = ft_atoi(*(av + 4));
	if (board->sleep < 1)
		return ("arg 4 must be 'time_to_sleep'");
	board->limit = -1;
	if (ac == 6)
		board->limit = ft_atoi(*(av + 5));
	if (ac == 6 && board->limit < 1)
		return ("arg 5 must be 'number_of_times_each_philosopher_must_eat'");
	return (NULL);
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
		return (printf("philo: error: can't start_philo\n"));
	free_philo(board, philo);
	return (1);
}
