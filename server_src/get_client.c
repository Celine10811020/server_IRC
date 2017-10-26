/*
** get_client.c for get_client in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 17:08:16 2017 Valentin Nasraty
** Last update Sun Jun 11 18:28:38 2017 Valentin Nasraty
*/

#include "server.h"

t_client		*get_client_by_name(char *name, t_channel *node)
{
  t_channel		*tmp;
  t_client		*tmp_cl;

  tmp = get_accueil_channel(node);
  while (tmp != NULL)
    {
      tmp_cl = tmp->client;
      while (tmp_cl != NULL)
	{
	  if (strncmp(tmp_cl->nickname, name, strlen(tmp_cl->nickname)) == 0)
	    return (tmp_cl);
	  tmp_cl = tmp_cl->next;
	}
      tmp = tmp->next;
    }
  return (NULL);
}

t_client		*find_copy_client(t_channel *channel, t_client *client)
{
  t_client		*tmp;

  tmp = channel->client;
  while (tmp != NULL)
    {
      if (tmp->fd_sock == client->fd_sock
	  && tmp != client)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

bool			client_is_on_channel(t_channel *channel, t_client *client)
{
  t_client		*tmp;

  tmp = channel->client;
  while (tmp != NULL)
    {
      if (tmp->fd_sock == client->fd_sock)
	return (true);
      tmp = tmp->next;
    }
  return (false);
}
