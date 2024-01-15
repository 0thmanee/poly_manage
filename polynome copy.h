#ifndef POLYNOME_H
#define POLYNOME_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//STRUCTURE DE MONOME
typedef struct monome
{
    int degre;
    fraction coeff;
    struct monome *suivant;
}monome;

//STRUCTURE DE POLYNOME
typedef struct polynome
{
    monome *tete;
}polynome;

//STRUCTURE DE OPERATIONS
typedef struct operations
{
    char op;
    struct operations *suivant;
}operations;


//LES PROTOTYPES DES FONCTIONS
void        freePolynome(monome *m);
void        supprimerCaseTableau(char *tab, int i);
void        ajouterMonome(polynome **p, monome *m);
void        afficherPolynome(monome *m);
void        enfiler(operations **o, char op);
void        enfiler(operations **o, char op);
char        defiler(operations **o);
char        *skipSpaces(char *str);
float       evaluationPolynome(polynome *p, float x);
int         isDegreeRepeated(polynome *p);
polynome    *initialisePolynome();
polynome    *letPolynome(char *expression);
polynome    *setPolynome(char *expression, polynome *p);
polynome    *sommePolynome(polynome *p1, polynome *p2);
polynome    *differencePolynome(polynome *p1, polynome *p2);
polynome    *produitPolynome(polynome *p1, polynome *p2);
polynome    *puissancePolynome(polynome *p, int n);
polynome    *affectationPolynome(polynome *p1, polynome *p2);
polynome    *deriveePolynome(polynome *p);
polynome    *integralePolynome(polynome *p);
polynome    *supprimerzeros(polynome *p);
polynome    *triePolynome(polynome *p);
polynome    *simplifierPolynome(polynome *p);
operations  *enfilerOperations(char *expression);
monome      *creerMonome(int degre, fraction coeff);

//LIBERER LA MEMOIRE DE POLYNOME
void freePolynome(monome *m)
{
    if (m != NULL)
    {
        freePolynome(m->suivant);
        free(m);
    }
} //COMPLEXITE : O(n)   (n = nombre de monome)

//FONCTION DE CREATION DE MONOME
monome *creerMonome(int degre, fraction coeff)
{
    monome *m = (monome *)malloc(sizeof(monome));
    m->degre = degre;
    m->coeff = coeff;
    m->suivant = NULL;
    return m;
} //COMPLEXITE : O(1)

//SUPPRIMER CASE DE TABLEAU
void supprimerCaseTableau(char *tab, int i)
{
    int j;
    for(j = i; j < strlen(tab); j++)
    {
        tab[j] = tab[j + 1];
    }
} //COMPLEXITE : O(n)   (n = taille de tableau)

//TRIE DE POLYNOME SELON LE DEGRE
polynome *triePolynome(polynome *p)
{
    monome *tmp = p->tete;
    monome *tmp1 = p->tete;
    monome *tmp2 = p->tete;
    while(tmp1 != NULL)
    {
        tmp2 = tmp1->suivant;
        while(tmp2 != NULL)
        {
            if(tmp1->degre < tmp2->degre)
            {
                int degre = tmp1->degre;
                tmp1->degre = tmp2->degre;
                tmp2->degre = degre;
                fraction coeff = tmp1->coeff;
                tmp1->coeff = tmp2->coeff;
                tmp2->coeff = coeff;
            }
            tmp2 = tmp2->suivant;
        }
        tmp1 = tmp1->suivant;
    }
    return p;
} //COMPLEXITE : O(n^2)  (n = nombre de monome)

//INITIALISATION DE POLYNOME
polynome *initialisePolynome()
{
    polynome *p = (polynome *)malloc(sizeof(polynome));
    p->tete = NULL;
    return p;
} //COMPLEXITE : O(1)

//AJOUT DE MONOME A POLYNOME
void ajouterMonome(polynome **p, monome *m)
{
    if((*p)->tete == NULL)
    {
        (*p)->tete = m;
    }
    else
    {
        monome *tmp = (*p)->tete;
        while(tmp->suivant != NULL)
        {
            tmp = tmp->suivant;
        }
        tmp->suivant = m;
    }
} //COMPLEXITE : O(n)   (n = nombre de monome)

//SUPPRIMER LES ESPACES
char *skipSpaces(char *str) {
    while (isspace(*str)) {
        str++;
    }
    return str;
} //COMPLEXITE : O(n)   (n = nombre de caractere)

