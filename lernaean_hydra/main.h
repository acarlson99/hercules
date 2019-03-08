/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:49:09 by acarlson          #+#    #+#             */
/*   Updated: 2019/03/07 17:19:38 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>

# define PORT 8080
# define BACKLOG 42

int			ft_strcmp(const char *s1, const char *s2);
int			read_args(int argc, char **argv);

#endif
