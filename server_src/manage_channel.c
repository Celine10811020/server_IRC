/*
** manage_channel.c for manage_channel in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:31:58 2017 Valentin Nasraty
** Last update Sun Jun 11 20:31:58 2017 Valentin Nasraty
*/

#include "server.h"

int			change_current_channel(t_channel *accueil,
					       t_client *client, t_channel *curr_chan)
{
  t_channel		*tmp;
  t_client		*tmp_cl;

  tmp = accueil;
  while (tmp != NULL)
    {
      tmp_cl = tmp->client;
      while (tmp_cl != NULL)
	{
	  if (tmp_cl->fd_sock == client->fd_sock && tmp_cl != client)
	    {
	      tmp_cl->current_chan = curr_chan;
	      client->current_chan = curr_chan;
	    }
	  tmp_cl = tmp_cl->next;
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}

void			set_fd_of_channel(t_client *client, t_server *srv)
{
  t_client		*tmp;

  FD_ZERO(&srv->readf);
  FD_SET(srv->fd_sock, &srv->readf);
  tmp = client;
  while (tmp != NULL)
    {
      if (socket_is_valid(tmp->fd_sock))
	FD_SET(tmp->fd_sock, &srv->readf);
      tmp = tmp->next;
    }
}

int			channel_manager(t_server *srv, t_channel *ch,
					struct timeval *tv)
{
  t_client		*new_cl;

  set_fd_of_channel(ch->client, srv);
  if (select((srv->fd_max + 1), &srv->readf, NULL, NULL, tv) == -1)
    return (puterror("Error: select failed\n"));
  if (FD_ISSET(srv->fd_sock, &srv->readf))
    {
      putstr("New client connected\n");
      if ((new_cl = add_client(get_accueil_channel(ch))) == NULL)
	return (FAILURE);
      if ((new_cl->fd_sock = accept(srv->fd_sock,
				    (struct sockaddr *)&new_cl->sin, &new_cl->sin_size)) == -1)
	return (puterror("Error: accept failed\n"));
      getsockname(new_cl->fd_sock,
		  (struct sockaddr*)(&new_cl->sin), &new_cl->sin_size);
      new_cl->ip_connection = inet_ntoa(new_cl->sin.sin_addr);
      new_cl->port_connection = ntohs(new_cl->sin.sin_port);
      print_welcome(new_cl->fd_sock);
      srv->fd_max = (srv->fd_max > new_cl->fd_sock) ?
	srv->fd_max : new_cl->fd_sock;
    }
  else if (transfert_data(ch, srv) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

int			init_channel(t_channel *ch, bool first_link)
{
  if ((ch->name = strdup(HOME)) == NULL)
    return (FAILURE);
  if (first_link)
    ch->prev = NULL;
  ch->next = NULL;
  ch->client = NULL;
  return (SUCCESS);
}

t_channel		*add_channel(t_channel *ch)
{
  t_channel		*tmp;
  t_channel		*new_ch;

  if ((new_ch = malloc(sizeof(t_channel))) == NULL)
    return (NULL);
  tmp = ch;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new_ch;
  new_ch->prev = tmp;
  new_ch->next = NULL;
  if (init_channel(new_ch, false) == FAILURE)
    return (NULL);
  return (new_ch);
}
