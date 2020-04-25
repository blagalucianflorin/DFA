#include <iostream>

#define DEBUG

#include "headers/LNFA.h"

int main ()
{
    LNFA my_lnfa;

    my_lnfa . add_state ({0, 1, 2, 3, 4, 5});
    my_lnfa . set_initial_state (0);
    my_lnfa . add_final_state (5);
    my_lnfa . add_character ({'a', 'b', 'c'});
    my_lnfa . add_transition (0, 'a', 1);
    my_lnfa . add_transition (0, lambda, 3);
    my_lnfa . add_transition (0, 'a', 4);
    my_lnfa . add_transition (1, 'c', 2);
    my_lnfa . add_transition (1, 'c', 4);
    my_lnfa . add_transition (2, 'b', 5);
    my_lnfa . add_transition (3, 'a', 4);
    my_lnfa . add_transition (4, lambda, 2);
    my_lnfa . add_transition (4, lambda, 5);
    my_lnfa . add_transition (5, 'c', 0);
    my_lnfa . add_transition (5, 'a', 3);

    my_lnfa . display ();

    DFA my_dfa = my_lnfa . to_DFA ();

    my_dfa . display ();


    std::string input_word = "ab";

    std::cout << my_lnfa . accepts (input_word) << " " << my_dfa . accepts (input_word);

    return (0);
}