//VERIFIER SI LE DEGRE SE REPETE
int isDegreeRepeated(polynome *p)
{
    if (p == NULL)
    {
        return 0;
    }

    monome *current = p->tete;

    while (current != NULL)
    {
        int degreeToCheck = current->degre;
        monome *temp = current->suivant;
        while (temp != NULL)
        {
            if (temp->degre == degreeToCheck)
            {
                return 1;
            }
            temp = temp->suivant;
        }
        current = current->suivant;
    }
    return 0;
} //COMPLEXITE : O(n^2) (n = nombre de monome)

//FAIRE UNE SIMPLIFICATION DE POLYNOME PAR LES MONOME DE MEME DEGRE
polynome *simplifierPolynome(polynome *p)
{
    polynome *p1 = initialisePolynome();
    monome *tmp = p->tete;
    while(tmp != NULL)
    {
        monome *tmp1 = tmp->suivant;
        while(tmp1 != NULL)
        {
            if(tmp->degre == tmp1->degre)
            {
                ajouterMonome(&p1, creerMonome(tmp->degre, sommeFraction(tmp->coeff, tmp1->coeff)));
                tmp->coeff = creerFraction(0, 1);
                tmp1->coeff = creerFraction(0, 1);
            }
            tmp1 = tmp1->suivant;
        }
        tmp = tmp->suivant;
    }
    tmp = p->tete;
    while(tmp != NULL)
    {
        if(tmp->coeff.numerateur != 0)
        {
            ajouterMonome(&p1, creerMonome(tmp->degre, tmp->coeff));
        }
        tmp = tmp->suivant;
    }  
    return p1;
} //COMPLEXITE : O(n^2) (n = nombre de monome)

//ENFILER L'OPERATION
void enfiler(operations **o, char op)
{
    operations *tmp = (operations *)malloc(sizeof(operations));
    tmp->op = op;
    tmp->suivant = NULL;
    if((*o) == NULL)
    {
        (*o) = tmp;
    }
    else
    {
        operations *tmp1 = (*o);
        while(tmp1->suivant != NULL)
        {
            tmp1 = tmp1->suivant;
        }
        tmp1->suivant = tmp;
    }
    free(tmp);
} //COMPLEXITE : O(n)   (n = nombre des operations)

//DEFILER L'OPERATION
char defiler(operations **o)
{
    if((*o) != NULL)
    {
        operations *tmp = (*o);
        char op = tmp->op;
        (*o) = (*o)->suivant;
        free(tmp);
        return op;
    }
    else
    {
        printf("Erreur : la pile est vide\n");
        exit(1);
    }
} //COMPLEXITE : O(1)

//ENFILER LES OPERATIONS
operations *enfilerOperations(char *expression)
{
    operations *o = NULL;
    if (expression[0] == '-')
    {
        enfiler(&o, '-');
    }
    else
    {
        enfiler(&o, '+');
    }
    for(int i=1;i<strlen(expression);i++)
    {
        if(expression[i] == '+' || expression[i] == '-')
        {
            enfiler(&o, expression[i]);
        }
    }
    return o;
} //COMPLEXITE : O(n)   (n = nombre de caractere )

