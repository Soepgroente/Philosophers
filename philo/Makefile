# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vincent <vincent@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2023/07/02 13:49:49 by vincent       #+#    #+#                  #
#    Updated: 2023/09/30 15:44:57 by vincent       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= gcc
RM		= rm -rf
CFLAGS	= -Wextra -Wall -Werror -pthread -Ofast #-g -fsanitize=thread
OBJDIR	= Philobjects

SRCS	= 	clean_up.c \
			initialize_structs.c \
			lock_functions.c \
			main.c \
			philatoi.c \
			prepare_routine.c \
			routine.c \
			stalking.c \
			utilities.c

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