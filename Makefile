# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antonweizmann <antonweizmann@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 09:29:29 by antonweizma       #+#    #+#              #
#    Updated: 2024/05/04 09:53:27 by antonweizma      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS =  $(INCLUDES) -Wall -Wextra -Werror -pthread -g
INCLUDES = -I./includes

SRC_PATH = srcs
OBJ_PATH = obj

SRCS_MAIN =	main.c		init.c		monitor_philo.c		philosopher.c		utils.c		utils2.c

OBJ_NAME = $(SRCS_MAIN:.c=.o)
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS)
	@printf "%-100s\n" "$(NAME) compiled"

$(OBJ_PATH)	:
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@printf "%-100s\r" "$(CC) $(CFLAGS) -o $@"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
