/*
** message.c for message in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:39:28 2017 Valentin Nasraty
** Last update Sun Jun 11 18:21:01 2017 Valentin Nasraty
*/

#include "server.h"

void		message(t_command *cmd)
{
  t_client	*tmp;

  tmp = cmd->client;
  if (count_tab(cmd->cmd_tab) == 3)
    {
      while (tmp->prev != NULL)
	tmp = tmp->prev;
      while (tmp != NULL && strcmp(tmp->nickname, cmd->cmd_tab[1]) != 0)
	tmp = tmp->next;
      putclient(cmd->cmd_tab[2], tmp->fd_sock);
      putclient("\n", tmp->fd_sock);
    }
  else if (count_tab(cmd->cmd_tab) == 4)
    {
      while (tmp->prev != NULL)
	tmp = tmp->prev;
      while (tmp != NULL && strcmp(tmp->nickname, cmd->cmd_tab[2]) != 0)
	tmp = tmp->next;
      putclient("New file inc, do you want to accept it ?", tmp->fd_sock);
      putclient("\n", tmp->fd_sock);
    }
  else
    putclient("Usage: /MSG $nickname $message\r\n", tmp->fd_sock);
}
