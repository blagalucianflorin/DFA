#include <iostream>

#define DEBUG

#include "headers/DFA.h"

int main ()
{
    DFA my_dfa;
    std::string input_word = "abc";

    my_dfa . add_state ({0, 1, 2, 3});
    my_dfa . add_character ({'a', 'b', 'c'});
    my_dfa . add_final_state ({0, 3});
    my_dfa . set_initial_state (0);
    my_dfa . add_transition (0, 'a', 1);
    my_dfa . add_transition (1, 'b', 2);
    my_dfa . add_transition (2, 'c', 3);
    my_dfa . add_transition (3, 'a', 0);

    my_dfa . delete_transition (1, 'b', 2);

    std::cout << my_dfa . accepts (input_word);

    return (0);
}
