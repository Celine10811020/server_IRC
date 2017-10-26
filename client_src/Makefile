##
## Makefile for client in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/client
## 
## Made by Valentin Nasraty
## Login   <valentin.nasraty@epitech.eu>
## 
## Started on  Thu Jun  1 14:22:11 2017 Valentin Nasraty
## Last update Fri Jun  2 16:27:43 2017 Valentin Nasraty
##

SRC_CLT		= client.c \
		  basic.c \
		  str_to_wordtab.c \
		  parser.c \
		  data.c

OBJ_CLT		= $(SRC_CLT:.c=.o)

RM		= rm -f

CC		= gcc -o

NAME_CLT	= client

CFLAGS		= -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code

all:		client

client:		$(OBJ_CLT)
		$(CC) $(NAME_CLT) $(OBJ_CLT)

clean:
		$(RM) $(OBJ_CLT)

fclean:		clean
		$(RM) $(NAME_CLT)

re:		fclean all
