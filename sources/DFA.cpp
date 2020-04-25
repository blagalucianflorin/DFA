//
// Created by lblaga on 17.04.2020.
//

#include "../headers/DFA.h"


DFA::DFA (const DFA &old_dfa)
{
    this -> states = old_dfa . get_states ();
    this -> alphabet = old_dfa . get_alphabet ();
    this -> final_states = old_dfa . get_final_states ();
    this -> transitions = old_dfa . get_transitions ();
    this -> initial_state = old_dfa . get_initial_state ();
}

DFA::DFA (std::vector <int> states, std::vector <char> alphabet, std::vector <int> final_states,
          std::vector <std::tuple <int, char, int>> transitions, int initial_state)
{
    this -> states = std::move (states);
    this -> alphabet = std::move (alphabet);
    this -> final_states = std::move (final_states);
    this -> transitions = std::move (transitions);
    this -> initial_state = initial_state;
}


void DFA::add_state (int new_state) noexcept (false)
{
    if (std::find (this -> states . begin (), this -> states . end (), new_state) == this -> states . end ())
    {
        this -> states . push_back (new_state);
    }
    else
    {
        throw (FaException::State_already_exists (new_state));
    }
}

void DFA::add_state (const std::vector <int> &new_states) noexcept (false)
{
    for (int new_state : new_states)
        this -> add_state (new_state);
}

const std::vector <int> & DFA::get_states () const
{
    return (this -> states);
}

void DFA::delete_state (const int old_state) noexcept (false)
{
    if (std::find (this -> states . begin (), this -> states . end (), old_state) == this -> states . end ())
    {
        throw (FaException::State_does_not_exist (old_state));
    }
    this -> states . erase (std::remove (this -> states . begin (), this -> states . end (), old_state),
                            this -> states . end ());
    this -> final_states . erase (
            std::remove (this -> final_states . begin (), this -> final_states . end (), old_state),
            this -> final_states . end ());
    if (this -> initial_state == old_state)
        this -> initial_state = INT_MIN;
    for (std::tuple <int, char, int> transition : this -> transitions)
        if (std::get <0> (transition) == old_state || std::get <2> (transition) == old_state)
            this -> transitions . erase (
                    std::remove (this -> transitions . begin (), this -> transitions . end (), transition),
                    this -> transitions . end ());
}


void DFA::add_character (char new_character) noexcept (false)
{
    if (std::find (this -> alphabet . begin (), this -> alphabet . end (), new_character) == this -> alphabet . end ())
    {
        this -> alphabet . push_back (new_character);
    }
    else
    {
        throw (FaException::Character_already_exists (new_character));
    }
}

void DFA::add_character (const std::vector <char> &new_characters) noexcept (false)
{
    for (char new_character : new_characters)
        this -> add_character (new_character);
}

const std::vector <char> & DFA::get_alphabet () const
{
    return (this -> alphabet);
}

void DFA::delete_character (const char old_character) noexcept (false)
{
    if (std::find (this -> alphabet . begin (), this -> alphabet . end (), old_character) == this -> alphabet . end ())
    {
        throw (FaException::Character_does_not_exist (old_character));
    }

    this -> alphabet . erase (std::remove (this -> alphabet . begin (), this -> alphabet . end (), old_character),
                              this -> alphabet . end ());

    for (std::tuple <int, char, int> transition : this -> transitions)
        if (std::get <1> (transition) == old_character)
            this -> transitions . erase (
                    std::remove (this -> transitions . begin (), this -> transitions . end (), transition),
                    this -> transitions . end ());
}


void DFA::add_final_state (int new_final_state) noexcept (false)
{
    if (std::find (this -> states . begin (), this -> states . end (), new_final_state) !=
        this -> states . end ())
    {
        if (std::find (this -> final_states . begin (), this -> final_states . end (), new_final_state) ==
            this -> final_states . end ())
        {
            this -> final_states . push_back (new_final_state);
        }
        else
        {
            throw (FaException::State_already_final (new_final_state));
        }
    }
    else
    {
        throw (FaException::State_does_not_exist (new_final_state));
    }
}

void DFA::add_final_state (const std::vector <int> &new_final_states) noexcept (false)
{
    for (int new_final_state : new_final_states)
        this -> add_final_state (new_final_state);
}

const std::vector <int> & DFA::get_final_states () const
{
    return (this -> final_states);
}

bool DFA::is_final_state (const int my_state) const
{
    if (std::find (this -> states . begin (), this -> states . end (), my_state) == this -> states . end ())
    {
        throw (FaException::State_does_not_exist (my_state));
    }
    return ((std::find (this -> final_states . begin (), this -> final_states . end (), my_state) !=
             this -> final_states . end ()));
}

void DFA::remove_final_state (const int old_final_state) noexcept (false)
{
    if (std::find (this -> states . begin (), this -> states . end (), old_final_state) == this -> states . end ())
    {
        throw (FaException::State_does_not_exist (old_final_state));
    }
    if (std::find (this -> final_states . begin (), this -> final_states . end (), old_final_state) ==
        this -> final_states . end ())
    {
        throw (FaException::State_is_not_final (old_final_state));
    }
    this -> final_states . erase (
            std::remove (this -> final_states . begin (), this -> final_states . end (), old_final_state),
            this -> final_states . end ());
}


