/*
** get_channel.c for get_channel in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:31:15 2017 Valentin Nasraty
** Last update Sun Jun 11 18:05:45 2017 Valentin Nasraty
*/

#include "server.h"

t_channel		*get_first_chan_connected(t_channel *ch, t_client *cl)
{
  t_channel		*tmp;
  t_client		*tmp_cl;

  tmp = get_accueil_channel(ch);
  while (tmp != NULL)
    {
      tmp_cl = tmp->client;
      while (tmp_cl != NULL)
	{
	  if (tmp_cl->fd_sock == cl->fd_sock &&
	      strncmp(tmp->name, cl->current_chan->name,
		      strlen(cl->current_chan->name)) != 0)
	    return (tmp);
	  tmp_cl = tmp_cl->next;
	}
      tmp = tmp->next;
    }
  return (NULL);
}

t_channel		*get_channel_by_name(char *name, t_channel *node)
{
  t_channel		*tmp;

  tmp = get_accueil_channel(node);
  while (tmp != NULL)
    {
      if (strncmp(tmp->name, name, strlen(tmp->name)) == 0)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

t_channel		*get_accueil_channel(t_channel *node)
{
  t_channel		*accueil;

  accueil = node;
  while (accueil->prev != NULL)
    accueil = accueil->prev;
  return (accueil);
}
