/*
** data.c for data in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/client
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Fri Jun  2 16:23:20 2017 Valentin Nasraty
** Last update Sun Jun 11 18:46:43 2017 Valentin Nasraty
*/

#include "client.h"

void			set_fd(int fd_sock, fd_set *readf)
{
  FD_ZERO(readf);
  FD_SET(fd_sock, readf);
  FD_SET(INPUT, readf);
}

int			read_write_data(char *buff, int fd_read, int fd_write)
{
  int			i;
  ssize_t		ret;

  i = -1;
  if ((ret = read(fd_read, buff, SIZE_BUFF)) == -1)
    return (FAILURE);
  buff[ret] = '\0';
  while (buff[++i])
    {
      if (buff[i] == '\r')
	write(fd_write, "[r]", 3);
      else if (buff[i] == '\n')
	write(fd_write, "[n]", 3);
      else
	write(fd_write, &buff[i], 1);
    }
  return (SUCCESS);
}

int			transfert_data(t_client *clt)
{
  bool			end;
  fd_set		readf;
  char			buff[SIZE_BUFF + 1];

  end = false;
  while (!end)
    {
      set_fd(clt->fd_sock, &readf);
      memset(buff, 0, SIZE_BUFF + 1);
      if (select((clt->fd_sock + 1), &readf, NULL, NULL, NULL) == -1)
	return (puterror("Error: select failed\n"));
      if (FD_ISSET(clt->fd_sock, &readf))
	{
	  if (read_write_data(buff, clt->fd_sock, OUTPUT) == FAILURE)
	    return (FAILURE);
	}
      else if (FD_ISSET(INPUT, &readf))
	{
	  if (read_write_data(buff, INPUT, clt->fd_sock) == FAILURE)
	    return (FAILURE);
	}
    }
  return (SUCCESS);
}
