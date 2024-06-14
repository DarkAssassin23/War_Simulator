#pragma once

#define JACK 11
#define QUEEN 12
#define KING 13
#define ACE 14
#define JOKER 15

/// @brief Convert the cards numerical value to its name
/// @param card The value of the card
/// @return The name of the card (e.g. Card = 11, return value is "Jack")
std::string cardToString(int card);

/// @brief Generate a random card based on the bounds
/// @param lowerBound The minimum numerical value of the card
/// @param upperBound The maximum numerical value of the card
/// @return The value of the card generated
/// @note Distribution in range [lowerBound, upperBound]
int genRandomNum(int lowerBound, int upperBound);
