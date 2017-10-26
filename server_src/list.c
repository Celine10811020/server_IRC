/*
** list.c for list in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:33:40 2017 Valentin Nasraty
** Last update Sun Jun 11 16:34:04 2017 Valentin Nasraty
*/

#include "server.h"

void		list(t_command *cmd)
{
  t_channel	*tmp;

  tmp = get_accueil_channel(cmd->channel);
  while (tmp != NULL)
    {
      if ((cmd->cmd_tab[1] && strstr(tmp->name, cmd->cmd_tab[1]) != NULL) ||
	  (cmd->cmd_tab[1] == NULL))
	{
	  putclient(tmp->name, cmd->client->fd_sock);
	  putclient("\n", cmd->client->fd_sock);
	}
      tmp = tmp->next;
    }
}
