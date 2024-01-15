#include "polynome.h"

// cette fonction permet de compter le nombre de mots dans une chaine de caractères
// La Complexité de cette fonction est O(n)
static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			if (i == 0 || s[i - 1] == c)
				count++;
			i++;
		}
	}
	return (count);
}

// cette fonction permet de calculer la longueur d'un mot dans une chaine de caractères
// La Complexité de cette fonction est O(n)
static size_t	calc_len(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
		count++;
	}
	return (count);
}

// cette fonction permet de remplir une sous-chaine de caractères
// La Complexité de cette fonction est O(n)
static char	*fill_subs(char const **s, char c)
{
	size_t	i;
	char	*subs;
	size_t	len;

	while (**s == c && **s)
		(*s)++;
	len = calc_len(*s, c);
	subs = (char *) malloc (sizeof (char) * (len + 1));
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = **s;
		i++;
		(*s)++;
	}
	subs[i] = '\0';
	return (subs);
}

// cette fonction permet de séparer une chaine de caractères en plusieurs sous-chaines
// La Complexité de cette fonction est O(n)
char	**ft_split(char const *s, char c)
{
	size_t	nbr_words;
	char	**strings;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	nbr_words = count_words(s, c);
	strings = (char **) malloc (sizeof(char *) * (nbr_words + 1));
	if (!strings)
		return (NULL);
	while (i < nbr_words)
	{
		strings[i] = fill_subs(&s, c);
		if (!strings[i])
		{
			while (i > 0)
				free(strings[--i]);
			free (strings);
			return (NULL);
		}
		i++;
	}
	strings[i] = NULL;
	return (strings);
}

// cette fonction permet d'ajouter un élément à la fin d'une liste chainée
// La Complexité de cette fonction est O(n)
void	lstadd_back(t_polynome **lst, t_polynome *new)
{
	t_polynome	*curr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = new;
}

