#include "polynome.h"

void display_rules(void)
{
	printf("\t\t\t\t\t\x1b[32m(*) LET:     To Enter Your Polynom\n");
	printf("\t\t\t\t\t\x1b[32m(*) SET:     To Edit Your Polynom\n");
	printf("\t\t\t\t\t\x1b[32m(*) DISPLAY: To Display Your Polynom\n");
	printf("\t\t\t\t\t\x1b[32m(*) ADD:     Add Your Polynoms\n");
	printf("\t\t\t\t\t\x1b[32m(*) SUB:     Substract Your Polynoms\n");
	printf("\t\t\t\t\t\x1b[32m(*) MUL:     Multiple Your Polynoms\n");
	printf("\t\t\t\t\t\x1b[32m(*) POW:     POW Of Your Polynom\n");
	printf("\t\t\t\t\t\x1b[32m(*) AFFECT:  Affectation Of A P To The Other\n");
	printf("\t\t\t\t\t\x1b[32m(*) DER:     Derivation Of A Polynom\n");
	printf("\t\t\t\t\t\x1b[32m(*) INT:     Integration Of A Polynom\n");
	printf("\t\t\t\t\t\x1b[32m(*) EVAL:    Evaluation Of A Polynom\n");
	printf("\t\t\t\t\t\x1b[32m(*) EXIT:    To Exit The Program\n\n");
}

char	*valid_cmd(char *cmd)
{
	if (strcmp(cmd, "LET") && strcmp(cmd, "SET") && strcmp(cmd, "DISPLAY") && strcmp(cmd, "ADD") && strcmp(cmd, "SUB") && strcmp(cmd, "MUL") && strcmp(cmd, "POW") && strcmp(cmd, "AFFECT") && strcmp(cmd, "DER") && strcmp(cmd, "INT") && strcmp(cmd, "EVAL") && strcmp(cmd, "EXIT"))
	{
		printf("\x1b[31mError: Command Not Found\n");
		return NULL;
	}
	return cmd;
}

void free_terminal(char **terminal)
{
	int i = 0;
	t_polynome *tmp = NULL;
	while (terminal[i])
	{
		free(terminal[i]);
		i++;
	}
	free(terminal);
}

void free_p1(t_polynome **p1)
{
	t_polynome *tmp = NULL;
	while (*p1)
	{
		tmp = *p1;
		*p1 = (*p1)->next;
		free(tmp);
	}
}

void free_p2(t_polynome **p2)
{
	t_polynome *tmp = NULL;
	while (*p2)
	{
		tmp = *p2;
		*p2 = (*p2)->next;
		free(tmp);
	}
}

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

void display_polynome(t_polynome *p, char name)
{
	t_polynome *tmp = p;
	int started = 0;
	printf("\t\t\t\t\t\t<< %c = ", name);
	while (tmp)
	{
		if (tmp->coeff > 0 && started)
			printf("+");
		if (tmp->coeff > 0 && !started)
			started = 1;
		printf("%d", tmp->coeff);
		if (tmp->degree > 0)
			printf("X");
		if (tmp->degree > 1)
			printf("^%d", tmp->degree);
		tmp = tmp->next;
	}
	printf(" >>\n\n\n");
}

