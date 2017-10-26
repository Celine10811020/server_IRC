/*
** server.h for server in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Thu May 25 19:54:35 2017 Valentin Nasraty
** Last update Sun Jun 11 19:39:03 2017 Valentin Nasraty
*/

#ifndef __SERVER_H__
# define __SERVER_H__

# define FAILURE	0
# define SUCCESS	!(FAILURE)
# define MAX_CLIENT	1000
# define BUFFER_SIZE	512
# define NB_OCTET_READ	64
# define SIZE_CMD_TAB	11
# define NB_CMD		(SIZE_CMD_TAB - 1)
# define TIME_SELECT	0
# define U_TIME_SELECT	1
# define DECONNECTED	404
# define HOME		"Accueil"
# define NO_NAME	"Anonymous"
# define EOF_SIGNAL	"EOF_signal"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct		s_server
{
  int			fd_sock;
  int			fd_max;
  fd_set		readf;
  char			**cmd_list;
}			t_server;

typedef struct		s_client
{
  struct sockaddr_in	sin;
  unsigned int		sin_size;
  int			fd_sock;
  char			*nickname;
  char			*ip_connection;
  int			port_connection;
  struct s_channel	*current_chan;
  struct s_client	*next;
  struct s_client	*prev;
}			t_client;

typedef struct		s_channel
{
  t_client		*client;
  char			*name;
  struct s_channel	*next;
  struct s_channel	*prev;
}			t_channel;

typedef struct		s_command
{
  char			**cmd_tab;
  t_client		*client;
  t_channel		*channel;
  void			(*func_ptr[NB_CMD])(struct s_command*);
}			t_command;

/* EPUR */
char			**epur_new_line(char **tab);

/* PRINT_MESSAGE */
void			format_message_commande(t_client *client,
						int fd_sock, char *cmd, char *param);
void			print_private_message(t_client *client,
					      int fd_sock, char **cmd_tab);
void			print_message_commande(t_client *client,
					       char *cmd, char *param);
void			print_names_list(t_client *client, char *name_chan);
void			print_welcome(int fd);

/* BASIC */
bool			socket_is_valid(int socket);
void			putstr(char *str);
int			puterror(char *str);
void			putclient(char *str, int fd_sock);
char			*int_to_string(int nb);

/* GET_CLIENT */
t_client		*get_client_by_name(char *name, t_channel *node);
t_client		*find_copy_client(t_channel *channel, t_client *client);
bool			client_is_on_channel(t_channel *channel, t_client *client);

/* MANAGE_CLIENT */
void			delete_client_allchan(t_channel *ch, t_client *del_node);
t_client		*delete_client(t_client *client_list, t_client *client);
int			set_name_client(t_client *client, t_channel *curr_chan);
t_client		*create_first_client(t_client *new_cl, t_channel *accueil);
t_client		*add_client(t_channel *ch);

/* GET_CHANNEL */
t_channel		*get_first_chan_connected(t_channel *ch, t_client *cl);
t_channel		*get_channel_by_name(char *name, t_channel *node);
t_channel		*get_accueil_channel(t_channel *node);

/* MANAGE_CHANNEL */
int			change_current_channel(t_channel *accueil,
					       t_client *client, t_channel *curr_chan);
void			set_fd_of_channel(t_client *client, t_server *srv);
int			channel_manager(t_server *srv,
					t_channel *ch, struct timeval *tv);
t_channel	       	*add_channel(t_channel *ch);
int			init_channel(t_channel *ch, bool first_link);

/* DATA */
void			write_data_on_channel(char *msg, t_client *sender);
int			loop_on_input(t_server *srv, t_channel *ch,
				      t_client *client, char *msg);
int			transfert_data(t_channel *ch, t_server *srv);

/* MESSAGE */
bool			is_end_msg_telnet(char *msg);
bool			is_end_msg_netcat(char *msg);
char			*concat_msg(char *msg, char *new_msg);
char			*shutdown_client(t_channel *ch, t_client *client);
char			*receive_msg(t_client *client, t_channel *ch);

/* SERVER */
int			loop_server(t_server *srv, t_channel *ch);
int			init_server(t_server *srv, int port);

/* COMMANDE */
char			**init_command_list();
int			which_func(char *msg, char **command_list);
void			accept_file(t_command *cmd);
void			set_function_pointer(t_command *cmd);
int			commander(t_server *srv, t_channel *ch,
				  t_client *client, char *msg);

/* STR_TO_WORDTAB */
int			count_tab(char **tab);
int			nb_mot(char *str, char sep);
int			nb_mot_bis(char *str, char sep1, char sep2);
char			**str_to_wordtab(char *str, char sep);
char			**str_to_wordtab_bis(char *str, char sep1, char sep2);

/* NICK */
void			nick(t_command *cmd);

/* LIST */
void			list(t_command *cmd);

/* JOIN */
void			add_copy_client(t_channel *accueil, t_channel *ch,
					t_client *copy_client, t_command *cmd);
void			join(t_command *cmd);

/* PART */
void			change_client_channel(t_channel *accueil, t_channel *ch,
					      t_channel *last_chan, t_command *cmd);
void			part(t_command *cmd);

/* USERS */
void			print_all_users(t_client *client, int fd_sock);
void			users(t_command *cmd);

/* NAMES */
void			print_names(t_channel *channel, t_command *cmd);
void			names(t_command *cmd);

/* MESSAGE */
void			message(t_command *cmd);

/* PRIVATE_MESSAGE */
void			private_message(t_command *cmd);

/* QUIT */
void			quit(t_command *cmd);

#endif /* !__SERVER_H__ */
