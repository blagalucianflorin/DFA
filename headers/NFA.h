//
// Created by lblaga on 18.04.2020.
//

#ifndef DFA_NFA_H
#define DFA_NFA_H

#include "DFA.h"

class NFA : public DFA
{
protected:
    std::vector <int> delta (int start_state, char transition_character) noexcept (false);

public:
    void add_transition (int start_state, char transition_character, int end_state) noexcept (false) override;

    bool accepts (std::string input_word) noexcept (false) override;
};

#endif //DFA_NFA_H
