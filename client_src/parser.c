/*
** parser.c for parser in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/client
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Thu Jun  1 18:19:51 2017 Valentin Nasraty
** Last update Thu Jun  1 21:05:32 2017 Valentin Nasraty
*/

#include "client.h"

int			find_char(char *buff, char c)
{
  int			i;
  int			n;

  i = -1;
  n = 0;
  while (buff[++i])
    {
      if (buff[i] == c)
	return (n);
      n += 1;
    }
  return (-1);
}

bool			pars_addr(char *buff, t_client *clt)
{
  int			i;
  int			size_a;
  int			size_b;
  char			**tab;

  i = -1;
  if (((tab = str_to_wordtab(buff, ' ')) == NULL) ||
      (strncmp(tab[0], "SERVER\n", 7) == 0) ||
      (count_tab(tab) != 2))
    return (false);
  if (((size_a = (find_char(tab[1], '['))) == -1) ||
      ((size_b = (find_char(tab[1], ']'))) == -1) ||
      size_a >= size_b)
    return (false);
  if (tab[1][size_a + 1] != ':')
    return (false);
  if ((clt->ip_addr = malloc(sizeof(char) * (size_a + 1))) == NULL)
    return (false);
  while (++i < size_a)
    clt->ip_addr[i] = tab[1][i];
  clt->ip_addr[i] = '\0';
  clt->ip_addr[size_b] = '\0';
  clt->port = atoi(tab[1] + size_a + 2);
  return (true);
}
