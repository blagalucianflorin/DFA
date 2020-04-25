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
    bool found_transition;

    if (get_initial_state () == INT_MIN)
    {
        throw (FaException::Initial_state_not_set ());
    }
    if (get_final_states () . empty ())
    {
        throw (FaException::No_final_states ());
    }

    current_states . push_back (this -> get_initial_state ());
    while ((input_word . length () != 0 || current_states != old_states) && !current_states . empty ())
    {
        found_transition = false;
        old_states = current_states;

        current_size = current_states . size ();
        for (int i = 0; i < current_size; i++)
            for (int new_state : lambda_closure (current_states[i]))
                if (std::count (current_states . begin (), current_states . end (), new_state) == 0)
                    current_states . push_back (new_state), found_transition = true;

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
                        current_states . push_back (new_state), found_transition = true;
        }

        current_size = current_states . size ();
        for (int i = 0; i < current_size; i++)
            for (int new_state : lambda_closure (current_states[i]))
                if (std::count (current_states . begin (), current_states . end (), new_state) == 0)
                    current_states . push_back (new_state), found_transition = true;

        if (input_word . length () != 0)
        {
            if (!found_transition)
                return false;
            input_word = input_word . substr (1, input_word . length () - 1);
        }
        std::sort (current_states . begin (), current_states . end ());
    }

    for (int i : current_states)
        for (int j : this -> get_final_states ())
            if (i == j)
                return (true);
    return (false);
}

DFA &LNFA::to_DFA ()
{
    if (this -> get_initial_state () == INT_MIN)
    {
        throw (FaException::Initial_state_not_set ());
    }
    if (this -> get_final_states () . empty ())
    {
        throw (FaException::No_final_states ());
    }

    auto ret_dfa = new DFA ();
    std::vector <int> DFA_states;
    std::vector <int> DFA_final_states;
    std::vector <std::tuple <int, char, int>> DFA_transitions;
    int DFA_initial_state;

    std::vector <std::vector <std::set <int>>> conversion_table;
    std::vector <std::set <int>> new_row;
    std::set <int> new_cell;
    std::set <std::set <int>> all_cells_set;
    std::vector <std::set <int>> cells_queue;
    std::set <int> curr_state_cell;
    std::vector <std::vector <int>> DFA_table;
    std::vector <int> DFA_table_row;
    std::set <std::pair <std::set <int>, int>> new_state_numbers_set;
    std::set <int> DFA_final_states_set;
    int new_state_number;

    // Generate the first row of the table
    DFA_initial_state = 0;
    new_state_number = 0;
    for (int curr_state : lambda_closure (this -> get_initial_state ()))
        new_cell . insert (curr_state);
    new_row . push_back (new_cell);
    all_cells_set . insert (new_cell);
    new_state_numbers_set . insert (std::make_pair (new_cell, new_state_number));
    new_state_number++;
    for (char curr_character : this -> get_alphabet ())
    {
        new_cell . clear ();
        for (int curr_state : new_row[0])
            for (int curr_state2 : delta (curr_state, curr_character))
                new_cell . insert (curr_state2);

        for (int curr_state : new_cell)
            for (int curr_state2 : lambda_closure (curr_state))
                new_cell . insert (curr_state2);

        new_row . push_back (new_cell);
        if (!new_cell . empty ())
        {
            if (all_cells_set . find (new_cell) == all_cells_set . end ())
            {
                cells_queue . push_back (new_cell);
                new_state_numbers_set . insert (std::make_pair (new_cell, new_state_number));
                new_state_number++;
            }
            all_cells_set . insert (new_cell);
        }
    }
    conversion_table . push_back (new_row);

    // Generate the rest of the table

    // While new state groups were found
    while (!cells_queue . empty ())
    {
        new_row . clear ();
        curr_state_cell = cells_queue[0];
        cells_queue . erase (cells_queue . begin ());
        if (!curr_state_cell . empty ())
        {
            new_row . push_back (curr_state_cell);

            for (char curr_character : this -> get_alphabet ())
            {
                new_cell . clear ();

                for (int curr_state : curr_state_cell)
                    for (int curr_state2 : this -> delta (curr_state, curr_character))
                        new_cell . insert (curr_state2);

                for (int curr_state : new_cell)
                    for (int curr_state2 : lambda_closure (curr_state))
                        new_cell . insert (curr_state2);

                if (!new_cell . empty ())
                {
                    if (all_cells_set . find (new_cell) == all_cells_set . end ())
                    {
                        cells_queue . push_back (new_cell);
                        new_state_numbers_set . insert (std::make_pair (new_cell, new_state_number));
                        new_state_number++;
                    }
                    all_cells_set . insert (new_cell);
                }

                new_row . push_back (new_cell);
            }
            conversion_table . push_back (new_row);
        }
    }

    // Assign new names (a single number) for the obtained state groups
    for (std::vector <std::set <int>> &row : conversion_table)
    {
        DFA_table_row . clear ();
        for (std::set <int> &cell : row)
        {
            if (!cell . empty ())
            {
                for (const std::pair <std::set <int>, int> &new_state_number_cell : new_state_numbers_set)
                    if (new_state_number_cell . first == cell)
                    {
                        DFA_table_row . push_back (new_state_number_cell . second);
                        break;
                    }
            }
            else
                DFA_table_row . push_back (-1);
        }
        DFA_table . push_back (DFA_table_row);
    }

    // Add the newly obtained states to the DFA
    DFA_states . reserve (new_state_numbers_set . size ());
    for (const std::pair <std::set <int>, int> &new_state_number_cell : new_state_numbers_set)
        DFA_states . push_back (new_state_number_cell . second);

    // Add the final states to the DFA
    for (const std::set <int> &curr_cell : all_cells_set)
        for (int curr_state : curr_cell)
            for (int curr_final_state : this -> get_final_states ())
                if (curr_state == curr_final_state)
                    for (const std::pair <std::set <int>, int> &new_state_number_cell : new_state_numbers_set)
                        if (new_state_number_cell . first == curr_cell)
                        {
                            DFA_final_states_set . insert (new_state_number_cell . second);
                            break;
                        }
    DFA_final_states . reserve (DFA_final_states_set . size ());
    for (int curr_state : DFA_final_states_set)
        DFA_final_states . push_back (curr_state);

    // Add the new transitions to the DFA
    for (auto &i : DFA_table)
        for (int j = 1; j < i . size (); j++)
            if (i[j] != -1)
                DFA_transitions . emplace_back (i[0], this -> get_alphabet ()[j - 1], i[j]);

    // Build the return DFA
    ret_dfa -> add_state (DFA_states);
    ret_dfa -> add_character (this -> get_alphabet ());
    ret_dfa -> add_final_state (DFA_final_states);
    ret_dfa -> set_initial_state (DFA_initial_state);
    for (std::tuple <int, char, int> transition : DFA_transitions)
        ret_dfa -> add_transition (std::get <0> (transition), std::get <1> (transition), std::get <2> (transition));

    return (*ret_dfa);
}

