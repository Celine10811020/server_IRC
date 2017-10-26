/*
** users.c for users in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:36:17 2017 Valentin Nasraty
** Last update Sun Jun 11 18:41:36 2017 Valentin Nasraty
*/

#include "server.h"

void		print_all_users(t_client *client, int fd_sock)
{
  putclient("\tClient : ", fd_sock);
  putclient(client->nickname, fd_sock);
  putclient("\tcurrent channel : ", fd_sock);
  putclient(client->current_chan->name, fd_sock);
  putclient("\n", fd_sock);
}

void		users(t_command *cmd)
{
  t_channel	*tmp;
  t_client	*tmp_cli;

  tmp = get_accueil_channel(cmd->channel);
  while (tmp != NULL)
    {
      putclient("Channel : ", cmd->client->fd_sock);
      putclient(tmp->name, cmd->client->fd_sock);
      putclient("\n", cmd->client->fd_sock);
      if (tmp->client)
	{
	  tmp_cli = tmp->client;
	  while (tmp_cli->prev != NULL)
	    tmp_cli = tmp_cli->prev;
	  while (tmp_cli != NULL)
	    {
	      print_all_users(tmp_cli, cmd->client->fd_sock);
	      tmp_cli = tmp_cli->next;
	    }
	}
      else
	putclient("\tNo client\n", cmd->client->fd_sock);
      tmp = tmp->next;
    }
}
