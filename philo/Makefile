# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vincent <vincent@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2023/07/02 13:49:49 by vincent       #+#    #+#                  #
#    Updated: 2023/10/12 21:19:59 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= cc
RM		= rm -rf
CFLAGS	= -Wextra -Wall -Werror -flto -O3 -g -fsanitize=thread #-pthread 
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