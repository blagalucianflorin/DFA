//
// Created by lblaga on 18.04.2020.
//

#include "../headers/NFA.h"


std::vector <int> NFA::delta (int start_state, char transition_character) noexcept (false)
{
    std::vector <int> result;

    if (std::find (this -> states . begin (), this -> states . end (), start_state) == this -> states . end ())
    {
        throw (FaException::State_does_not_exist (start_state));
    }

    if (std::find (this -> get_alphabet () . begin (), this -> get_alphabet () . end (), transition_character) ==
        this -> get_alphabet () . end ())
    {
        throw (FaException::Character_does_not_exist (transition_character));
    }

    for (std::tuple <int, char, int> transition : this -> get_transitions ())
    {
        if (std::get <0> (transition) == start_state && std::get <1> (transition) == transition_character)
        {
            result . push_back (std::get <2> (transition));
        }
    }
    return (result);
}

void NFA::add_transition (int start_state, char transition_character, int end_state) noexcept (false)
{
    if (std::find (this -> states . begin (), this -> states . end (), start_state) == this -> states . end ())
    {
        throw (FaException::State_does_not_exist (start_state));
    }
    if (std::find (this -> alphabet . begin (), this -> alphabet . end (), transition_character) ==
        this -> alphabet . end ())
    {
        throw (FaException::Character_does_not_exist (transition_character));
    }
    if (std::find (this -> states . begin (), this -> states . end (), start_state) == this -> states . end ())
    {
        throw (FaException::State_does_not_exist (end_state));
    }
    for (std::tuple <int, char, int> transition : this -> transitions)
    {
        if (std::get <0> (transition) == start_state && std::get <1> (transition) == transition_character &&
            std::get <2> (transition) == end_state)
        {
            throw (FaException::Transition_already_exists (start_state, transition_character, end_state));
        }
    }
    this -> transitions . emplace_back (start_state, transition_character, end_state);
}

bool NFA::accepts (std::string input_word) noexcept (false)
{
    std::vector <int> current_states;
    int current_size;

    if (get_initial_state () == INT_MIN)
    {
        throw (FaException::Initial_state_not_set ());
    }
    if (get_final_states () . empty ())
    {
        throw (FaException::No_final_states ());
    }

    current_states . push_back (this -> get_initial_state ());
    while (input_word . length () != 0)
    {
        if (std::find (this -> get_alphabet () . begin (), this -> get_alphabet () . end (), input_word[0]) ==
            this -> get_alphabet () . end ())
        {
            throw (FaException::Character_does_not_exist (input_word[0]));
        }

        current_size = current_states . size ();
        for (int i = 0; i < current_size; i++)
        {
            for (int new_state : delta (current_states[i], input_word[0]))
                current_states . push_back (new_state);
        }
        current_states . erase (current_states . begin (), current_states . begin () + current_size);

        input_word = input_word . substr (1, input_word . length () - 1);
    }
    for (int i : current_states)
        for (int j : this -> get_final_states ())
            if (i == j)
                return (true);
    return (false);
}

