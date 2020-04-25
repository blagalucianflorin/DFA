//
// Created by lblaga on 25.04.2020.
//

#ifndef DFA_REGGRAMMAR_H
#define DFA_REGGRAMMAR_H

#include <string>
#include <vector>
#include <tuple>

#include "LNFA.h"

#define lambda '#'

class RegGrammar
{
private:
    std::vector <char> symbols;
    std::vector <char> terminals;
    std::vector <std::tuple <char, char, char>> productions;
    char start_symbol;

public:
    void add_symbol (char new_symbol);

    void add_terminal (char new_terminal);

    void add_production (char start_sym, char terminal_character, char end_sym);

    void set_start_symbol (char new_start_symbol);

    const std::vector <char> &get_symbols ();

    const std::vector <char> &get_terminals ();

    const std::vector <std::tuple <char, char, char>> &get_productions ();

    const char &get_start_symbol ();

    bool accepts (std::string input_word);
};

#endif //DFA_REGGRAMMAR_H
