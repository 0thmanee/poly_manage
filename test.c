#include "polynome.h"

t_polynome* create_polynome(char* str, t_polynome* p)
{
	int i = 0;
	int j = 0;
	int len = strlen(str);
	int degree = 0;
	double coeff = 0;
	int sign = 1;

	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			coeff = coeff * 10 + (str[i] - '0');
			i++;
		}
		if (!coeff)
			coeff = 1;
		t_polynome* node = malloc(sizeof(t_polynome));
		if (str[i] == 'X')
		{
			node->coeff = coeff * sign;
			if (str[i + 1] == '^')
			{
				i += 2;
				while (str[i] >= '0' && str[i] <= '9')
				{
					degree = degree * 10 + (str[i] - '0');
					i++;
				}
				node->degree = degree;
			}
			else
			{
				node->degree = 1;
				i++;
			}
		}
		else
		{
			node->coeff = coeff * sign;
			node->degree = 0;
		}
		lstadd_back(&p, node);
		degree = 0;
		coeff = 0;
		sign = 1;
		i++;
	}

	return p;
}

int main()
{
	char	**terminal = NULL;
	t_polynome *p1 = NULL;
	terminal = ft_split("LET P=5X^2+4X^1+X+45", ' ');
	p1 = create_polynome(ft_substr(terminal[1], 2, strlen(terminal[1])), p1);
	while (p1)
	{
		printf("coeff: %d\n", p1->coeff);
		printf("degree: %d\n", p1->degree);
		p1 = p1->next;
	}
	
	return 0;
}