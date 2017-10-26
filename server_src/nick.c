/*
** nick.c for nick in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:34:37 2017 Valentin Nasraty
** Last update Sun Jun 11 16:34:51 2017 Valentin Nasraty
*/

#include "server.h"

void		nick(t_command *cmd)
{
  if (cmd->cmd_tab[1])
    {
      putclient(":", cmd->client->fd_sock);
      if (strstr(cmd->client->nickname, NO_NAME) != NULL)
	putclient("(null)", cmd->client->fd_sock);
      else
	putclient(cmd->client->nickname, cmd->client->fd_sock);
      putclient("!", cmd->client->fd_sock);
      putclient(cmd->client->ip_connection, cmd->client->fd_sock);
      putclient(" NICK ", cmd->client->fd_sock);
      putclient(cmd->cmd_tab[1], cmd->client->fd_sock);
      putclient("\r\n", cmd->client->fd_sock);
      if (cmd->client->nickname)
	free(cmd->client->nickname);
      cmd->client->nickname = strdup(cmd->cmd_tab[1]);
    }
  else
    putclient("Usage: NICK $nickname\n", cmd->client->fd_sock);
}