void DFA::add_transition (int start_state, char transition_character, int end_state) noexcept (false)
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
        if (std::get <0> (transition) == start_state && std::get <1> (transition) == transition_character)
        {
            throw (FaException::Transition_with_character_already_exists (start_state, transition_character));
        }
    }
    this -> transitions . emplace_back (start_state, transition_character, end_state);
}

const std::vector <std::tuple <int, char, int>> & DFA::get_transitions () const
{
    return (this -> transitions);
}

void DFA::delete_transition (int start_state, char transition_character, int end_state) noexcept (false)
{
    bool found_transition;

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

    found_transition = false;
    for (std::tuple <int, char, int> transition : this -> transitions)
    {
        if (std::get <0> (transition) == start_state && std::get <1> (transition) == transition_character &&
            std::get <2> (transition) == end_state)
        {
            found_transition = true;
            break;
        }
    }
    if (!found_transition)
    {
        throw (FaException::Transition_does_not_exist (start_state, transition_character, end_state));
    }

    this -> transitions . erase (std::remove (this -> transitions . begin (), this -> transitions . end (),
                                              std::make_tuple (start_state, transition_character, end_state)),
                                 this -> transitions . end ());
}

void DFA::delete_transition (char transition_character) noexcept (false)
{
    if (std::find (this -> alphabet . begin (), this -> alphabet . end (), transition_character) ==
        this -> alphabet . end ())
    {
        throw (FaException::Character_does_not_exist (transition_character));
    }

    for (std::tuple <int, char, int> transition : this -> transitions)
        if (std::get <1> (transition) == transition_character)
            this -> transitions . erase (
                    std::remove (this -> transitions . begin (), this -> transitions . end (), transition),
                    this -> transitions . end ());
}

void DFA::delete_transition (int state) noexcept (false)
{
    if (std::find (this -> states . begin (), this -> states . end (), state) == this -> states . end ())
    {
        throw (FaException::State_does_not_exist (state));
    }

    for (std::tuple <int, char, int> transition : this -> transitions)
        if (std::get <0> (transition) == state || std::get <2> (transition) == state)
            this -> transitions . erase (
                    std::remove (this -> transitions . begin (), this -> transitions . end (), transition),
                    this -> transitions . end ());
}

const int &DFA::get_initial_state () const noexcept (false)
{
    return (this -> initial_state);
}

void DFA::set_initial_state (int new_initial_state) noexcept (false)
{
    if (std::find (this -> states . begin (), this -> states . end (), new_initial_state) != this -> states . end ())
    {
        this -> initial_state = new_initial_state;
    }
    else
    {
        throw (FaException::State_does_not_exist (new_initial_state));
    }
}

void DFA::reset_initial_state ()
{
    this -> initial_state = INT_MIN;
}


bool DFA::accepts (std::string input_word) noexcept (false)
{
    int current_state;
    bool found_transition;

    if (get_initial_state () == INT_MIN)
    {
        throw (FaException::Initial_state_not_set ());
    }
    if (get_final_states () . empty ())
    {
        throw (FaException::No_final_states ());
    }

    current_state = this -> get_initial_state ();
    while (input_word . length () != 0)
    {
        found_transition = false;

        for (std::tuple <int, char, int> transition : this -> transitions)
        {
            if (std::find (this -> alphabet . begin (), this -> alphabet . end (), input_word[0]) ==
                this -> alphabet . end ())
            {
                throw (FaException::Character_does_not_exist (input_word[0]));
            }
            if (std::get <0> (transition) == current_state && std::get <1> (transition) == input_word[0])
            {
                found_transition = true;
                current_state = std::get <2> (transition);
                input_word = input_word . substr (1, input_word . length () - 1);
                break;
            }
        }
        if (!found_transition)
            return (false);
    }
    return ((bool) (std::find (this -> final_states . begin (), this -> final_states . end (), current_state) !=
                    this -> final_states . end ()));
}

void DFA::display ()
{
    std::cout << "[DEBUG DISPLAY]" << std::endl;
    std::cout << "States: ";
    for (int state : this -> get_states ())
        std::cout << state << " ";
    std::cout << std::endl;

    std::cout << "Alphabet: ";
    for (char character : this -> get_alphabet ())
        std::cout << character << " ";
    std::cout << std::endl;

    std::cout << "Final States: ";
    for (int final_state : this -> get_final_states ())
        std::cout << final_state << " ";
    std::cout << std::endl;

    std::cout << "Initial State: "
              << (this -> get_initial_state () == INT_MIN ? "Not set" : std::to_string (this -> get_initial_state ()))
              << std::endl;

    std::cout << "Transitions:" << std::endl;
    for (std::tuple <int, char, int> transition : this -> get_transitions ())
        std::cout << "(" << std::get <0> (transition) << ", '" << std::get <1> (transition) << "', "
                  << std::get <2> (transition) << ")" << std::endl;
    std::cout << "[END DEBUG DISPLAY]" << std::endl << std::endl;
}

void DFA::reset ()
{
    this -> states . clear ();
    this -> final_states . clear ();
    this -> alphabet . clear ();
    this -> transitions . clear ();
    this -> initial_state = INT_MIN;
}
