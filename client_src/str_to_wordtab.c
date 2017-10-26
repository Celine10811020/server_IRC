/*
** str_to_wordtab.c for str_to_wordtab in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/client
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Thu Jun  1 17:58:58 2017 Valentin Nasraty
** Last update Thu Jun  1 18:01:23 2017 Valentin Nasraty
*/

#include "client.h"

int	count_tab(char **tab)
{
  int	n;

  n = -1;
  while (tab[++n]);
  return (n);
}

int	nb_mot(char *str, char sep)
{
  int	i;
  int	nb;

  i = 0;
  nb = 1;
  while (str[i] != 0)
    {
      if (str[i] == sep)
	nb = nb + 1;
      i = i + 1;
    }
  return (nb);
}

char	**str_to_wordtab(char *str, char sep)
{
  char	**tab;
  int	i;
  int	j;

  if ((tab = malloc((nb_mot(str, sep) + 1) * sizeof(char*))) == NULL)
    return (NULL);
  tab[nb_mot(str, sep)] = NULL;
  i = 0;
  j = 1;
  tab[0] = str;
  while (str[i])
    {
      if (str[i] == sep)
	{
	  str[i] = 0;
	  i += 1;
	  tab[j] = &str[i];
	  j += 1;
	}
      i += 1;
    }
  return (tab);
}
