//
// Created by lblaga on 25.04.2020.
//

#include "../headers/regGrammar.h"

#include <utility>


void RegGrammar::add_symbol (char new_symbol)
{
    this -> symbols . push_back (new_symbol);
}

void RegGrammar::add_terminal (char new_terminal)
{
    this -> terminals . push_back (new_terminal);
}

void RegGrammar::add_production (char start_sym, char terminal_character, char end_sym)
{
    this -> productions . emplace_back (start_sym, terminal_character, end_sym);
}

void RegGrammar::set_start_symbol (char new_start_symbol)
{
    this -> start_symbol = new_start_symbol;
}

const std::vector <char> &RegGrammar::get_symbols ()
{
    return this -> symbols;
}

const std::vector <char> &RegGrammar::get_terminals ()
{
    return this -> terminals;
}

const std::vector <std::tuple <char, char, char>> &RegGrammar::get_productions ()
{
    return this -> productions;
}

const char &RegGrammar::get_start_symbol ()
{
    return this -> start_symbol;
}

int max (int a, int b)
{
    return a > b ? a : b;
}

bool RegGrammar::accepts (std::string input_word)
{
    LNFA my_lnfa;
    DFA *my_dfa;
    bool response;

    for (char curr_char : this -> get_symbols ())
        my_lnfa . add_state (((int) curr_char) - 65);
    my_lnfa . add_state (-1);

    for (char curr_char : this -> get_terminals ())
        my_lnfa . add_character (curr_char);

    my_lnfa . set_initial_state (((int) this -> get_start_symbol ()) - 65);

    my_lnfa . add_final_state (-1);

    for (std::tuple <char, char, char> production : this -> get_productions ())
        my_lnfa . add_transition (((int) std::get <0> (production)) - 65, std::get <1> (production),
                                  (max (((int) std::get <2> (production)) - 65, -1)));

    my_dfa = my_lnfa . to_DFA ();
    response = my_dfa -> accepts (std::move (input_word));
    delete my_dfa;

    return (response);
}
