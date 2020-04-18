//
// Created by lblaga on 18.04.2020.
//

#ifndef DFA_LNFA_H
#define DFA_LNFA_H

#include "NFA.h"

/*
 * This implementation uses '#' to mark lambda transitions
 * Change it here if you need to use '#' in your alphabet.
 */
#define lambda '#'

class LNFA : public NFA
{
public:
    std::vector <int> lambda_closure (int start_state) noexcept (false);

    void add_transition (int start_state, char transition_character, int end_state) noexcept (false) override;

    bool accepts (std::string input_word) noexcept (false) override;
};

#endif //DFA_LNFA_H
