/*
** basic.c for basic in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Thu May 25 23:51:48 2017 Valentin Nasraty
** Last update Sun Jun 11 16:28:54 2017 Valentin Nasraty
*/

#include "server.h"

bool		socket_is_valid(int socket)
{
  int		copy_fd;

  errno = 0;
  copy_fd = dup(socket);
  close(copy_fd);
  if (errno == EBADF)
    return (false);
  return (true);
}

void		putstr(char *str)
{
  int		i;

  i = -1;
  while (str[++i])
    write(1, &str[i], 1);
}

int		puterror(char *str)
{
  int		i;

  i = -1;
  while (str[++i])
    write(2, &str[i], 1);
  return (FAILURE);
}

void		putclient(char *str, int fd_sock)
{
  int		i;

  if (socket_is_valid(fd_sock))
    {
      i = -1;
      while (str[++i])
	write(fd_sock, &str[i], 1);
    }
}

char		*int_to_string(int nb)
{
  int		i;
  int		x;
  char		*str;

  i = 0;
  x = nb;
  while (x > 0)
    {
      x /= 10;
      i += 1;
    }
  if ((str = malloc(sizeof(char) * (i + 1))) == NULL)
    return (NULL);
  snprintf(str, (i + 1), "%d", nb);
  return (str);
}
