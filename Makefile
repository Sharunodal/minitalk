# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 14:12:49 by arissane          #+#    #+#              #
#    Updated: 2024/08/26 11:50:43 by arissane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
NAME_BONUS = minitalk_bonus

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft/libft.a

SRCS_CLIENT = client.c
SRCS_SERVER = server.c

SRCS_CLIENT_BONUS = client_bonus.c
SRCS_SERVER_BONUS = server_bonus.c

OFILES_CLIENT = $(SRCS_CLIENT:.c=.o)
OFILES_SERVER = $(SRCS_SERVER:.c=.o)

OFILES_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)
OFILES_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OFILES_CLIENT) $(OFILES_SERVER)
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OFILES_CLIENT) $(LIBFT) -o client
	@$(CC) $(CFLAGS) $(OFILES_SERVER) $(LIBFT) -o server

$(NAME_BONUS): $(OFILES_CLIENT_BONUS) $(OFILES_SERVER_BONUS)
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OFILES_CLIENT_BONUS) $(LIBFT) -o client_bonus
	@$(CC) $(CFLAGS) $(OFILES_SERVER_BONUS) $(LIBFT) -o server_bonus

clean:
	@$(MAKE) -C ./libft clean
	@rm -f $(OFILES_CLIENT) $(OFILES_SERVER)
	@rm -f $(OFILES_CLIENT_BONUS) $(OFILES_SERVER_BONUS)

fclean: clean
	@rm -f client server client_bonus server_bonus ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re bonus
