/*
** commande.c for commande.c in /home/brokolski/rendu/tek2/PSU_reseaux/PSU_2016_myirc
** 
** Made by felten
** Login   <felten_n@epitech.net>
** 
** Started on  Fri May 26 19:26:40 2017 felten
** Last update Sun Jun 11 20:50:17 2017 Valentin Nasraty
*/

#include "server.h"

char		**init_command_list()
{
  char		**command_list;

  if ((command_list = malloc(sizeof(char *) * SIZE_CMD_TAB)) == NULL)
    return (NULL);
  command_list[0] = strdup("NICK");
  command_list[1] = strdup("LIST");
  command_list[2] = strdup("JOIN");
  command_list[3] = strdup("PART");
  command_list[4] = strdup("USERS");
  command_list[5] = strdup("NAMES");
  command_list[6] = strdup("MSG");
  command_list[7] = strdup("ACCEPT_FILE");
  command_list[8] = strdup("QUIT");
  command_list[9] = strdup("PRIVMSG");
  command_list[10] = NULL;
  return (command_list);
}

int		which_func(char *msg, char **command_list)
{
  int		n;

  n = 0;
  while (command_list[n] &&
	 strncmp(command_list[n], msg, strlen(command_list[n])) != 0)
    n += 1;
  return (n);
}

void		accept_file(t_command *cmd)
{
  dprintf(cmd->client->fd_sock, "command accept_file executed.\n");
}

void		set_function_pointer(t_command *cmd)
{
  cmd->func_ptr[0] = &nick;
  cmd->func_ptr[1] = &list;
  cmd->func_ptr[2] = &join;
  cmd->func_ptr[3] = &part;
  cmd->func_ptr[4] = &users;
  cmd->func_ptr[5] = &names;
  cmd->func_ptr[6] = &message;
  cmd->func_ptr[7] = &accept_file;
  cmd->func_ptr[8] = &quit;
  cmd->func_ptr[9] = &private_message;
}

int		commander(t_server *srv, t_channel *ch, t_client *client, char *msg)
{
  int		n;
  t_command	cmd;
  static int	init = 0;

  cmd.cmd_tab = str_to_wordtab(msg, ' ');
  cmd.channel = ch;
  cmd.client = client;
  n = which_func(cmd.cmd_tab[0], srv->cmd_list);
  if (init == 0)
    set_function_pointer(&cmd);
  if (n < NB_CMD)
    (cmd.func_ptr[n])(&cmd);
  else
    {
      free(cmd.cmd_tab);
      return (1);
    }
  if (strncmp("QUIT", msg, 4) == 0)
    return (DECONNECTED);
  free(cmd.cmd_tab);
  return (0);
}