//LET POLYNOME
polynome *letPolynome(char *expression)
{
    polynome *p = initialisePolynome();
    //ENFILER LES OPERATIONS POUR LES UTILISER PLUS TARD
    operations *operations = enfilerOperations(expression);
    int sign = 1;
    char *token = strtok(expression, "+-");

    while (token != NULL)
    {
        int degre = 0;
        fraction coeff = creerFraction(0, 1);
        //CHECKER LE SIGNE DU MONOME
        if (defiler(&operations) == '-')
        {
            sign = -1;
        }
        else
        {
            sign = 1;
        }
        //FORMAT %d/%dX^%d
        if (sscanf(token, "%d/%dX^%d", &coeff.numerateur, &coeff.denominateur, &degre) == 3)
        {
            coeff.numerateur *= sign;
            ajouterMonome(&p, creerMonome(degre, coeff));
        }
        //FORMAT %dX^%d
        else if (sscanf(token, "%dX^%d", &coeff.numerateur, &degre) == 2)
        {
            coeff.numerateur *= sign;
            ajouterMonome(&p, creerMonome(degre, coeff));
        }
        else if (sscanf(token, "%d/%dX", &coeff.numerateur, &coeff.denominateur) == 2)
        {
            coeff.numerateur *= sign;
            printf("i am here\n");
            //FORMAT %d/%dX
            if(strchr(token, 'X') != NULL)
            {
                ajouterMonome(&p, creerMonome(1, coeff));
            }
            //FORMAT %d/%d
            else
            {
                ajouterMonome(&p, creerMonome(0, coeff));
            }
        } 
        //FORMAT X^%d             
        else if (sscanf(token, "X^%d", &degre) == 1)
        {
            if (sign == 1)
            {
                ajouterMonome(&p, creerMonome(degre, creerFraction(1, 1)));
            }
            else
            {
                ajouterMonome(&p, creerMonome(degre, creerFraction(-1, 1)));
            }
        }
        //FORMAT X
        else if (strcmp(token, "X") == 0 || strcmp(token, "X\n") == 0)
        {
            if (sign == 1)
            {
                ajouterMonome(&p, creerMonome(1, creerFraction(1, 1)));
            }
            else
            {
                ajouterMonome(&p, creerMonome(1, creerFraction(-1, 1)));
            }
        }
        else if (sscanf(token, "%dX", &coeff.numerateur) == 1)
        {
            coeff.numerateur *= sign;
            //FORMAT %dX
            if (strchr(token, 'X') != NULL)
            {
                ajouterMonome(&p, creerMonome(1, creerFraction(coeff.numerateur, 1)));
            }
            //FORMAT %d
            else
            {
                ajouterMonome(&p, creerMonome(0, creerFraction(coeff.numerateur, 1)));
            }
        }
        else
        {
            printf("Invalid term: %s\n", token);
        }
        token = strtok(NULL, "+-");
    }
    //SIMPLIFIER LE POLYNOME
    while (isDegreeRepeated(p) == 1)
    {    
        p = simplifierPolynome(p);
        p = supprimerzeros(p);
    }
    //TRIE LE POLYNOME
    p = triePolynome(p);
    free(operations);
    return p;
} //COMPLEXITE : O(n^2) (n = nombre de caractere de expression)

//SET POLYNOME
polynome *setPolynome(char *expression, polynome *p)
{
    freePolynome(p->tete);
    polynome *p1 = initialisePolynome();
    p1 = letPolynome(expression);
    return p1;
} //COMPLEXITE : O(n^2) (n = nombre de caractere de expression)

//SOMME DE DEUX POLYNOMES
polynome *sommePolynome(polynome *p1, polynome *p2)
{
    polynome *p = initialisePolynome();
    monome *tmp1 = p1->tete;
    monome *tmp2 = p2->tete;
    while(tmp1 != NULL && tmp2 != NULL)
    {
        //SI LES DEUX DEGRES SONT EGAUX
        if(tmp1->degre == tmp2->degre)
        {
            ajouterMonome(&p, creerMonome(tmp1->degre, sommeFraction(tmp1->coeff, tmp2->coeff)));
            tmp1 = tmp1->suivant;
            tmp2 = tmp2->suivant;
        }
        //SI LE DEGRE DE PREMIER POLYNOME EST SUPERIEUR
        else if(tmp1->degre > tmp2->degre)
        {
            ajouterMonome(&p, creerMonome(tmp1->degre, tmp1->coeff));
            tmp1 = tmp1->suivant;
        }
        //SI LE DEGRE DE DEUXIEME POLYNOME EST SUPERIEUR
        else
        {
            ajouterMonome(&p, creerMonome(tmp2->degre, tmp2->coeff));
            tmp2 = tmp2->suivant;
        }
    }
    //SI LE PREMIER POLYNOME EST PLUS LONG
    while(tmp1 != NULL)
    {
        ajouterMonome(&p, creerMonome(tmp1->degre, tmp1->coeff));
        tmp1 = tmp1->suivant;
    }
    //SI LE DEUXIEME POLYNOME EST PLUS LONG
    while(tmp2 != NULL)
    {
        ajouterMonome(&p, creerMonome(tmp2->degre, tmp2->coeff));
        tmp2 = tmp2->suivant;
    }
    return p;
} //COMPLEXITE : O(n)   (n = nombre de monome)

