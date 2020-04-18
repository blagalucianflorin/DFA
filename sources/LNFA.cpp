//
// Created by lblaga on 18.04.2020.
//

#include "../headers/LNFA.h"

std::vector <int> LNFA::lambda_closure (int start_state)
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

