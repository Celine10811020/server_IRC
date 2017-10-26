/*
** client.c for client in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Thu May 25 19:55:11 2017 Valentin Nasraty
** Last update Sun Jun 11 18:53:45 2017 Valentin Nasraty
*/

#include "client.h"

int			wait_for_ip_addr(t_client *clt)
{
  int			ret_val;
  bool			end;
  ssize_t		ret;
  char			buff[SIZE_BUFF + 1];

  end = false;
  while (!end)
    {
      memset(buff, 0, SIZE_BUFF + 1);
      if ((ret = read(INPUT, buff, SIZE_BUFF)) == -1)
	return (FAILURE);
      buff[ret] = '\0';
      if (pars_addr(buff, clt))
	end = true;
      else
	putstr("Usage: SERVER $host[$port]\n");
    }
  if ((ret_val = init_client(clt)) == FAILURE)
    return (84);
  else if (ret_val == BAD_ADDR)
    wait_for_ip_addr(clt);
  return (SUCCESS);
}

int			init_client(t_client *clt)
{
  struct sockaddr_in	sin;

  if ((clt->fd_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (puterror("Error: socket creation failed\n"));
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(clt->port);
  sin.sin_addr.s_addr = inet_addr(clt->ip_addr);
  if (connect(clt->fd_sock,
	      (struct sockaddr *)(&sin), sizeof(struct sockaddr)) == -1)
    {
      putstr("[\x1b[31mKO\x1b[0m]\t");
      putstr("Bad address: connection to the server failed.\n");
      return (BAD_ADDR);
    }
  else
    print_loading_connection();
  return (SUCCESS);
}

int			main()
{
  t_client		clt;

  if (wait_for_ip_addr(&clt) == FAILURE)
    return (84);
  if (transfert_data(&clt) == FAILURE)
    return (84);
  return (0);
}
