/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:26:08 by lzaccome          #+#    #+#             */
/*   Updated: 2021/12/30 22:32:45 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define SIG_EVEN 0
# define SIG_ODD 1
# define SIG_BLOCK_EAT 2
# define SIG_TERMINATE 3

typedef struct s_stuff {
	int				nbr_philo;
	int				ttd;
	int				tte;
	int				tts;
	long long		init_time;
	int				last_ate;
	int				died;
	struct s_philo	*philo;
	pthread_mutex_t	display;
	pthread_mutex_t	begin;
	pthread_mutex_t	death;
}				t_stuff;

typedef struct s_philo {
	pthread_t		t_id;
	int				id;
	int				meals;
	int				forks;
	long long		last_ate;
	long long		start_time;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	time;
	pthread_mutex_t	nb_meals;
	t_stuff			*stuff;
}				t_philo;

/* -------------------------------------------------------------------------- */
/*                              FILE = ./main.c                               */
/* -------------------------------------------------------------------------- */
int				main(int ac, char **av);
int				died(t_philo *p);
int				last_meal_ate(t_philo *p);
void			*routine(void *philo);
void			print(t_philo *p, char *str);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./parsing.c                            */
/* -------------------------------------------------------------------------- */
int				parse(int ac, char **av);
void			init_stuff(t_stuff *stuff, char **av, int ac);
void			control_parsing(t_stuff *stuff, char **av, int ac);
void			init_philo(t_stuff *stuff);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./atoi.c                               */
/* -------------------------------------------------------------------------- */
int				ft_atoi(const char *str, int *ret, long res);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./error.c                              */
/* -------------------------------------------------------------------------- */
void			failed_malloc(void);
void			error_value(void);
void			end_free(t_stuff *stuff);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./utils.c                              */
/* -------------------------------------------------------------------------- */
int				ft_strlen(char *str);
void			ft_putstr(char *str);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./sleep.c                              */
/* -------------------------------------------------------------------------- */
long			get_time(long sleep);
void			ft_pause(long sleep);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./death_routine.c                      */
/* -------------------------------------------------------------------------- */
void			*death_routine(void *philo);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./meals.c                              */
/* -------------------------------------------------------------------------- */
void			eat(t_philo *p);
int				get_forks(t_philo *p);
void			limit_meals(t_philo *p);
void			release_forks(t_philo *p);

#endif
