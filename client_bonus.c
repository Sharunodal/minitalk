/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:14:05 by arissane          #+#    #+#             */
/*   Updated: 2024/08/26 11:26:30 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	g_server_reply;

static void	handle_reply(int signal)
{
	g_server_reply = signal;
}

static void	confirm_message(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("Message sent successfully\n");
}

static void	bit_convert(unsigned char c, int id)
{
	unsigned char	bit;
	int				i;

	i = 7;
	while (i > -1)
	{
		bit = (c >> i & 1);
		if (bit == 1)
			kill(id, SIGUSR1);
		else if (bit == 0)
			kill(id, SIGUSR2);
		else
			write(1, "error\n", 6);
		i--;
		while (g_server_reply == 0)
		{
			sleep(5);
			if (g_server_reply == 0)
			{
				ft_printf("Server timed out\n");
				exit (0);
			}
		}
		g_server_reply = 0;
	}
}

int	main(int argc, char **argv)
{
	int		id;
	char	*str;
	int		i;

	if (argc != 3)
	{
		ft_printf("invalid input\n");
		return (0);
	}
	signal(SIGUSR1, &handle_reply);
	signal(SIGUSR2, &confirm_message);
	id = ft_atoi(argv[1]);
	str = argv[2];
	i = 0;
	while (str[i])
	{
		bit_convert((unsigned char)str[i], id);
		i++;
	}
	bit_convert(0, id);
	return (0);
}
