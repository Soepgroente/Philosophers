# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vincent <vincent@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2023/07/02 13:49:49 by vincent       #+#    #+#                  #
#    Updated: 2023/11/06 12:49:01 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
CC		= gcc
RM		= rm -rf
CFLAGS	= -Wextra -Wall -Werror -pthread -flto -Ofast -g #-fsanitize=thread 
OBJDIR	= Philobjects

SRCS	= 	clean_up.c \
			create_processes.c \
			initialize_structs.c \
			lock_functions.c \
			main.c \
			ft_philatoi.c \
			ft_philitoa.c \
			routine.c \
			stalking.c \
			time_functions.c \
			utils.c \

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re