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

#ifdef DEBUG
#include <iostream>
#endif

#include "exceptions/faExceptions.h"

class DFA
{
private:
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

    std::vector <int> get_states () const;

    void delete_state (int old_state) noexcept (false);


    void add_character (char new_character) noexcept (false);

    void add_character (const std::vector <char> &new_characters) noexcept (false);

    std::vector <char> get_alphabet () const;

    void delete_character (char old_character) noexcept (false);


    void add_final_state (int new_final_state) noexcept (false);

    void add_final_state (const std::vector <int> &new_final_states) noexcept (false);

    std::vector <int> get_final_states () const;

    bool is_final_state (int my_state) const;

    void remove_final_state (int old_final_state) noexcept (false);


    void add_transition (int start_state, char transition_character, int end_state) noexcept (false);

    std::vector <std::tuple <int, char, int>> get_transitions () const;

    void delete_transition (int start_state, char transition_character, int end_state) noexcept (false);

    void delete_transition (char transition_character) noexcept (false);

    void delete_transition (int state) noexcept (false);


    int get_initial_state () const;

    void set_initial_state (int new_initial_state) noexcept (false);

    void reset_initial_state ();


    /**
     *
     * Determines if a word is <b>accepted</b> by the automate or not.
     *
     * @param input_word : A std::string word which will be tested in the automate. Must be composed only of characters
     * present in the alphabet.
     *
     * @throws FaException::Initial_state_not_set : If the initial state has not been set.
     *
     * @throws FaException::No_final_states : If no final states have been added.
     *
     * @throws FaException::Character_does_not_exist : If any character in the input word is not
     * present in the alphabet.
     *
     * @return Returns <b>true</b> if the word if accepted by the automate and <b>false</b> if it is not.
     *
     */
    bool accepts (std::string input_word) noexcept (false);

#ifdef DEBUG
    void display ();
#endif
};

#endif //DFA_DFA_H
