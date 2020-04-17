//
// Created by lblaga on 17.04.2020.
//

#ifndef DFA_FAEXCEPTIONS_H
#define DFA_FAEXCEPTIONS_H

#include <exception>

#include <string>
#include <climits>

namespace FaException
{
    class FaException : public std::exception
    {
    protected:
        FaException () = default;

        std::string message;
    public:

        ~FaException () override = default;

        const char *what () const noexcept (true) override;
    };


    class State_exception : public FaException
    {
    protected:
        int state = INT_MIN;

    public:
        int get_state () const;
    };

    class State_already_exists : public State_exception
    {
    public:
        explicit State_already_exists (int state);
    };

    class State_already_final : public State_exception
    {
    public:
        explicit State_already_final (int state);
    };

    class State_does_not_exist : public State_exception
    {
    public:
        explicit State_does_not_exist (int state);
    };

    class Initial_state_not_set : public State_exception
    {
    private:
        using State_exception::state;
        using State_exception::get_state;

    public:
        Initial_state_not_set ();
    };

    class No_final_states : public State_exception
    {
    private:
        using State_exception::state;
        using State_exception::get_state;

    public:
        No_final_states ();
    };

    class State_is_not_final : public State_exception
    {
    public:
        explicit State_is_not_final (int state);
    };


    class Character_exception : public FaException
    {
    protected:
        char character;

    public:
        char get_character () const;
    };

    class Character_already_exists : public Character_exception
    {
    public:
        explicit Character_already_exists (char character);
    };

    class Character_does_not_exist : public Character_exception
    {
    public:
        explicit Character_does_not_exist (char character);
    };


    class Transition_exception : public FaException
    {
    protected:
        int start_state;
        char transition_character;
        int end_state;

    public:
        int get_start_state () const;

        char get_transition_character () const;

        int get_end_state () const;
    };

    class Transition_already_exists : public Transition_exception
    {
    public:
        Transition_already_exists (int start_state, char transition_character, int end_state);
    };

    class Transition_does_not_exist : public Transition_exception
    {
    public:
        Transition_does_not_exist (int start_state, char transition_character, int end_state);
    };

    class Transition_with_character_already_exists : public Transition_exception
    {
    private:
        using Transition_exception::get_end_state;
        using Transition_exception::end_state;

    public:
        Transition_with_character_already_exists (int start_state, char transition_character);
    };
}

#endif //DFA_FAEXCEPTIONS_H
