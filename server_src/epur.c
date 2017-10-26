/*
** epur.c for epur in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/server_src
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Mon Jun  5 17:38:01 2017 Valentin Nasraty
** Last update Sun Jun 11 18:13:11 2017 Valentin Nasraty
*/

#include "server.h"

char		**epur_new_line(char **tab)
{
  int		i;
  int		n;

  i = -1;
  while (tab[++i])
    {
      n = -1;
      while (tab[i][++n])
	{
	  if (tab[i][n] == '\n' && tab[i][n + 1] == '\0')
	    tab[i][n] = '\0';
	}
    }
  return (tab);
}
