/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:44:52 by acarlson          #+#    #+#             */
/*   Updated: 2019/04/21 14:46:52 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRUS_H
# define VIRUS_H

# include <stdio.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <time.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# ifdef __linux__
#  include <sys/prctl.h>
#  define PCTL(x,y) ptrctl(x,y)
# else
#  define PCTL(x,y)
# endif
# include <unistd.h>

void	thing(void);
void	set_name(char *s1);
void	random_pname(char *s1);
void	colors(void);
void	luigme(void);
void	protection(void);

#endif
