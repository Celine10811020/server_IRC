/*
** manage_client.c for manage_client in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 17:08:35 2017 Valentin Nasraty
** Last update Sun Jun 11 18:21:47 2017 Valentin Nasraty
*/

#include "server.h"

void			delete_client_allchan(t_channel *ch, t_client *del_node)
{
  t_channel		*tmp;
  t_client		*copy;

  tmp = get_accueil_channel(ch);
  while (tmp != NULL)
    {
      if ((copy = find_copy_client(tmp, del_node)) != NULL)
	tmp->client = delete_client(tmp->client, copy);
      tmp = tmp->next;
    }
  ch->client = delete_client(ch->client, del_node);
}

t_client		*delete_client(t_client *client_list, t_client *del_node)
{
  t_client		*tmp;

  if (del_node->next && del_node->prev)
    {
      del_node->prev->next = del_node->next;
      del_node->next->prev = del_node->prev;
    }
  else if (del_node->prev)
    del_node->prev->next = NULL;
  else
    {
      tmp = client_list->next;
      if (tmp)
	tmp->prev = NULL;
      client_list = NULL;
      free(client_list);
      return (tmp);
    }
  del_node = NULL;
  free(del_node);
  return (client_list);
}

int			set_name_client(t_client *client, t_channel *curr_chan)
{
  char			*nb_string;
  static int		nb = 0;

  if ((nb_string = int_to_string(++nb)) == NULL)
    return (FAILURE);
  if (client->nickname)
    free(client->nickname);
  if ((client->nickname = concat_msg(NO_NAME, nb_string)) == NULL)
    return (FAILURE);
  free(nb_string);
  client->current_chan = curr_chan;
  return (SUCCESS);
}

t_client		*create_first_client(t_client *new_cl, t_channel *chan)
{
  new_cl->next = NULL;
  new_cl->prev = NULL;
  new_cl->sin_size = sizeof(new_cl->sin);
  if ((new_cl->nickname = strdup(NO_NAME)) == NULL)
    return (NULL);
  new_cl->current_chan = chan;
  return (new_cl);
}

t_client		*add_client(t_channel *ch)
{
  t_client		*new_cl;
  t_client		*tmp;

  if ((new_cl = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  tmp = ch->client;
  if (tmp != NULL)
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new_cl;
      new_cl->prev = tmp;
      new_cl->next = NULL;
      new_cl->nickname = NULL;
      tmp->next->sin_size = sizeof(tmp->next->sin);
      if (set_name_client(tmp->next, ch) == FAILURE)
	return (NULL);
    }
  else
    {
      if ((tmp = create_first_client(new_cl, ch)) == FAILURE)
	return (NULL);
      ch->client = tmp;
    }
  return (new_cl);
}
