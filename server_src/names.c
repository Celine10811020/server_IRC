/*
** names.c for names in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:37:00 2017 Valentin Nasraty
** Last update Sun Jun 11 18:27:41 2017 Valentin Nasraty
*/

#include "server.h"

void		print_names(t_channel *channel, t_command *cmd)
{
  t_client	*tmp;

  putclient("Channel : ", cmd->client->fd_sock);
  putclient(channel->name, cmd->client->fd_sock);
  putclient("\n", cmd->client->fd_sock);
  if ((tmp = channel->client) != NULL)
    {
      while (tmp != NULL)
	{
	  putclient("\tClient : ", cmd->client->fd_sock);
	  putclient(tmp->nickname, cmd->client->fd_sock);
	  putclient("\n", cmd->client->fd_sock);
	  tmp = tmp->next;
	}
    }
  else
    putclient("\tNo client\n", cmd->client->fd_sock);
}

void		names(t_command *cmd)
{
  t_channel	*channel;

  if (count_tab(cmd->cmd_tab) == 2)
    {
      if ((channel = get_channel_by_name(cmd->cmd_tab[1],
					 cmd->channel)) != NULL)
	print_names(channel, cmd);
      else
	{
	  putclient("Channel ", cmd->client->fd_sock);
	  putclient(cmd->cmd_tab[1], cmd->client->fd_sock);
	  putclient(" does not exist\n", cmd->client->fd_sock);
	}
    }
  else
    putclient("Usage: /names $channel\n", cmd->client->fd_sock);
}
