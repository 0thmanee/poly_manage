#ifndef POLYNOME_H
# define POLYNOME_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef	struct s_coeff
{
	int a;
	int b;
}	t_coeff;

typedef struct s_polynome
{
	int degree;
	t_coeff *coeff;
	struct s_polynome *next;
} 	t_polynome;

char	**ft_split(char const *s, char c);
void	lstadd_back(t_polynome **lst, t_polynome *new);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
