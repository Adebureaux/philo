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
# define LOOP	42

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print;
	int				start_time;
	int				cur_time;
	int				last_time;
	int				is_dead;
	int				eat_count;
}				t_philo;

typedef struct s_board
{
	t_philo			*philo;
	int				id;
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				limit;
}			t_board;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	get_time(void);
void	*routine(void *arg);
#endif
