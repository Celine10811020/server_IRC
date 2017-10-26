/*
** join.c for join in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:36:34 2017 Valentin Nasraty
** Last update Sun Jun 11 17:28:45 2017 Valentin Nasraty
*/

#include "server.h"

void		add_copy_client(t_channel *accueil, t_channel *ch,
				t_client *copy_client, t_command *cmd)
{
  copy_client = add_client(ch);
  copy_client->fd_sock = cmd->client->fd_sock;
  copy_client->port_connection = cmd->client->port_connection;
  copy_client->ip_connection = strdup(cmd->client->ip_connection);
  free(copy_client->nickname);
  copy_client->nickname = strdup(cmd->client->nickname);
  change_current_channel(accueil, copy_client, ch);
  if (client_is_on_channel(accueil, cmd->client))
    accueil->client = delete_client(accueil->client, cmd->client);
  print_message_commande(copy_client, cmd->cmd_tab[0], cmd->cmd_tab[1]);
  print_names_list(copy_client, ch->name);
}

void		join(t_command *cmd)
{
  t_channel	*tmp;
  t_channel	*accueil;
  t_client	*copy_client;

  copy_client = NULL;
  if (count_tab(cmd->cmd_tab) == 2)
    {
      accueil = get_accueil_channel(cmd->channel);
      if ((tmp = get_channel_by_name(cmd->cmd_tab[1], accueil)) != NULL)
	{
	  if (client_is_on_channel(tmp, cmd->client))
	    return;
	  add_copy_client(accueil, tmp, copy_client, cmd);
	}
      else
	{
	  tmp = add_channel(cmd->channel);
	  tmp->name = strdup(cmd->cmd_tab[1]);
	  add_copy_client(accueil, tmp, tmp->client, cmd);
	}
    }
  else
    putclient("Usage: /join $channel\n", cmd->client->fd_sock);
}
