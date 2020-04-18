#include <iostream>

#define DEBUG

#include "headers/LNFA.h"

int main ()
{
    LNFA my_lnfa;
    std::string input_word = "ab";

    my_lnfa . add_state ({0, 1, 2, 3, 4, 5});
    my_lnfa . set_initial_state (0);
    my_lnfa . add_final_state (5);
    my_lnfa . add_character ({'a', 'b'});
    my_lnfa . add_transition (0, lambda, 1);
    my_lnfa . add_transition (1, lambda, 2);
//    my_lnfa . add_transition (1, lambda, 2);
    my_lnfa . add_transition (2, lambda, 0);
    my_lnfa . add_transition (2, 'a', 3);
    my_lnfa . add_transition (3, lambda, 4);
    my_lnfa . add_transition (4, 'b', 5);

    my_lnfa . display ();

    std::cout << my_lnfa . accepts (input_word) << std::endl;

    return (0);
}
