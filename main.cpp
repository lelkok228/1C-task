#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <chrono>
#include <algorithm>

std :: mt19937 rd(std :: chrono :: system_clock :: now().time_since_epoch().count());

const int NUMBER_OF_STACKS = 8;
const int NUMBER_OF_CARD_VALUES = 9;

int get_number_of_consecutive_cards(const std::vector<int>& stack, int number_of_last_closed_card_) {
    if (stack.empty()) {
        return 0;
    }

    int number_of_consecutive_cards = 1;
    for (int i = static_cast<int>(stack.size()) - 2; i >= 0 && i > number_of_last_closed_card_ && stack[i] == stack[i + 1] + 1; ++number_of_consecutive_cards, --i) {}
}

class StackOfCards {
public:
    StackOfCards(std::string stack) {
        stack += " ";
        size_t beginning_of_new_card = 0;
        for (size_t i = 0; i < stack.size(); ++i) {
            if (stack[i] == ' ') {
                std::string card = stack.substr(beginning_of_new_card, i - beginning_of_new_card);
                if (card == "A") {
                    stack_.push_back(14);
                } else if (card == "K") {
                    stack_.push_back(13);
                } else if (card == "Q") {
                    stack_.push_back(12);
                } else if (card == "J") {
                    stack_.push_back(11);
                } else {
                    stack_.push_back(stoi(card));
                }

                beginning_of_new_card = i + 1;
            }
        }

        number_of_last_closed_card_ = static_cast<int>(stack_.size()) - 2;
    }

    int HowManyCardsCanBeTransferedTo(const StackOfCards& to) const {
        if (stack_.empty()) {
            return 0;
        }
        if (to.stack_.empty()) {
            return get_number_of_consecutive_cards(stack_, number_of_last_closed_card_);
        }

        bool can_remove_cards_starting_ith = true;
        for (int i = stack_.size() - 1; i >= 0 && i > number_of_last_closed_card_ && can_remove_cards_starting_ith; --i) {
            if (i != stack_.size() - 1) {
                can_remove_cards_starting_ith = (stack_[i] == stack_[i + 1] + 1);
            }
            if (stack_[i] == to.stack_.back() - 1) {
                return stack_.size() - i;
            }
        }

        return 0;
    }

    void TranserTo(StackOfCards& to, int number_of_transfered_card) {
        for (int i = stack_.size() - number_of_transfered_card; i < stack_.size(); ++i) {
            to.stack_.push_back(stack_[i]);
        }
        for (int i = 0; i < number_of_transfered_card; ++i) {
            stack_.pop_back();
        }
        number_of_last_closed_card_ = std::min(number_of_last_closed_card_, static_cast<int>(stack_.size()) - 2);
        to.RemoveCardsIfPossible_();
    }

    bool IsEmpty() const {
        return stack_.empty();
    }

private:
    void RemoveCardsIfPossible_() {
        if (stack_.empty() || stack_.back() != 6) {
            return;
        }

        int number_of_consecutive_cards = get_number_of_consecutive_cards(stack_, number_of_last_closed_card_);

        if (number_of_consecutive_cards == NUMBER_OF_CARD_VALUES) {
            for (int i = 0; i < number_of_consecutive_cards; ++i) {
                stack_.pop_back();
            }
            number_of_last_closed_card_ = std::min(number_of_last_closed_card_, static_cast<int>(stack_.size()) - 2);
        }
    }

    std::vector<int> stack_;
    int number_of_last_closed_card_;
};

class SpiderSolitaire {
public:
    void AddStack(const std::string& stack) {
        stacks_.push_back(StackOfCards(stack));
    }

    bool IsSolved() {
        RemoveAsManyCardsAsPossible_();
        for (int i = 0; i < stacks_.size(); ++i) {
            if (!stacks_[i].IsEmpty()) {
                return false;
            }
        }
        return true;
    }

private:
    void RemoveAsManyCardsAsPossible_() {
        for (int number_of_moves = 0; number_of_moves < MAX_NUMBER_OF_MOVES_; ++number_of_moves) {
            int from_id = rd() % stacks_.size();
            int to_id = rd() % stacks_.size();
            if (from_id == to_id) {
                continue;
            }

            int number_of_transfered_card = stacks_[from_id].HowManyCardsCanBeTransferedTo(stacks_[to_id]);
            stacks_[from_id].TranserTo(stacks_[to_id], number_of_transfered_card);
        }
    }

    std::vector<StackOfCards> stacks_;
    static const int MAX_NUMBER_OF_MOVES_ = 100000;
};

int main() {
    SpiderSolitaire spider_solitaire;

    for (int i = 0; i < NUMBER_OF_STACKS; ++i) {
        std::string stack;
        std::getline(std::cin, stack);
        spider_solitaire.AddStack(stack);
    }

    if (spider_solitaire.IsSolved()) {
        std::cout << "All cards can be removed.\n";
    } else {
        std::cout << "Failed to remove all cards.\n";
    }

    return 0;
}