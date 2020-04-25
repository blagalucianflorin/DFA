#include <iostream>
#include <fstream>
#include <sstream>

#include "headers/LNFA.h"
#include "headers/regGrammar.h"

RegGrammar *read_grammar_from_file (const char *file_name)
{
    std::ifstream fin;
    std::string line;
    char aux;
    char start_symbol;
    char end_symbol;
    auto ret_grammar = new RegGrammar ();

    fin . open (file_name);
    {
        std::getline (fin, line);
        std::istringstream iss (line);
        while (iss >> aux)
            ret_grammar -> add_symbol (aux);
    }

    {
        std::getline (fin, line);
        std::istringstream iss (line);
        while (iss >> aux)
            ret_grammar -> add_terminal (aux);
    }

    {
        std::getline (fin, line);
        std::istringstream iss (line);
        iss >> aux;
        ret_grammar -> set_start_symbol (aux);
    }

    while (std::getline (fin, line))
    {
        std::istringstream iss (line);
        iss >> start_symbol >> aux;
        if (iss >> end_symbol)
            ret_grammar -> add_production (start_symbol, aux, end_symbol);
        else
            ret_grammar -> add_production (start_symbol, aux, -1);
    }
    fin . close ();

    return (ret_grammar);
}

LNFA *read_LNFA_from_file (const char *file_name)
{
    auto ret_lnfa = new LNFA ();
    std::ifstream fin;
    std::string line;
    char aux_char;
    int aux_int;
    int start_state;
    char transition_character;
    int end_state;

    fin . open (file_name);
    {
        std::getline (fin, line);
        std::istringstream iss (line);
        while (iss >> aux_int)
            ret_lnfa -> add_state (aux_int);
    }
    {
        std::getline (fin, line);
        std::istringstream iss (line);
        while (iss >> aux_int)
            ret_lnfa -> add_final_state (aux_int);
    }
    {
        std::getline (fin, line);
        std::istringstream iss (line);
        iss >> aux_int;
        ret_lnfa -> set_initial_state (aux_int);
    }
    {
        std::getline (fin, line);
        std::istringstream iss (line);
        while (iss >> aux_char)
            ret_lnfa -> add_character (aux_char);
    }

    while (std::getline (fin, line))
    {
        std::istringstream iss (line);
        iss >> start_state >> transition_character >> end_state;
        ret_lnfa -> add_transition (start_state, transition_character, end_state);
    }
    fin . close ();

    return (ret_lnfa);
}

int main ()
{
    /* Acceptare cuvant in gramatica regulata */
    RegGrammar *my_regGrammar;
    std::vector <std::string> regGrammarTests;

    regGrammarTests = {
            "a",
            "b",
            "bb",
            "bbb",
            "ab",
            "ba",
    };
    my_regGrammar = read_grammar_from_file ("grammar1.input");


    std::cout << "\n[Start Regular Grammar test]\n";
    for (const std::string &test : regGrammarTests)
        std::cout << test << ": " << my_regGrammar -> accepts (test) << "\n";
    std::cout << "[End Regular Grammar test]\n\n";


    /* Conversie LNFA in DFA */
    DFA *my_dfa;
    LNFA *my_lnfa;

    my_lnfa = read_LNFA_from_file ("lnfa1.input");

    my_lnfa -> display ();
    my_dfa = my_lnfa -> to_DFA ();
    my_dfa -> display ();

    delete my_dfa;
    delete my_lnfa;
    delete my_regGrammar;

    return (0);
}
