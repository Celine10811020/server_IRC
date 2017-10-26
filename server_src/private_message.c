/*
** private_message.c for private_message in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:40:45 2017 Valentin Nasraty
** Last update Sun Jun 11 18:22:40 2017 Valentin Nasraty
*/

#include "server.h"

void		private_message(t_command *cmd)
{
  t_client	*client;
  t_client	*tmp;
  t_channel	*channel;

  if (count_tab(cmd->cmd_tab) >= 3)
    {
      if ((client = get_client_by_name(cmd->cmd_tab[1], cmd->channel)) != NULL)
	print_private_message(cmd->client, client->fd_sock, cmd->cmd_tab);
      else if ((channel = get_channel_by_name(cmd->cmd_tab[1],
					      cmd->channel)) != NULL)
	{
	  tmp = channel->client;
	  while (tmp != NULL)
	    {
	      if (tmp->fd_sock != cmd->client->fd_sock)
		print_private_message(cmd->client, tmp->fd_sock, cmd->cmd_tab);
	      tmp = tmp->next;
	    }
	}
      else
	putclient("User or channel doesn't exist\r\n", cmd->client->fd_sock);
    }
  else
    putclient("Usage: PRIVMSG $nickname\r\n", cmd->client->fd_sock);
}
