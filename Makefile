# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smargine <smargine@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 14:14:38 by smargine          #+#    #+#              #
#    Updated: 2023/09/29 03:05:03 by smargine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol
CFLAGS := -Wall -Werror -Wextra -g
LIBFT := libft/libft.a
LIBMLX := ./MLX42/MiniLibX/libmlx42.a

HEADERS := -I ./inc -I $(LIBMLX)/include
LIBS := $(LIBMLX) -ldl -lglfw -pthread -lm
SRCS := ./src/main.c ./src/color.c ./src/fractals.c ./src/user_input.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
		$(MAKE) -C ./libft
		$(MAKE) bonus -C ./libft

$(LIBMLX):
		@cmake $(LIBMLX) -B $(LIBMLX)/MiniLibX && make -C $(LIBMLX)/MiniLibX -j4

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
		@$(CC) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

clean:
		@rm -rf $(OBJS)
		@make clean -C ./libft
		@rm -rf $(LIBMLX)/MiniLibX

fclean: clean
		@make fclean -C ./libft
		@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