//DIFFERENCE DE DEUX POLYNOMES
polynome *differencePolynome(polynome *p1, polynome *p2)
{
    polynome *p = initialisePolynome();
    monome *tmp1 = p1->tete;
    monome *tmp2 = p2->tete;
    while(tmp1 != NULL && tmp2 != NULL)
    {
        //SI LES DEUX DEGRES SONT EGAUX
        if(tmp1->degre == tmp2->degre)
        {
            ajouterMonome(&p, creerMonome(tmp1->degre, differenceFraction(tmp1->coeff, tmp2->coeff)));
            tmp1 = tmp1->suivant;
            tmp2 = tmp2->suivant;
        }
        //SI LE DEGRE DE PREMIER POLYNOME EST SUPERIEUR
        else if(tmp1->degre > tmp2->degre)
        {
            ajouterMonome(&p, creerMonome(tmp1->degre, tmp1->coeff));
            tmp1 = tmp1->suivant;
        }
        //SI LE DEGRE DE DEUXIEME POLYNOME EST SUPERIEUR
        else
        {
            ajouterMonome(&p, creerMonome(tmp2->degre, produitFraction(creerFraction(-1, 1), tmp2->coeff)));
            tmp2 = tmp2->suivant;
        }
    }
    //SI LE PREMIER POLYNOME EST PLUS LONG
    while(tmp1 != NULL)
    {
        ajouterMonome(&p, creerMonome(tmp1->degre, tmp1->coeff));
        tmp1 = tmp1->suivant;
    }
    //SI LE DEUXIEME POLYNOME EST PLUS LONG
    while(tmp2 != NULL)
    {
        ajouterMonome(&p, creerMonome(tmp2->degre, produitFraction(creerFraction(-1, 1), tmp2->coeff)));
        tmp2 = tmp2->suivant;
    }
    return p;
} //COMPLEXITE : O(n)   (n = nombre de monome)

//PRODUIT DE DEUX POLYNOMES
polynome *produitPolynome(polynome *p1, polynome *p2)
{
    polynome *p = initialisePolynome();
    monome *tmp1 = p1->tete;
    monome *tmp2 = p2->tete;
    while(tmp1 != NULL)
    {
        while(tmp2 != NULL)
        {
            ajouterMonome(&p, creerMonome(tmp1->degre + tmp2->degre, produitFraction(tmp1->coeff, tmp2->coeff)));
            tmp2 = tmp2->suivant;
        }
        tmp1 = tmp1->suivant;
    }
    return p;
} //COMPLEXITE : O(n^2) (n = nombre de monome)

//PRODUIT DE DEUX POLYNOMES PAR KARATSUBA
polynome *produitPolynomeKaratsuba(polynome *p1, polynome *p2)
{
} //COMPLEXITE : O(n^2) (n = nombre de monome)

//SUPPRIMER LES MONOME LORSQUE NUMERATEUR = 0
polynome *supprimerzeros(polynome *p)
{
    polynome *p1 = initialisePolynome();
    monome *tmp = p->tete;
    while(tmp != NULL)
    {
        if(tmp->coeff.numerateur != 0)
        {
            ajouterMonome(&p1, creerMonome(tmp->degre, tmp->coeff));
        }
        tmp = tmp->suivant;
    }
    return p1;
} //COMPLEXITE : O(n)   (n = nombre de monome)

