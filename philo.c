/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:22 by adeburea          #+#    #+#             */
/*   Updated: 2021/10/07 12:31:21 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*parse_philo(int ac, char **av, t_philo *philo)
{
	if (ac != 5 && ac != 6)
		return ("must have 4 or 5 arguments");
	philo->number = ft_atoi(*(av + 1));
	if (philo->number < 0)
		return ("arg 1 must be 'number_of_philosophers'");
	philo->die = ft_atoi(*(av + 2));
	if (philo->die < 1)
		return ("arg 2 must be 'time_to_die'");
	philo->eat = ft_atoi(*(av + 3));
	if (philo->eat < 1)
		return ("arg 3 must be 'time_to_eat'");
	philo->sleep = ft_atoi(*(av + 4));
	if (philo->sleep < 1)
		return ("arg 4 must be 'time_to_sleep'");
	philo->times = -1;
	if (ac == 6)
		philo->times = ft_atoi(*(av + 5));
	if (ac == 6 && philo->times < 1)
		return ("arg 5 must be 'number_of_times_each_philosopher_must_eat'");
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (parse_philo(ac, av, &philo))
		return (printf("%s: error: %s\n", av[0], parse_philo(ac, av, &philo)));
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	printf("seconds : %ld\nmicro seconds : %d\n", current_time.tv_sec, current_time.tv_usec);
	return (0);
}
