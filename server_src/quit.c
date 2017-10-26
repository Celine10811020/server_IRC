/*
** quit.c for quit in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Sun Jun 11 16:40:12 2017 Valentin Nasraty
** Last update Sun Jun 11 17:02:46 2017 Valentin Nasraty
*/

#include "server.h"

void		quit(t_command *cmd)
{
  close(cmd->client->fd_sock);
  shutdown(cmd->client->fd_sock, SHUT_RDWR);
  delete_client_allchan(cmd->channel, cmd->client);
}
