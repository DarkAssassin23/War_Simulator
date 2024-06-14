#pragma once
#include <cstdint>
#include <queue>

/// @class Player
/// @brief Collection of data and actions a Player will use during War
class Player
{
  public:
    /// @brief Default constructor
    Player(void){};

    /// @brief Add a single card to the Player's hand.
    /// @param card The card to be added to the Player's hand
    void addToHand(int card);

    /// @brief Add the winnings that were just won to the Player's hand
    /// @param cards The array of Cards won
    /// @param numCards The number of Cards in the array
    void takeWinnings(int *cards, size_t numCards);

    /// @brief Play the next Card in the Player's hand
    /// @return The value of the card
    int playCard(void);

    /// @brief Check if the Player is out of cards
    /// @note Same as emptyHand()
    /// @see emptyHand()
    /// @return If the Player is out of Cards
    bool outOfCards(void);

    /// @brief Check if the Players hand is empty
    /// @note Same as outOfCards()
    /// @see outOfCards()
    /// @return If the Player's hand is empty
    bool emptyHand(void);

    /// @brief Shuffle the Cards that the Player has in their hand
    void shuffleHand(void);

    /// @brief Get how many Cards the Player has left in their hand
    /// @return Number of cards left in the Player's hand
    int getHandSize(void);

  private:
    std::queue<uint8_t> hand;
};