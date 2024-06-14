#pragma once
#include <queue>

#include "deck.h"

/// @class Game
/// @brief Class containing the came logic for War
class Game
{
  public:
    /// @brief Default constructor
    Game(void);

    /// @brief Create the game given a deck and two players
    /// @param d The Deck of Cards to use
    /// @param p1 The first player
    /// @param p2 The second player
    /// @param simulate Should the Game be played simulated (default: true)
    Game(Deck &d, Player &p1, Player &p2, bool simulate = true);

    /// @brief Create the game given two players
    /// @param p1 The first player
    /// @param p2 The second player
    /// @param simulate Should the Game be played simulated (default: true)
    Game(Player &p1, Player &p2, bool simulate = true);

    /// @brief Play the game, simulating all the turns until one player wins
    void play();

  private:
    void takeTurn(int &turnNum);

    /// @brief If both players put down the same card the go to war
    ///
    /// In the event both players put down the same card (e.g. 4) they keep
    /// putting cards down (in groups of 3) and playing the fourth card until
    /// the tie is broken, and the winner takes all the cards
    /// @param cards Array of cards currently down
    /// @param numCards The number of cards currently a part of the war
    void war(int *cards, size_t numCards);

    /// @brief Make sure the Players have enough cards for war
    /// @param p1Cards The number of Cards Player 1 has
    /// @param p2Cards The number of Cards Player 2 has
    /// @return The number of Cards each player will put down
    size_t cardsToWar(size_t p1Cards, size_t p2Cards);

    /// @brief Add the Cards won from the war to the Players hand
    /// @param winningsPot The queue of all the cards put down during the war
    /// @param cards The Players had that the cards should be added to
    void convertWinningsToArray(std::queue<int> winningsPot, int *cards);

    Deck deck;      //!< The Deck of Cards used in the game
    Player player1; //!< The first player
    Player player2; //!< The second player
    bool draw;      //!< Is the game a tie?
    bool sim;       //!< Simulate the whole game
};