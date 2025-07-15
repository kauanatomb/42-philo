# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 17:32:59 by ktombola          #+#    #+#              #
#    Updated: 2025/07/04 17:50:29 by ktombola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := philo

SRCS     := src/main.c src/philo_utils.c src/philo_utils1.c src/philo_utils2.c \
			src/monitor.c src/parse.c

OBJS     := $(SRCS:.c=.o)

CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INCLUDES := -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re