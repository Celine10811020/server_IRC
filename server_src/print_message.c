/*
** print_message.c for print_message in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Mon Jun  5 17:23:35 2017 Valentin Nasraty
** Last update Sun Jun 11 18:16:18 2017 Valentin Nasraty
*/

#include "server.h"

void		format_message_commande(t_client *client, int fd_sock,
					char *cmd, char *param)
{
  putclient(":", fd_sock);
  putclient(client->nickname, fd_sock);
  putclient("!", fd_sock);
  putclient(client->ip_connection, fd_sock);
  putclient(" ", fd_sock);
  putclient(cmd, fd_sock);
  putclient(" ", fd_sock);
  putclient(param, fd_sock);
}

void		print_private_message(t_client *client,
				      int fd_sock, char **cmd_tab)
{
  int		i;

  i = 1;
  format_message_commande(client, fd_sock, cmd_tab[0], cmd_tab[1]);
  putclient(" :", fd_sock);
  while (cmd_tab[++i])
    {
      putclient(cmd_tab[i], fd_sock);
      if (cmd_tab[i + 1] != NULL)
	putclient(" ", fd_sock);
    }
  putclient("\r\n", fd_sock);
}

void		print_message_commande(t_client *client,
				       char *cmd, char *param)
{
  t_client	*tmp;

  tmp = client->current_chan->client;
  while (tmp != NULL)
    {
      format_message_commande(client, tmp->fd_sock, cmd, param);
      putclient("\r\n", tmp->fd_sock);
      tmp = tmp->next;
    }
}

void		print_names_list(t_client *client, char *name_chan)
{
  t_client	*tmp;

  putclient("353 ", client->fd_sock);
  putclient(name_chan, client->fd_sock);
  putclient(" : NAMES", client->fd_sock);
  putclient(client->nickname, client->fd_sock);
  tmp = client->current_chan->client;
  while (tmp != NULL)
    {
      if (strncmp(NO_NAME, tmp->nickname, strlen(NO_NAME)) != 0 &&
	  tmp->nickname != client->nickname)
	{
	  putclient(" ", client->fd_sock);
	  putclient(tmp->nickname, client->fd_sock);
	}
      tmp = tmp->next;
     }
  putclient("\r\n", client->fd_sock);
  putclient("366 ", client->fd_sock);
  putclient(name_chan, client->fd_sock);
  putclient(" :End of /NAMES list", client->fd_sock);
  putclient("\r\n", client->fd_sock);
}

void		print_welcome(int fd)
{
  putclient("001 Welcome on\r\n", fd);
  putclient(" \x1b[31m                     ________  ______\n", fd);
  putclient(" \x1b[31m   ____ ___  __  __ /  _/ __ \\/ ____/\n", fd);
  putclient(" \x1b[33m  / __ `__ \\/ / / / / // /_/ / /     \n", fd);
  putclient(" \x1b[32m / / / / / / /_/ / / // _, _/ /___   \n", fd);
  putclient(" \x1b[34m/_/ /_/ /_/\\__, //___/_/ |_|\\____/   \n", fd);
  putclient(" \x1b[35m          /____/                    \n\r\n\x1b[0m", fd);
}
