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

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft/libft.a

SRCS_CLIENT = client.c
SRCS_SERVER = server.c

OFILES_CLIENT = $(SRCS_CLIENT:.c=.o)
OFILES_SERVER = $(SRCS_SERVER:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES_CLIENT) $(OFILES_SERVER)
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OFILES_CLIENT) $(LIBFT) -o client
	@$(CC) $(CFLAGS) $(OFILES_SERVER) $(LIBFT) -o server

clean:
	@$(MAKE) -C ./libft clean
	@rm -f $(OFILES_CLIENT) $(OFILES_SERVER)

fclean: clean
	@rm -f client server ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re
