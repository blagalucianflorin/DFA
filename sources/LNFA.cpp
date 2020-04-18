//
// Created by lblaga on 18.04.2020.
//

#include "../headers/LNFA.h"

std::vector <int> LNFA::lambda_closure (int start_state) noexcept (false)
{
    std::vector <int> result;
    std::vector <int> state_queue;

    if (std::find (this -> get_states () . begin (), this -> get_states () . end (), start_state) ==
        this -> get_states () . end ())
    {
        throw (FaException::State_does_not_exist (start_state));
    }
    state_queue . push_back (start_state);
    while (!state_queue . empty ())
    {
        result . push_back (state_queue . front ());
        for (std::tuple <int, char, int> transition : this -> get_transitions ())
        {
            if (std::get <0> (transition) == state_queue . front () && std::get <1> (transition) == lambda)
                if (std::count (result . begin (), result . end (), std::get <2> (transition)) == 0)
                {
                    state_queue . push_back (std::get <2> (transition));
                }
        }
        state_queue . erase (state_queue . begin ());
    }
    std::sort (result . begin (), result . end ());
    return (result);
}

void LNFA::add_transition (int start_state, char transition_character, int end_state) noexcept (false)
{
    if (std::find (this -> states . begin (), this -> states . end (), start_state) == this -> states . end ())
    {
        throw (FaException::State_does_not_exist (start_state));
    }
    if (transition_character != lambda &&
        std::find (this -> alphabet . begin (), this -> alphabet . end (), transition_character) ==
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
        if (std::get <0> (transition) == start_state &&
            (std::get <1> (transition) == transition_character || std::get <1> (transition) == lambda) &&
            std::get <2> (transition) == end_state)
        {
            throw (FaException::Transition_already_exists (start_state, transition_character, end_state));
        }
    }
    this -> transitions . emplace_back (start_state, transition_character, end_state);
}

bool LNFA::accepts (std::string input_word) noexcept (false)
{
    std::vector <int> current_states;
    std::vector <int> old_states;
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
    while (input_word . length () != 0 || current_states != old_states)
    {
        old_states = current_states;

        current_size = current_states . size ();
        for (int i = 0; i < current_size; i++)
            for (int new_state : lambda_closure (current_states[i]))
                if (std::count (current_states . begin (), current_states . end (), new_state) == 0)
                    current_states . push_back (new_state);

        if (input_word . length () != 0)
        {
            if (std::find (this -> get_alphabet () . begin (), this -> get_alphabet () . end (), input_word[0]) ==
                this -> get_alphabet () . end ())
            {
                throw (FaException::Character_does_not_exist (input_word[0]));
            }
            current_size = current_states . size ();
            for (int i = 0; i < current_size; i++)
                for (int new_state : delta (current_states[i], input_word[0]))
                    if (std::count (current_states . begin (), current_states . end (), new_state) == 0)
                        current_states . push_back (new_state);
        }

        current_size = current_states . size ();
        for (int i = 0; i < current_size; i++)
            for (int new_state : lambda_closure (current_states[i]))
                if (std::count (current_states . begin (), current_states . end (), new_state) == 0)
                    current_states . push_back (new_state);

        if (input_word . length () != 0)
            input_word = input_word . substr (1, input_word . length () - 1);
        std::sort (current_states . begin (), current_states . end ());
    }
    for (int i : current_states)
        for (int j : this -> get_final_states ())
            if (i == j)
                return (true);
    return (false);
}

