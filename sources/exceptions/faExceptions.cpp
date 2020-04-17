//
// Created by lblaga on 17.04.2020.
//

#include "../../headers/exceptions/faExceptions.h"

const char *FaException::FaException::what () const noexcept (true)
{
    return this -> message . c_str ();
}

using namespace FaException;

int State_exception::get_state () const
{
    return this -> state;
}

State_already_exists::State_already_exists (int state)
{
    this -> state = state;
    this -> message = "FaException::State_already_exists: State (" + std::to_string (state) + ") already exists.\n";
}

State_already_final::State_already_final (int state)
{
    this -> state = state;
    this -> message = "FaException::State_already_final: State (" + std::to_string (state) + ") is already final.\n";
}

State_does_not_exist::State_does_not_exist (int state)
{
    this -> state = state;
    this -> message = "FaException::State_does_not_exist: State (" + std::to_string (state) + ") does not exist.\n";
}

Initial_state_not_set::Initial_state_not_set ()
{
    this -> message = "FaException::Initial_state_not_set: No initial state has been set.\n";
}

No_final_states::No_final_states ()
{
    this -> message = "FaException::No_final_states: No final state has been set.\n";
}

State_is_not_final::State_is_not_final (int state)
{
    this -> state = state;
    this -> message = "FaException::State_is_not_final: State (" + std::to_string (state) + ") is not final.\n";
}


char Character_exception::get_character () const
{
    return this -> character;
}

Character_already_exists::Character_already_exists (char character)
{
    this -> character = character;
    this -> message = "FaException::Character_already_exists: Character ('";
    this -> message += character;
    this -> message += "') already exists in the alphabet.\n";
}

Character_does_not_exist::Character_does_not_exist (char character)
{
    this -> character = character;
    this -> message = "FaException::Character_already_exists: Character ('";
    this -> message += character;
    this -> message += "') does not exist in the alphabet.\n";
}


int Transition_exception::get_start_state () const
{
    return this -> start_state;
}

char Transition_exception::get_transition_character () const
{
    return this -> transition_character;
}

int Transition_exception::get_end_state () const
{
    return this -> end_state;
}

Transition_already_exists::Transition_already_exists (int start_state, char transition_character, int end_state)
{
    this -> start_state = start_state;
    this -> transition_character = transition_character;
    this -> end_state = end_state;
    this -> message =
            "FaException::Transition_already_exists: Transition (" + std::to_string (start_state) + ", '" +
            transition_character +
            "', " + std::to_string (end_state) +
            ") already exists.\n";
}

Transition_does_not_exist::Transition_does_not_exist (int start_state, char transition_character, int end_state)
{
    this -> start_state = start_state;
    this -> transition_character = transition_character;
    this -> end_state = end_state;
    this -> message =
            "FaException::Transition_does_not_exist: Transition (" + std::to_string (start_state) + ", '" +
            transition_character +
            "', " + std::to_string (end_state) +
            ") does not exist.\n";
}

Transition_with_character_already_exists::Transition_with_character_already_exists (int start_state,
                                                                                    char transition_character)
{
    this -> start_state = start_state;
    this -> transition_character = transition_character;
    this -> message = "FaException::Transition_with_character_already_exists: A transition from (" +
                      std::to_string (start_state) +
                      ") with ('" + transition_character + "') already exists.\n";
}

