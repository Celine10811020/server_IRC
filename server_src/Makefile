##
## Makefile for Makefile in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc
## 
## Made by Valentin Nasraty
## Login   <valentin.nasraty@epitech.eu>
## 
## Started on  Thu May 25 19:48:36 2017 Valentin Nasraty
## Last update Sun Jun 11 17:09:00 2017 Valentin Nasraty
##

SRC_SRV		= server.c \
		  basic.c \
		  manage_channel.c \
		  get_channel.c \
		  manage_client.c \
		  get_client.c \
		  data.c \
		  read_message.c \
		  commande.c \
		  str_to_wordtab.c \
		  print_message.c \
		  epur.c \
		  join.c \
		  list.c \
		  names.c \
		  nick.c \
		  part.c \
		  message.c \
		  private_message.c \
		  quit.c \
		  users.c

OBJ_SRV		= $(SRC_SRV:.c=.o)

RM		= rm -f

CC		= gcc -o

NAME_SRV	= server

CFLAGS		= -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code -g3

all:		server

server:		$(OBJ_SRV)
		$(CC) $(NAME_SRV) $(OBJ_SRV)

clean:
		$(RM) $(OBJ_SRV)

fclean:		clean
		$(RM) $(NAME_SRV)

re:		fclean all
