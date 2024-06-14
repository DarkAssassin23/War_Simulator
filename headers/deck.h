#pragma once
#include <cstdint>

#include "player.h"

#define NUM_JOKERS 2
#define DECK_SIZE (52 + NUM_JOKERS)

/// @class Deck
/// @brief Class to hold all of the Cards that make up a deck of cards
class Deck
{
  public:
    /// @brief Default constructor
    Deck(void);

    /// @brief Give each player their cards
    /// @param p1 The first player
    /// @param p2 The second player
    void dealCards(Player &p1, Player &p2);

    /// @brief Randomize the order of the cards in the deck
    void shuffle(void);

    /// @brief Be a no good cheater and rig the Deck for Player 1
    ///
    /// Rigs the deck for Player 1 so they have both Jockers
    /// @note Should be called at the beginning when both Players have the
    /// same number of cards
    /// @param p1 The Player we are rigging the Deck for
    /// @param p2 The Player who the Game's being rigged against
    void rigDeck(Player &p1, Player &p2);

    /// @brief Print the contents of the deck to the console
    void printDeck(void);

  private:
    /// @brief Initialize the deck with its cards
    void initDeck(void);

    uint8_t deck[DECK_SIZE];
};