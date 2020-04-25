//
// Created by lblaga on 17.04.2020.
//

#ifndef DFA_DFA_H
#define DFA_DFA_H

#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
#include <climits>
#include <iostream>
#include <set>

#include "exceptions/faExceptions.h"

class DFA
{
protected:
    std::vector <int> states;
    std::vector <char> alphabet;
    std::vector <int> final_states;
    std::vector <std::tuple <int, char, int>> transitions;
    int initial_state = INT_MIN;

public:
    DFA (std::vector <int> states, std::vector <char> alphabet, std::vector <int> final_states,
         std::vector <std::tuple <int, char, int>> transitions, int initial_state);

    DFA () = default;

    ~DFA () = default;

    DFA (const DFA &old_dfa);


    void add_state (int new_state) noexcept (false);

    void add_state (const std::vector <int> &new_states) noexcept (false);

    const std::vector <int> &get_states () const;

    void delete_state (int old_state) noexcept (false);


    void add_character (char new_character) noexcept (false);

    void add_character (const std::vector <char> &new_characters) noexcept (false);

    const std::vector <char> &get_alphabet () const;

    void delete_character (char old_character) noexcept (false);


    void add_final_state (int new_final_state) noexcept (false);

    void add_final_state (const std::vector <int> &new_final_states) noexcept (false);

    const std::vector <int> &get_final_states () const;

    bool is_final_state (int my_state) const;

    void remove_final_state (int old_final_state) noexcept (false);


    virtual void add_transition (int start_state, char transition_character, int end_state) noexcept (false);

    const std::vector <std::tuple <int, char, int>> &get_transitions () const;

    void delete_transition (int start_state, char transition_character, int end_state) noexcept (false);

    void delete_transition (char transition_character) noexcept (false);

    void delete_transition (int state) noexcept (false);


    const int &get_initial_state () const;

    void set_initial_state (int new_initial_state) noexcept (false);

    void reset_initial_state ();


    virtual bool accepts (std::string input_word) noexcept (false);

    void reset ();

    void display ();
};

#endif //DFA_DFA_H
