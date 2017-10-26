/*
** data.c for data in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Fri May 26 17:29:15 2017 Valentin Nasraty
** Last update Sun Jun 11 20:49:41 2017 Valentin Nasraty
*/

#include "server.h"

void			write_data_on_channel(char *msg, t_client *sender)
{
  t_client		*tmp_cl;

  tmp_cl = sender->current_chan->client;
  while (tmp_cl != NULL)
    {
      if (tmp_cl->fd_sock != sender->fd_sock)
	{
	  putclient("[", tmp_cl->fd_sock);
	  putclient(sender->nickname, tmp_cl->fd_sock);
	  putclient("] ", tmp_cl->fd_sock);
	  putclient(msg, tmp_cl->fd_sock);
	  putclient("\r\n", tmp_cl->fd_sock);
	}
      tmp_cl = tmp_cl->next;
    }
}

int			loop_on_input(t_server *srv, t_channel *ch,
				      t_client *client, char *msg)
{
  int			i;
  int			res;
  char			**all_cmd;
  char			*backup_msg;

  if ((backup_msg = strdup(msg)) == NULL)
    return (FAILURE);
  if ((all_cmd = str_to_wordtab_bis(msg, '\r', '\n')) == NULL)
    return (FAILURE);
  i = -1;
  while (all_cmd[++i])
    {
      if ((res = commander(srv, ch, client, all_cmd[i])) == 1)
	write_data_on_channel(backup_msg, client);
      else if (res == DECONNECTED)
	all_cmd[i + 1] = NULL;
    }
  free(all_cmd);
  free(backup_msg);
  return (SUCCESS);
}

int			transfert_data(t_channel *ch, t_server *srv)
{
  char			*msg;
  t_client		*tmp;

  tmp = ch->client;
  while (tmp != NULL)
    {
      if (FD_ISSET(tmp->fd_sock, &srv->readf))
	{
	  if ((msg = receive_msg(tmp, ch)) == NULL)
	    return (FAILURE);
	  else if (strncmp(msg, EOF_SIGNAL, strlen(EOF_SIGNAL)) != 0)
	    {
	      if (loop_on_input(srv, ch, tmp, msg) == FAILURE)
		return (FAILURE);
	      free(msg);
	    }
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}
