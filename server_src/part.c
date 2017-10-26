/*
** part.c for part in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:35:12 2017 Valentin Nasraty
** Last update Sun Jun 11 18:11:16 2017 Valentin Nasraty
*/

#include "server.h"

void		change_client_channel(t_channel *accueil, t_channel *ch,
				      t_channel *last_chan, t_command *cmd)
{
  t_client	*new_cl;

  if (client_is_on_channel(ch, cmd->client))
    {
      print_message_commande(cmd->client, cmd->cmd_tab[0], cmd->cmd_tab[1]);
      if ((last_chan = get_first_chan_connected(accueil, cmd->client)) != NULL)
	{
	  if (strncmp(cmd->cmd_tab[1], cmd->client->current_chan->name,
		      strlen(cmd->client->current_chan->name)) == 0)
	      change_current_channel(accueil, cmd->client, last_chan);
	}
      else
	{
	  new_cl = add_client(accueil);
	  free(new_cl->nickname);
	  new_cl->nickname = strdup(cmd->client->nickname);
	  new_cl->fd_sock = cmd->client->fd_sock;
	  new_cl->ip_connection = strdup(cmd->client->ip_connection);
	  new_cl->port_connection = cmd->client->port_connection;
	  change_current_channel(accueil, cmd->client, accueil);
	}
      ch->client = delete_client(ch->client, cmd->client);
    }
  else
    putclient("Error: Client is not on this channel.\n", cmd->client->fd_sock);
}

void		part(t_command *cmd)
{
  t_channel	*tmp;
  t_channel	*last_chan;
  t_channel	*accueil;

  last_chan = NULL;
  if (count_tab(cmd->cmd_tab) == 2)
    {
      accueil = get_accueil_channel(cmd->channel);
      if ((tmp = get_channel_by_name(cmd->cmd_tab[1], accueil)) != NULL)
	change_client_channel(accueil, tmp, last_chan, cmd);
      else
	putclient("Error: This channel is not created.\n", cmd->client->fd_sock);
    }
  else
    putclient("Usage: PART $channel\n", cmd->client->fd_sock);
}
