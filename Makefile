# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vincent <vincent@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2023/07/02 13:49:49 by vincent       #+#    #+#                  #
#    Updated: 2023/09/11 15:48:19 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= gcc
RM		= rm -rf
CFLAGS	= -Wextra -Wall -Werror -pthread #-fsanitize=address
OBJDIR	= Philobjects

SRCS	= philatoi.c main.c

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