/*
** basic.c for basic in /home/nasrat_v/Dev/rendu/tek2/C/Systeme-Unix/Reseau/PSU_2016_myirc/client
** 
** Made by Valentin Nasraty
** Login   <valentin.nasraty@epitech.eu>
** 
** Started on  Thu Jun  1 14:31:34 2017 Valentin Nasraty
** Last update Sat Jun  3 12:32:32 2017 Valentin Nasraty
*/

#include "client.h"

void		print_loading_connection()
{
  int		value;
  int		percent;
  int		sec_percent;

  percent = 1;
  putstr("\n\x1b[32m[0]\t");
  while (percent++ < 1000)
    {
      value = 0;
      sec_percent = 0;
      printf("\r[\x1b[32m%d\x1b[0m]\t[", (percent / 10));
      while (sec_percent++ < (percent / 60))
	{
	  if (sec_percent == (percent / 60))
	    printf("\x1b[36m%c\x1b[0m", LOAD_CHAR);
	  else
	    printf("\x1b[31m%c\x1b[0m", LOAD_CHAR);
	}
      while (value++ <= (16 - sec_percent))
	printf(" ");
      write(OUTPUT, "]", 1);
      fflush (stdout);
      usleep(4000);
      }
  putstr("]    \x1b[0mConnection established !\n");
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
