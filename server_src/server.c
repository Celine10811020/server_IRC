/*
** server.c for server in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Thu May 25 19:54:03 2017 Valentin Nasraty
** Last update Sun Jun 11 18:28:02 2017 Valentin Nasraty
*/

#include "server.h"

int			loop_server(t_server *srv, t_channel *ch)
{
  t_channel		*tmp;
  struct timeval	tv;

  tv.tv_sec = TIME_SELECT;
  tv.tv_usec = U_TIME_SELECT;
  while (42)
    {
      tmp = ch;
      while (tmp != NULL)
	{
	  if (channel_manager(srv, tmp, &tv) == FAILURE)
	    return (FAILURE);
	  tmp = tmp->next;
	}
    }
  return (SUCCESS);
}

int			init_server(t_server *srv, int port)
{
  struct sockaddr_in	sin;

  if ((srv->fd_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (puterror("Error: socket creation failed\n"));
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if ((bind(srv->fd_sock, (struct sockaddr*)(&sin),
	    sizeof(struct sockaddr))) == -1)
    return (puterror("Error: bind failed\n"));
  if ((listen(srv->fd_sock, MAX_CLIENT)) == -1)
    return (puterror("Error: listen failed\n"));
  srv->fd_max = srv->fd_sock;
  return (SUCCESS);
}

int			main(int ac, char **av)
{
  t_server		srv;
  t_channel		ch;

  if (ac != 2)
    return (84);
  if (init_server(&srv, atoi(av[1])) == FAILURE)
    return (84);
  if (init_channel(&ch, true) == FAILURE)
    return (84);
  if ((srv.cmd_list = init_command_list()) == NULL)
    return (84);
  if (loop_server(&srv, &ch) == FAILURE)
    return (84);
  return (0);
}
