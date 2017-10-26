/*
** str_to_wordtab.c for str_to_wordtab in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Mon Jun  5 15:12:00 2017 Valentin Nasraty
** Last update Sun Jun 11 16:42:40 2017 felten
*/

#include "server.h"

int	count_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab[++i]);
  return (i);
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

int	nb_mot_bis(char *str, char sep1, char sep2)
{
  int	i;
  int	nb;

  i = 0;
  nb = 1;
  while (str[i] != 0)
    {
      if (str[i] && str[i] == sep1 &&
	  str[i + 1] && str[i + 1] == sep2)
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
  while (str[i] != 0)
    {
      if (str[i] == sep)
	{
	  str[i] = 0;
	  i = i + 1;
	  tab[j] = &str[i];
	  j = j + 1;
	}
      i = i + 1;
    }
  return (epur_new_line(tab));
}

char	**str_to_wordtab_bis(char *str, char sep1, char sep2)
{
  char	**tab;
  int	i;
  int	j;

  if ((tab = malloc((nb_mot_bis(str, sep1, sep2) + 1)
		    * sizeof(char*))) == NULL)
    return (NULL);
  tab[nb_mot_bis(str, sep1, sep2)] = NULL;
  i = 0;
  j = 1;
  tab[0] = str;
  while (str[i] != 0)
    {
      if (str[i] && str[i] == sep1 &&
	  str[i + 1] && str[i + 1] == sep2)
	{
	  str[i] = 0;
	  i = i + 1;
	  tab[j] = &str[i + 1];
	  j = j + 1;
	}
      i = i + 1;
    }
  return (epur_new_line(tab));
}
