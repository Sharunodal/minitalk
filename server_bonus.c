/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:13:20 by arissane          #+#    #+#             */
/*   Updated: 2024/08/26 13:23:54 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h" 

static char	*add_char(char byte, char *str)
{
	char	*final;
	int		i;

	i = 0;
	final = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!final)
		return (NULL);
	while (str[i])
	{
		final[i] = str[i];
		i++;
	}
	final[i] = byte;
	final[i + 1] = 0;
	free(str);
	return (final);
}

static void	print_free(char **str, int client_pid)
{
	ft_printf("%s\n", *str);
	free(*str);
	*str = NULL;
	kill(client_pid, SIGUSR2);
}

static void	process(int signal, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	byte = 0;
	static char	*str;

	(void)context;
	if (!str)
		str = ft_strdup("");
	i++;
	if (signal == SIGUSR1)
		byte |= 1;
	if (signal == SIGUSR2)
		byte |= 0;
	if (i != 8)
		byte <<= 1;
	if (i == 8)
	{
		if (byte != 0)
			str = add_char(byte, str);
		if (byte == 0)
			print_free(&str, info->si_pid);
		i = 0;
		byte = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	received_data;
	int					pid;

	pid = getpid();
	ft_printf("The server pid == %d\n", pid);
	sigemptyset(&received_data.sa_mask);
	received_data.sa_sigaction = &process;
	received_data.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &received_data, NULL) == -1)
	{
		ft_printf("Error handling the signal\n");
		return (0);
	}
	if (sigaction(SIGUSR2, &received_data, NULL) == -1)
	{
		ft_printf("error handling the signal\n");
		return (0);
	}
	while (1)
		pause();
	return (0);
}
