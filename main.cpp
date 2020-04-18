#include <iostream>

#define DEBUG

#include "headers/LNFA.h"

int main ()
{
    LNFA my_lnfa;

    my_lnfa . add_state ({0, 1, 2, 3});
    my_lnfa . add_transition (0, lambda, 1);
    my_lnfa . add_transition (1, lambda, 0);
    my_lnfa . add_transition (0, lambda, 0);
    my_lnfa . add_transition (1, lambda, 2);

    my_lnfa . display ();

    for (int state : my_lnfa . lambda_closure (1))
        std::cout << state << " ";
    std::cout << std::endl;

    return (0);
}
