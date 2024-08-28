/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:30:41 by arissane          #+#    #+#             */
/*   Updated: 2024/08/26 11:15:28 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_server_reply;

static void	handle_reply(int signal)
{
	g_server_reply = signal;
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
