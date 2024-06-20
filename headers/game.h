#pragma once
#include <queue>

#include "deck.h"

/// @enum GameResult
/// @brief Possible results from a Game
enum GameResult
{
    GAME_RESULT_TIE = 0,
    GAME_RESULT_P1_W = 1,
    GAME_RESULT_P2_W = 2
};

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
    /// @param v Should the Game run in verbose mode (default: true)
    Game(Deck &d, Player &p1, Player &p2, bool simulate = true, bool v = true);

    /// @brief Create the game given two players
    /// @param p1 The first player
    /// @param p2 The second player
    /// @param simulate Should the Game be played simulated (default: true)
    /// @param v Should the Game run in verbose mode (default: true)
    Game(Player &p1, Player &p2, bool simulate = true, bool v = true);

    /// @brief Play the game, simulating all the turns until one player wins
    void play(void);

    /// @brief Get the winner of the game
    /// @return 1 for Player 1; 2 for Player 2
    int getWinner(void);

  private:
    /// @brief Perform a single turn with each player playing their top card
    ///
    /// Each player lays down their card. If they are the same they go to
    /// war until one player runs out of cards or one player wins
    /// @param turnNum The counter for what turn of the game is on
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
    bool verbose;   //!< Print out turn-by-turn info
};
