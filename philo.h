/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:23 by adeburea          #+#    #+#             */
/*   Updated: 2021/12/21 14:47:02 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_board
{
	pthread_mutex_t	**forks;
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				limit;
}			t_board;

typedef struct s_philo
{
	int				id;
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_board			*board;
	int				is_die;
	int				is_eat;
	int				is_sleep;
	int				eat_count;
}				t_philo;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	*routine(void *arg);
#endif
