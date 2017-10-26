##
## Makefile for Makefile in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc
## 
## Made by Valentin Nasraty
## Login   <valentin.nasraty@epitech.eu>
## 
## Started on  Thu May 25 19:48:36 2017 Valentin Nasraty
## Last update Sun Jun 11 18:49:55 2017 Valentin Nasraty
##

SRC_SRV		= server_src/server.c \
		  server_src/basic.c \
		  server_src/manage_channel.c \
		  server_src/get_channel.c \
		  server_src/manage_client.c \
		  server_src/get_client.c \
		  server_src/data.c \
		  server_src/read_message.c \
		  server_src/commande.c \
		  server_src/str_to_wordtab.c \
		  server_src/print_message.c \
		  server_src/epur.c \
		  server_src/join.c \
		  server_src/list.c \
		  server_src/names.c \
		  server_src/nick.c \
		  server_src/part.c \
		  server_src/message.c \
		  server_src/private_message.c \
		  server_src/quit.c \
		  server_src/users.c

SRC_CLT		= client_src/client.c \
		  client_src/basic.c \
		  client_src/str_to_wordtab.c \
		  client_src/parser.c \
		  client_src/data.c

OBJ_SRV		= $(SRC_SRV:.c=.o)

OBJ_CLT		= $(SRC_CLT:.c=.o)

RM		= rm -f

CC		= gcc -o

NAME_SRV	= server

NAME_CLT	= client

CFLAGS		= -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code -g3

all:		server client

server:		$(OBJ_SRV)
		$(CC) $(NAME_SRV) $(OBJ_SRV)

client:		$(OBJ_CLT)
		$(CC) $(NAME_CLT) $(OBJ_CLT)

clean:
		$(RM) $(OBJ_SRV) $(OBJ_CLT)

fclean:		clean
		$(RM) $(NAME_SRV) $(NAME_CLT)

re:		fclean all
