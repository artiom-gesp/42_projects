#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stack
{
    char bal;
    float weigth;
    struct stack *next;
}               stack;

stack* insert_stack(stack *val, char bal, float value)
{
    stack *tmp = val;
    stack *n;

    while (val)
    {
        if (val->bal == bal)
        {
            val->weigth += value;
            return tmp;
        }
        val = val->next;
    }
    n = malloc(sizeof(val));
    n->bal = bal;
    n->weigth = value;
    n->next = tmp;

    return n;
}

// void print_s(stack *val)
// {
//     while (val)
//     {
//         printf("%c %f\n", val->bal, val->weigth);
//         val = val->next;
//     }
// }

void print_s(stack *val)
{
    float max = -1;
    char max_val = 0;
    while (val)
    {
        // printf("%c %f\n", val->bal, val->weigth);
        max_val = max == -1 || val->weigth > max || (max == val->weigth && val->bal < max_val) ? val->bal : max_val;
        max = max == -1 || val->weigth > max || (max == val->weigth && val->bal < max_val) ? val->weigth : max;
        printf("%f %c\n", val->weigth, val->bal);
        val = val->next;
    }
    printf("\n%c\n", max_val);
}


int main() {
   char s[1024];
    stack *st;
    stack *val;
    stack *tmp;
    int bet = 1;

    st = NULL;
    val = NULL;
	while (scanf("%s", &s) != EOF) {
		//
		// Lisez les données ici et effectuez votre traitement ici
		//
	}

	for (int i = 0; i < strlen(s); ++i)
	{
	    if (s[i] != '-')
	    {
	         tmp = malloc(sizeof(stack));
	         tmp->bal = s[i];
	         tmp->next = st;
	         st = tmp;
	         val = insert_stack(val, s[i], (float)1 / bet);
	         ++bet;
	    }
	    if (s[i] == '-')
	    {
	        st = st->next;
	        ++i;
          --bet;
	    }
	}
	print_s(val);


	// Vous pouvez aussi effectuer votre traitement ici après avoir lu toutes les données
	return 0;
}
