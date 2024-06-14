#include <iostream>
#include <random>

#include "card.h"
using std::mt19937;
using std::uniform_int_distribution;

std::string cardToString(int card)
{
    switch (card)
    {
        case JACK:
            return "Jack";
            break;
        case QUEEN:
            return "Queen";
            break;
        case KING:
            return "King";
            break;
        case ACE:
            return "Ace";
            break;
        case JOKER:
            return "Joker";
            break;
        default:
            return std::to_string(card);
    }
};

int genRandomNum(int lowerBound, int upperBound)
{
    // Sets up the random number generator
    std::random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> genRandom(lowerBound,
                                                             upperBound);

    return genRandom(rng);
};