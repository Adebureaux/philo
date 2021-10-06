/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:22 by adeburea          #+#    #+#             */
/*   Updated: 2021/10/06 16:28:17 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]


int		parse_philo(int ac, char **av, t_philo *philo)
{
	if (ac != 5 || ac != 6)
		return (1);
	philo->number = ft_atoi(*(av + 1));
	philo->die = ft_atoi(*(av + 2));
	philo->eat = ft_atoi(*(av + 3));
	philo->sleep = ft_atoi(*(av + 4));
	if (ac == 6)
		philo->times = ft_atoi(*(av + 5));
	printf("%d\n%d\n%d\n%d\n", philo->number, philo->die, philo->eat, philo->sleep);
	if (philo->number < 1 || philo->die < 1 || philo->eat < 1
		|| philo->sleep < 1 || (ac == 5 && philo->times < 1))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo philo;

	if (parse_philo(ac, av, &philo))
	{
		printf("%s: wrong arguments\n", av[0]);
		return (1);
	}
	return (0);
}
