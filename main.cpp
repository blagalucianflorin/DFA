#include <iostream>

#define DEBUG

#include "headers/NFA.h"
//#include "headers/DFA.h"

int main ()
{
    NFA my_nfa;
    std::string input_word = "aabaaaaaaaaaaabaaaab";

    my_nfa . add_state ({0, 1});
    my_nfa . add_character ({'a', 'b'});
    my_nfa . set_initial_state (0);
    my_nfa . add_final_state ({1});

    my_nfa . add_transition (0, 'a', 1);
    my_nfa . add_transition (0, 'b', 0);
    my_nfa . add_transition (0, 'a', 0);

    std::cout << my_nfa . accepts (input_word) << std::endl;

    my_nfa . DFA::display ();

    return (0);
}
