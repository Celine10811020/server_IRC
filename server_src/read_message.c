/*
** message.c for message in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Fri May 26 18:33:39 2017 Valentin Nasraty
** Last update Sun Jun 11 20:57:57 2017 Valentin Nasraty
*/

#include "server.h"

bool		is_end_msg_telnet(char *msg)
{
  int		i;
  static short	n = 0;
  static short	x = 0;

  i = -1;
  while (msg[++i])
    {
      if ((n - x) > 1)
	{
	  x = 0;
	  n = 0;
	}
      if (msg[i] == '\r')
	x = 1;
      if (msg[i] == '\n' && x == 1)
	{
	  x = 0;
	  n = 0;
	  return (true);
	}
      if (x == 1)
	n += 1;
    }
  return (false);
}

bool		is_end_msg_netcat(char *msg)
{
  int		i;

  i = -1;
  while (msg[++i])
    {
      if (msg[i] == '\n')
        return (true);
    }
  return (false);
}

char		*concat_msg(char *msg, char *new_msg)
{
  int		i;
  int		n;
  char		*str;

  i = -1;
  n = -1;
  if ((str = malloc(sizeof(char) * (strlen(msg) +
				    strlen(new_msg) + 1))) == NULL)
    return (NULL);
  while (msg[++i])
    str[i] = msg[i];
  while (new_msg[++n])
    str[i++] = new_msg[n];
  str[i] = '\0';
  return (str);
}

char		*shutdown_client(t_channel *ch, t_client *client)
{
  close(client->fd_sock);
  shutdown(client->fd_sock,  SHUT_RDWR);
  delete_client_allchan(ch, client);
  return (EOF_SIGNAL);
}

char		*receive_msg(t_client *client, t_channel *ch)
{
  ssize_t	ret;
  char		msg[BUFFER_SIZE + 1];
  char		*tmp;
  bool		end;

  end = false;
  memset(msg, 0, BUFFER_SIZE + 1);
  while (!end)
    {
      tmp = msg;
      if ((ret = read(client->fd_sock, tmp, NB_OCTET_READ)) == -1)
	{
	  puterror("Error: read client's socket failed\n");
	  return (NULL);
	}
      if (ret == 0)
	return (shutdown_client(ch, client));
      tmp += ret;
      if (is_end_msg_telnet(msg) || is_end_msg_netcat(msg))
	end = true;
    }
  return (strdup(msg));
}

