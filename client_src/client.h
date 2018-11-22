/*
** client.h for client in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Thu May 25 19:55:36 2017 Valentin Nasraty
** Last update Sat Jun  3 00:09:02 2017 Valentin Nasraty
*/

#ifndef __CLIENT_H__
# define __CLIENT_H__

# define SIZE_BUFF	512
# define INPUT		0
# define OUTPUT        1
# define FAILURE	0
# define SUCCESS	!(FAILURE)
# define BAD_ADDR	404
# define LOAD_CHAR	'|'

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct		s_client
{
  int			fd_sock;
  char			*ip_addr;
  int			port;
}			t_client;

/* CLIENT */
int			wait_for_ip_addr(t_client *clt);
int			init_client(t_client *clt);

/* BASIC */
void			print_loading_connection();
void			putstr(char *str);
int			puterror(char *str);

/* STR_TO_WORDTAB */
int			count_tab(char **tab);
int			nb_mot(char *str, char sep);
char			**str_to_wordtab(char *str, char sep);

/* PARSER */
int			find_char(char *buff, char c);
bool			pars_addr(char *buff, t_client *clt);

/* DATA */
void			set_fd(int fd_sock, fd_set *readf);
int			read_write_data(char *buff, int fd_read, int fd_write);
int			transfert_data(t_client *clt);

#endif /* !__CLIENT_H__ */