//AFFICHAGE DE POLYNOME
void afficherPolynome(monome *m)
{
    if (m != NULL)
    {
        while (m != NULL)
        {
            //SI LE NUMERATEUR EST DIFFERENT DE 0 
            if (m->coeff.numerateur != 0)
            {
                m->coeff = simplifierFraction(m->coeff);
                //SI LE DEGRE EST 0
                if (m->degre == 0)
                {
                    //SI LE DENOMINATEUR EST 1
                    if (m->coeff.denominateur == 1)
                    {
                        printf("%d", m->coeff.numerateur);
                    }
                    //SI LE DENOMINATEUR EST DIFFERENT DE 1
                    else
                    {
                        printf("%d/%d", m->coeff.numerateur, m->coeff.denominateur);
                    }
                }
                //SI LE DEGRE EST 1
                else if (m->degre == 1)
                {
                    //SI LE DENOMINATEUR EST 1
                    if (m->coeff.denominateur == 1)
                    {
                        //SI LE NUMERATEUR EST 1
                        if (m->coeff.numerateur == 1)
                        {
                            printf("x");
                        }
                        //SI LE NUMERATEUR EST -1
                        else if (m->coeff.numerateur == -1)
                        {
                            printf("-x");
                        }
                        //SI LE NUMERATEUR EST DIFFERENT DE 1 ET -1
                        else
                        {
                            printf("%dx", m->coeff.numerateur);
                        }
                    }
                    //SI LE DENOMINATEUR EST DIFFERENT DE 1
                    else
                    {
                        //SI LE DENOMINATEUR EST 1
                        if (m->coeff.denominateur == 1)
                        {
                            printf("%dX", m->coeff.numerateur);
                        }
                        //SI LE DENOMINATEUR EST DIFFERENT DE 1
                        else
                        {
                            printf("%d/%dX", m->coeff.numerateur, m->coeff.denominateur);
                        }
                    }
                }
                //SI LE DEGRE EST DIFFERENT DE 0 ET 1
                else
                {
                    //SI LE DENOMINATEUR EST 1
                    if (m->coeff.denominateur == 1)
                    {
                        //SI LE NUMERATEUR EST 1
                        if (m->coeff.numerateur == 1)
                        {
                            printf("x^%d", m->degre);
                        }
                        //SI LE NUMERATEUR EST -1
                        else if (m->coeff.numerateur == -1)
                        {
                            printf("-x^%d", m->degre);
                        }
                        //SI LE NUMERATEUR EST DIFFERENT DE 1 ET -1
                        else
                        {
                            printf("%dx^%d", m->coeff.numerateur, m->degre);
                        }
                    }
                    //SI LE DENOMINATEUR EST DIFFERENT DE 1
                    else
                    {
                        //SI LE DENOMINATEUR EST 1
                        if (m->coeff.denominateur == 1)
                        {
                            printf("%dX^%d", m->coeff.numerateur, m->degre);
                        }
                        //SI LE DENOMINATEUR EST DIFFERENT DE 1
                        else
                        {
                            printf("%d/%dX^%d", m->coeff.numerateur, m->coeff.denominateur, m->degre);
                        }
                    }
                }
                if (m->suivant != NULL)
                {
                    //SI LE COEFFICIENT DU MONOME SUIVANT EST POSITIF
                    if(m->suivant->coeff.numerateur > 0)
                    {
                        printf("+");
                    }
                }
            }
            m = m->suivant;
        }
    }
    //SI LE POLYNOME EST VIDE
    else
    {
        printf("0");
    }
} //COMPLEXITE : O(n)   (n = nombre de monome)

//PUISSANCE DE POLYNOME
polynome *puissancePolynome(polynome *p, int n)
{
    if (n == 0)
    {
        return letPolynome("1");
    }
    else
    {
        polynome *partialResult = puissancePolynome(p, n - 1);
        return produitPolynome(partialResult, p);
    }
} //COMPLEXITE : O(n^2) (n = nombre de monome)

//AFFECTATION DE POLYNOME A POLYNOME
polynome *affectationPolynome(polynome *p1, polynome *p2)
{
    freePolynome(p1->tete);
    polynome *p = initialisePolynome();
    monome *tmp = p2->tete;
    while(tmp != NULL)
    {
        ajouterMonome(&p, creerMonome(tmp->degre, tmp->coeff));
        tmp = tmp->suivant;
    }
    return p;
} //COMPLEXITE : O(n)   (n = nombre de monome)

//DERIVEE DE POLYNOME
polynome *deriveePolynome(polynome *p)
{
    polynome *p1 = initialisePolynome();
    monome *tmp = p->tete;
    while(tmp != NULL)
    {
        if(tmp->degre != 0)
        {
            ajouterMonome(&p1, creerMonome(tmp->degre - 1, produitFraction(tmp->coeff, creerFraction(tmp->degre, 1))));
        }
        tmp = tmp->suivant;
    }
    return p1;
} //COMPLEXITE : O(n)   (n = nombre de monome)

//INTEGRALE DE POLYNOME
polynome *integralePolynome(polynome *p)
{
    polynome *p1 = initialisePolynome();
    monome *tmp = p->tete;
    while(tmp != NULL)
    {
        ajouterMonome(&p1, creerMonome(tmp->degre + 1, produitFraction(tmp->coeff, creerFraction(1, tmp->degre + 1))));
        tmp = tmp->suivant;
    }
    return p1;
} //COMPLEXITE : O(n)   (n = nombre de monome)

//EVALUATION DE POLYNOME
float evaluationPolynome(polynome *p, float x)
{
    float resultat = 0;
    monome *tmp = p->tete;
    while(tmp != NULL)
    {
        resultat += (tmp->coeff.numerateur * pow(x, tmp->degre) )/ tmp->coeff.denominateur;
        tmp = tmp->suivant;
    }
    return resultat;
} //COMPLEXITE : O(n)   (n = nombre de monome)

#endif