t_polynome *add_polynomes(t_polynome *p1, t_polynome *p)
{
	t_polynome *res = NULL;
	t_polynome *tmp = p1;
	t_polynome *tmp2 = p;
	t_polynome *node = NULL;
	while (tmp && tmp2)
	{
		node = malloc(sizeof(t_polynome));
		if (tmp->degree == tmp2->degree)
		{
			node->degree = tmp->degree;
			node->coeff = tmp->coeff + tmp2->coeff;
			lstadd_back(&res, node);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
		else if (tmp->degree > tmp2->degree)
		{
			node->degree = tmp->degree;
			node->coeff = tmp->coeff;
			lstadd_back(&res, node);
			tmp = tmp->next;
		}
		else
		{
			node->degree = tmp2->degree;
			node->coeff = tmp2->coeff;
			lstadd_back(&res, node);
			tmp2 = tmp2->next;
		}
	}
	while (tmp)
	{
		node = malloc(sizeof(t_polynome));
		node->degree = tmp->degree;
		node->coeff = tmp->coeff;
		lstadd_back(&res, node);
		tmp = tmp->next;
	}
	while (tmp2)
	{
		node = malloc(sizeof(t_polynome));
		node->degree = tmp2->degree;
		node->coeff = tmp2->coeff;
		lstadd_back(&res, node);
		tmp2 = tmp2->next;
	}
	return res;
}

t_polynome *sub_polynoms(t_polynome *p1, t_polynome *p)
{
	t_polynome *res = NULL;
	t_polynome *tmp = p1;
	t_polynome *tmp2 = p;
	t_polynome *node = NULL;
	while (tmp && tmp2)
	{
		node = malloc(sizeof(t_polynome));
		if (tmp->degree == tmp2->degree)
		{
			node->degree = tmp->degree;
			node->coeff = tmp->coeff - tmp2->coeff;
			lstadd_back(&res, node);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
		else if (tmp->degree > tmp2->degree)
		{
			node->degree = tmp->degree;
			node->coeff = tmp->coeff;
			lstadd_back(&res, node);
			tmp = tmp->next;
		}
		else
		{
			node->degree = tmp2->degree;
			node->coeff = tmp2->coeff;
			lstadd_back(&res, node);
			tmp2 = tmp2->next;
		}
	}
	while (tmp)
	{
		node = malloc(sizeof(t_polynome));
		node->degree = tmp->degree;
		node->coeff = tmp->coeff;
		lstadd_back(&res, node);
		tmp = tmp->next;
	}
	while (tmp2)
	{
		node = malloc(sizeof(t_polynome));
		node->degree = tmp2->degree;
		node->coeff = tmp2->coeff;
		lstadd_back(&res, node);
		tmp2 = tmp2->next;
	}
	return res;
}

t_polynome *mul_polynoms(t_polynome *p1, t_polynome *p)
{
	t_polynome *res = NULL;
	t_polynome *tmp = p1;
	t_polynome *tmp2 = p;
	t_polynome *node = NULL;
	while (tmp)
	{
		tmp2 = p;
		while (tmp2)
		{
			node = malloc(sizeof(t_polynome));
			node->degree = tmp->degree + tmp2->degree;
			node->coeff = tmp->coeff * tmp2->coeff;
			lstadd_back(&res, node);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return res;
}

t_polynome *optmz_polynom(t_polynome *p)
{
	t_polynome *res = NULL; // New list to store optimized polynomial
	t_polynome *tmp = p;
	t_polynome *tmp2 = p;
	t_polynome *node = NULL;
	int degs[1000] = {0};
	while (tmp)
	{
		while (degs[tmp->degree] == 1)
			tmp = tmp->next;
		node = malloc(sizeof(t_polynome));
		node->coeff = tmp->coeff;
		node->degree = tmp->degree;
		node->coeff = tmp->coeff;
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp->degree == tmp2->degree && degs[tmp2->degree] == 0)
				node->coeff += tmp2->coeff;
			tmp2 = tmp2->next;
		}
		degs[tmp->degree] = 1;
		lstadd_back(&res, node);
		tmp = tmp->next;
	}
	return res;
}

int main()
{
	char	**terminal = NULL;
	char	**polys = NULL;
	t_polynome *p1 = NULL;
	t_polynome *p2 = NULL;

	char input[200];
	while (1)
	{
		printf("\t\t\t\x1b[32mHi There, Welcome To Your Small App, We Will Help You To Handle Your Polynom\n\n\t\t\t\t\t\tEnter <Help> To See The Rules\n\n");
		printf(">> ");
		printf("\x1b[0m");	
		scanf(" %[^\n]", input);
		terminal = ft_split(input, ' ');
		if (!strcmp(terminal[0], "Help"))
		{
			system("clear");
			display_rules();
			free_terminal(terminal);
		}
		
		else if (!valid_cmd(terminal[0]) || !terminal[1] || !strcmp(terminal[0], "EXIT"))
		{
			free_terminal(terminal);
			system("clear");
		}
		
		else if (!strcmp(terminal[0], "LET"))
		{
			if (terminal[1][0] == 'P')
			{
				if (p1)
				{
					printf("\x1b[31mError: Polynom Already Exists\n");
					free_terminal(terminal);
					system("clear");
				}
				else p1 = optmz_polynom(create_polynome(ft_substr(terminal[1], 2, strlen(terminal[1])), p1));
			}
			else if (terminal[1][0] == 'Q')
			{
				if (p2)
				{
					printf("\x1b[31mError: Polynom Already Exists\n");
					free_terminal(terminal);
					system("clear");
				}
				else p2 = optmz_polynom(create_polynome(ft_substr(terminal[1], 2, strlen(terminal[1])), p2));
			}
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}
		
		else if (!strcmp(terminal[0], "SET"))
		{
			if ((terminal[1][0] == 'P' && !p1) || (terminal[1][0] == 'Q' && !p2))
			{
				printf("\x1b[31mError: You Must Enter A Polynom First\n");
				free_terminal(terminal);
				system("clear");
			}
			else if (terminal[1][0] == 'P')
				p1 = optmz_polynom(create_polynome(ft_substr(terminal[1], 2, strlen(terminal[1])), p1));
			else if (terminal[1][0] == 'Q')
				p2 = optmz_polynom(create_polynome(ft_substr(terminal[1], 2, strlen(terminal[1])), p2));
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}
		
		else if (!strcmp(terminal[0], "DISPLAY"))
		{
			if ((terminal[1][0] == 'P' && !p1) || (terminal[1][0] == 'Q' && !p2))
			{
				free_terminal(terminal);
				system("clear");
			}
			else
			if (terminal[1][0] == 'P')
				display_polynome(p1, 'P');
			else if (terminal[1][0] == 'Q')
				display_polynome(p2, 'Q');
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}
		
		else if (!strcmp(terminal[0], "ADD"))
		{
			polys = ft_split(terminal[1], ',');
			if (strcmp(polys[0], "P") && strcmp(polys[1], "Q") && strcmp(polys[0], "Q") && strcmp(polys[1], "P"))
			{
				free_terminal(terminal);
				system("clear");
			}
			else if (!strcmp(polys[0], "P") && !strcmp(polys[1], "Q"))
			{
				if (!p1 || !p2)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = add_polynomes(p1, p2);
					display_polynome(res, 'R');
				}
			}
			else if (!strcmp(polys[0], "Q") && !strcmp(polys[1], "P"))
			{
				if (!p1 || !p2)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = add_polynomes(p1, p2);
					display_polynome(res, 'R');
				}
			}
			else if (!strcmp(polys[0], "P") && !strcmp(polys[1], "P"))
			{
				if (!p1)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = add_polynomes(p1, p1);
					display_polynome(res, 'R');
				}
			}
			else if (!strcmp(polys[0], "Q") && !strcmp(polys[1], "Q"))
			{
				if (!p2)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = add_polynomes(p2, p2);
					display_polynome(res, 'R');
				}
			}
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}

		else if (!strcmp(terminal[0], "SUB"))
		{
			polys = ft_split(terminal[1], ',');
			if (strcmp(polys[0], "P") && strcmp(polys[1], "Q") && strcmp(polys[0], "Q") && strcmp(polys[1], "P"))
			{
				free_terminal(terminal);
				system("clear");
			}
			else if (!strcmp(polys[0], "P") && !strcmp(polys[1], "Q"))
			{
				if (!p1 || !p2)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = sub_polynoms(p1, p2);
					display_polynome(res, 'R');
				}
			}
			else if (!strcmp(polys[0], "Q") && !strcmp(polys[1], "P"))
			{
				if (!p1 || !p2)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = sub_polynoms(p1, p2);
					display_polynome(res, 'R');
				}
			}
			else if (!strcmp(polys[0], "P") && !strcmp(polys[1], "P"))
			{
				if (!p1)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = sub_polynoms(p1, p1);
					display_polynome(res, 'R');
				}
			}
			else if (!strcmp(polys[0], "Q") && !strcmp(polys[1], "Q"))
			{
				if (!p2)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = sub_polynoms(p2, p2);
					display_polynome(res, 'R');
				}
			}
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}

		else if (!strcmp(terminal[0], "MUL"))
		{
			polys = ft_split(terminal[1], ',');
			if (strcmp(polys[0], "P") && strcmp(polys[1], "Q") && strcmp(polys[0], "Q") && strcmp(polys[1], "P"))
			{
				free_terminal(terminal);
				system("clear");
			}
			else if (!strcmp(polys[0], "P") && !strcmp(polys[1], "Q"))
			{
				if (!p1 || !p2)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = optmz_polynom(mul_polynoms(p1, p2));
					display_polynome(res, 'R');
				}
			}
			else if (!strcmp(polys[0], "Q") && !strcmp(polys[1], "P"))
			{
				if (!p1 || !p2)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = optmz_polynom(mul_polynoms(p1, p2));
					display_polynome(res, 'R');
				}
			}
			else if (!strcmp(polys[0], "P") && !strcmp(polys[1], "P"))
			{
				if (!p1)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = optmz_polynom(mul_polynoms(p1, p1));
					display_polynome(res, 'R');
				}
			}
			else if (!strcmp(polys[0], "Q") && !strcmp(polys[1], "Q"))
			{
				if (!p2)
				{
					printf("\x1b[31mError: You Must Enter Two Polynoms First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					t_polynome *res = optmz_polynom(mul_polynoms(p2, p2));
					display_polynome(res, 'R');
				}
			}
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}

		else if (!strcmp(terminal[0], "POW"))
		{
			if (terminal[1][0] == 'P')
			{
				if (!p1)
				{
					printf("\x1b[31mError: You Must Enter A Polynom First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					int pow = atoi(ft_substr(terminal[1], 2, strlen(terminal[1])));
					t_polynome *res = p1;
					while (pow > 1)
					{
						res = mul_polynoms(res, p1);
						pow--;
					}
					display_polynome(res, 'R');
				}
			}
			else if (terminal[1][0] == 'Q')
			{
				if (!p2)
				{
					printf("\x1b[31mError: You Must Enter A Polynom First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
				{
					int pow = atoi(ft_substr(terminal[1], 2, strlen(terminal[1])));
					t_polynome *res = p2;
					while (pow > 1)
					{
						res = mul_polynoms(res, p2);
						pow--;
					}
					display_polynome(res, 'R');
				}
			}
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}
	}
		return 0;
}