// cette fonction permet de SUBSTR une chaine de caractères
// La Complexité de cette fonction est O(n)
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*subs;

	if (!s)
		return (NULL);
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	subs = (char *)malloc(len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		subs[i] = s[start];
		start++;
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

// cette fonction affiche les règles du programme, elle est appelée lors de l'execution de la commande "Help"
// La Complexité de cette fonction est O(1)
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

// cette fonction permet de vérifier si la commande entrée par l'utilisateur est valide ou non
// La Complexité de cette fonction est O(1)
char	*valid_cmd(char *cmd)
{
	if (strcmp(cmd, "LET") && strcmp(cmd, "SET") && strcmp(cmd, "DISPLAY") && strcmp(cmd, "ADD") && strcmp(cmd, "SUB") && strcmp(cmd, "MUL") && strcmp(cmd, "POW") && strcmp(cmd, "AFFECT") && strcmp(cmd, "DER") && strcmp(cmd, "INT") && strcmp(cmd, "EVAL") && strcmp(cmd, "EXIT") && strcmp(cmd, "Help"))
	{
		printf("\x1b[31mError: Command Not Found\n");
		return NULL;
	}
	return cmd;
}

// cette fonction libere la mémoire allouée pour la fonction ft_split
// La Complexité de cette fonction est O(n)
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

// cette fonction permet de libérer la mémoire allouée pour la liste chainée p1
// La Complexité de cette fonction est O(n)
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

// cette fonction permet de libérer la mémoire allouée pour la liste chainée p2
// La Complexité de cette fonction est O(n)
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


int new_degree(int *degs, int degree)
{
	int i = 0;
	while (i < 100)
	{
		if (degs[i] == degree)
			return 0;
		i++;
	}
	return 1;
}

// cette fonction permet d'optimiser le polynome entré par l'utilisateur
// La Complexité de cette fonction est O(n)
t_polynome *optmz_polynom(t_polynome *p)
{
	// t_polynome *res = NULL;
	// t_polynome *tmp = p;
	// t_polynome *tmp2 = NULL;
	// t_polynome *node = NULL;
	// int degs[100] = {-1};
	// int i = 0;
	// while (tmp)
	// {
	// 	tmp2 = p->next;
	// 	if (new_degree(degs, tmp->degree))
	// 	{
	// 		degs[i] = tmp->degree;
	// 		i++;
	// 		node = malloc(sizeof(t_polynome));
	// 		if (!node)
	// 			return (NULL);
	// 		node->coeff = malloc(sizeof(t_coeff));
	// 		if (!node->coeff)
	// 			return (NULL);
	// 		node->degree = tmp->degree;
	// 		node->coeff->a = tmp->coeff->a;
	// 		node->coeff->b = tmp->coeff->b;
	// 		while (tmp2)
	// 		{
	// 			if (tmp->degree == tmp2->degree)
	// 			{
	// 				node->coeff->a = (node->coeff->a * tmp2->coeff->b) + (tmp2->coeff->a * node->coeff->b);
	// 				node->coeff->b = node->coeff->b * tmp2->coeff->b;
	// 				lstadd_back(&res, node);
	// 			}
	// 			tmp2 = tmp2->next;
	// 		}
	// 	}
	// 	tmp = tmp->next;
	// }
	// return res;
	return p;
}

// cette fonction permet de créer une liste chainée qui contient les coefficients et les degrés du polynome entré par l'utilisateur
// La Complexité de cette fonction est O(n)
t_polynome* create_polynome(char* str, t_polynome* p)
{
	int i = 0;
	int j = 0;
	int len = strlen(str);
	int degree = 0;
	int coeff_a = 0;
	int coeff_b = 0;
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
		while (str[i] && str[i] >= '0' && str[i] <= '9')
		{
			coeff_a = coeff_a * 10 + (str[i] - '0');
			i++;
		}
		if (!coeff_a)
			coeff_a = 1;
		if (str[i] == '/')
			i++;
		while (str[i] && str[i] >= '0' && str[i] <= '9')
		{
			coeff_b = coeff_b * 10 + (str[i] - '0');
			i++;
		}
		if (!coeff_b)
			coeff_b = 1;
		t_polynome* node = malloc(sizeof(t_polynome));
		if (!node)
			return (NULL);
		node->coeff = malloc(sizeof(t_coeff));
		if (!node->coeff)
			return (NULL);
		node->coeff->a = coeff_a * sign;
		node->coeff->b = coeff_b;
		if (str[i] == 'X')
		{
			if (str[i + 1] == '^')
			{
				i += 2;
				while (str[i] && str[i] >= '0' && str[i] <= '9')
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
			node->degree = 0;
		node->next = NULL;
		if (p == NULL)
			p = node;
		else
		{
			t_polynome* tmp = p;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = node;
		}
		degree = 0;
		coeff_a = 0;
		coeff_b = 0;
		sign = 1;
		i++;
	}
	return optmz_polynom(p);
}

// cette fonction permet d'afficher le polynome entré par l'utilisateur
// La Complexité de cette fonction est O(n)
void display_polynome(t_polynome *p, char name)
{
	t_polynome *tmp = p;
	int started = 0;
	int frac = 0;
	printf("\t\t\t\t\t\t<< %c = ", name);
	while (tmp)
	{
		frac = !(tmp->coeff->a % tmp->coeff->b) ? (tmp->coeff->a / tmp->coeff->b) : 0;
		if (tmp->coeff->a >= 0 && started)
			printf("+");
		if (tmp->coeff->a >= 0 && !started)
			started = 1;
		if (frac)
			printf("%d", frac);
		else
		{
			printf("%d", tmp->coeff->a);
			if (tmp->coeff->b > 1)
				printf("/%d", tmp->coeff->b);
		}
		if (tmp->degree > 0)
			printf("X");
		if (tmp->degree > 1)
			printf("^%d", tmp->degree);
		tmp = tmp->next;
		frac = 0;
	}
	printf(" >>\n\n\n");
}

// cette fonction permet d'additionner deux polynomes
// La Complexité de cette fonction est O(n)
t_polynome *add_polynomes(t_polynome *p1, t_polynome *p)
{
	t_polynome *res = NULL;
	t_polynome *tmp = p1;
	t_polynome *tmp2 = p;
	t_polynome *node = NULL;
	while (tmp && tmp2)
	{
		node = malloc(sizeof(t_polynome));
		if (!node)
			return (NULL);
		node->coeff = malloc(sizeof(t_coeff));
		if (!node->coeff)
			return (NULL);
		if (tmp->degree == tmp2->degree)
		{
			node->degree = tmp->degree;
			node->coeff->a = (tmp->coeff->a * tmp2->coeff->b) + (tmp2->coeff->a * tmp->coeff->b);
			node->coeff->b = tmp->coeff->b * tmp2->coeff->b;
			lstadd_back(&res, node);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
		else if (tmp->degree > tmp2->degree)
		{
			node->degree = tmp->degree;
			node->coeff->a = tmp->coeff->a;
			node->coeff->b = tmp->coeff->b;
			lstadd_back(&res, node);
			tmp = tmp->next;
		}
		else
		{
			node->degree = tmp2->degree;
			node->coeff->a = tmp2->coeff->a;
			node->coeff->b = tmp2->coeff->b;
			lstadd_back(&res, node);
			tmp2 = tmp2->next;
		}
	}
	while (tmp)
	{
		node = malloc(sizeof(t_polynome));
		node->degree = tmp->degree;
		node->coeff->a = tmp->coeff->a;
		node->coeff->b = tmp->coeff->b;
		lstadd_back(&res, node);
		tmp = tmp->next;
	}
	while (tmp2)
	{
		node = malloc(sizeof(t_polynome));
		node->degree = tmp2->degree;
		node->coeff->a = tmp2->coeff->a;
		node->coeff->b = tmp2->coeff->b;
		lstadd_back(&res, node);
		tmp2 = tmp2->next;
	}
	return optmz_polynom(res);
}

// cette fonction permet de soustraire deux polynomes
// La Complexité de cette fonction est O(n)
t_polynome *sub_polynoms(t_polynome *p1, t_polynome *p)
{
	t_polynome *res = NULL;
	t_polynome *tmp = p1;
	t_polynome *tmp2 = p;
	t_polynome *node = NULL;
	while (tmp && tmp2)
	{
		node = malloc(sizeof(t_polynome));
		if (!node)
			return (NULL);
		node->coeff = malloc(sizeof(t_coeff));
		if (!node->coeff)
			return (NULL);
		if (tmp->degree == tmp2->degree)
		{
			node->degree = tmp->degree;
			node->coeff->a = (tmp->coeff->a * tmp2->coeff->b) - (tmp2->coeff->a * tmp->coeff->b);
			node->coeff->b = tmp->coeff->b * tmp2->coeff->b;
			lstadd_back(&res, node);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
		else if (tmp->degree > tmp2->degree)
		{
			node->degree = tmp->degree;
			node->coeff->a = tmp->coeff->a;
			node->coeff->b = tmp->coeff->b;
			lstadd_back(&res, node);
			tmp = tmp->next;
		}
		else
		{
			node->degree = tmp2->degree;
			node->coeff->a = tmp2->coeff->a;
			node->coeff->b = tmp2->coeff->b;
			lstadd_back(&res, node);
			tmp2 = tmp2->next;
		}
	}
	while (tmp)
	{
		node = malloc(sizeof(t_polynome));
		node->degree = tmp->degree;
		node->coeff->a = tmp->coeff->a;
		node->coeff->b = tmp->coeff->b;
		lstadd_back(&res, node);
		tmp = tmp->next;
	}
	while (tmp2)
	{
		node = malloc(sizeof(t_polynome));
		node->degree = tmp2->degree;
		node->coeff->a = tmp2->coeff->a;
		node->coeff->b = tmp2->coeff->b;
		lstadd_back(&res, node);
		tmp2 = tmp2->next;
	}
	return optmz_polynom(res);
}

// cette fonction permet de multiplier deux polynomes
// La Complexité de cette fonction est O(n)
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
			if (!node)
			return (NULL);
			node->coeff = malloc(sizeof(t_coeff));
			if (!node->coeff)
				return (NULL);
			node->degree = tmp->degree + tmp2->degree;
			node->coeff->a = tmp->coeff->a * tmp2->coeff->a;
			node->coeff->b = tmp->coeff->b * tmp2->coeff->b;
			lstadd_back(&res, node);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return optmz_polynom(res);
}

t_polynome *der_polynom(t_polynome *p)
{
	t_polynome *res = NULL;
	t_polynome *tmp = p;
	t_polynome *node = NULL;
	while (tmp)
	{
		node = malloc(sizeof(t_polynome));
		if (!node)
			return (NULL);
		node->coeff = malloc(sizeof(t_coeff));
		if (!node->coeff)
			return (NULL);
		node->degree = tmp->degree - 1;
		node->coeff->a = tmp->coeff->a * tmp->degree;
		node->coeff->b = tmp->coeff->b;
		lstadd_back(&res, node);
		tmp = tmp->next;
	}
	return optmz_polynom(res);
}

t_polynome *int_polynom(t_polynome *p)
{
	t_polynome *res = NULL;
	t_polynome *tmp = p;
	t_polynome *node = NULL;
	while (tmp)
	{
		node = malloc(sizeof(t_polynome));
		if (!node)
			return (NULL);
		node->coeff = malloc(sizeof(t_coeff));
		if (!node->coeff)
			return (NULL);
		node->degree = tmp->degree + 1;
		node->coeff->a = tmp->coeff->a;
		node->coeff->b = tmp->coeff->b * (tmp->degree + 1);
		lstadd_back(&res, node);
		tmp = tmp->next;
	}
	return optmz_polynom(res);
}

// La fonction main est la fonction principale du programme
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
				else p1 = create_polynome(ft_substr(terminal[1], 2, strlen(terminal[1])), p1);
			}
			else if (terminal[1][0] == 'Q')
			{
				if (p2)
				{
					printf("\x1b[31mError: Polynom Already Exists\n");
					free_terminal(terminal);
					system("clear");
				}
				else p2 = create_polynome(ft_substr(terminal[1], 2, strlen(terminal[1])), p2);
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
			{
				free_p1(&p1);
				p1 = create_polynome(ft_substr(terminal[1], 2, strlen(terminal[1])), p1);
			}
			else if (terminal[1][0] == 'Q')
			{
				free_p2(&p2);
				p2 = create_polynome(ft_substr(terminal[1], 2, strlen(terminal[1])), p2);
			}
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
					t_polynome *res = (mul_polynoms(p1, p2));
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
					t_polynome *res = (mul_polynoms(p1, p2));
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
					t_polynome *res = (mul_polynoms(p1, p1));
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
					t_polynome *res = (mul_polynoms(p2, p2));
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
					display_polynome(optmz_polynom(res), 'R');
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
	
		else if (!strcmp(terminal[0], "AFFECT"))
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
					free_p2(&p2);
					p2 = p1;
					display_polynome(p2, 'Q');
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
					free_p1(&p1);
					p1 = p2;
					display_polynome(p1, 'P');
				}
			}
			else if (!strcmp(polys[0], "P") && !strcmp(polys[1], "P"))
			{
				if (!p1)
				{
					printf("\x1b[31mError: You Must Enter A Polynom First\n");
					free_terminal(terminal);
					system("clear");
				}	
				else
					display_polynome(p1, 'P');
			}
			else if (!strcmp(polys[0], "Q") && !strcmp(polys[1], "Q"))
			{
				if (!p2)
				{
					printf("\x1b[31mError: You Must Enter A Polynom First\n");
					free_terminal(terminal);
					system("clear");
				}
				else
					display_polynome(p2, 'Q');
			}
		}

		else if (!strcmp(terminal[0], "DER"))
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
					t_polynome *res = der_polynom(p1);
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
					t_polynome *res = der_polynom(p2);
					display_polynome(res, 'R');
				}
			}
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}

		else if (!strcmp(terminal[0], "INT"))
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
					t_polynome *res = int_polynom(p1);
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
					t_polynome *res = int_polynom(p2);
					display_polynome(res, 'R');
				}
			}
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}

		else if (!strcmp(terminal[0], "EVAL"))
		{
			if (terminal[1][0] == 'P' && terminal[5])
			{
				if (!p1)
				{
					printf("\x1b[31mError: You Must Enter A Polynom First\n");
					free_terminal(terminal);
					system("clear");
				}	
				else
				{
					int x = atoi(terminal[5]);
					t_polynome *tmp = p1;
					int res = 0;
					while (tmp)
					{
						res += tmp->coeff->a * pow(x, tmp->degree);
						tmp = tmp->next;
					}
					printf("\t\t\t\t\t\t<< R = %d >>\n\n\n", res);
				}
			}
			else if (terminal[1][0] == 'Q' && terminal[5])
			{
				if (!p2)
				{
					printf("\x1b[31mError: You Must Enter A Polynom First\n");
					free_terminal(terminal);
					system("clear");
				}	
				else
				{
					int x = atoi(terminal[5]);
					t_polynome *tmp = p2;
					int res = 0;
					while (tmp)
					{
						res += tmp->coeff->a * pow(x, tmp->degree);
						tmp = tmp->next;
					}
					printf("\t\t\t\t\t\t<< R = %d >>\n\n\n", res);
				}
			}
			else
			{
				free_terminal(terminal);
				system("clear");
			}
		}

		else if (!strcmp(terminal[0], "EXIT"))
		{
			free_terminal(terminal);
			system("clear");
			break;
		}

		else
		{
			free_terminal(terminal);
			system("clear");
		}
	}
	return 0;
}