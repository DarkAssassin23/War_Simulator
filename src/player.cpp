#include <iostream>

#include "card.h"
#include "player.h"

void Player::addToHand(int card)
{
    hand.push((uint8_t) card);
}

void Player::shuffleHand(void)
{
    int size = (int) hand.size();
    uint8_t *cards;
    try
    {
        cards = new uint8_t[size];
    }
    catch (const std::bad_alloc &e)
    {
        std::cout << "Memory Allocation failed: " << e.what()
                  << "\nAborting...\n";
        exit(-1);
    }

    int index = 0;
    while (!hand.empty())
    {
        cards[index] = hand.front();
        hand.pop();
        index++;
    }

    for (int x = 0; x < size; x++)
    {
        int temp = cards[x];
        int randNum = genRandomNum(0, size - 1);
        cards[x] = cards[randNum];
        cards[randNum] = temp;
    }

    for (int x = 0; x < size; x++)
        addToHand(cards[x]);
    delete[] cards;
}

void Player::takeWinnings(int *cards, size_t numCards)
{
    for (int x = 0; x < (int) numCards; x++)
        addToHand(cards[x]);
}

bool Player::emptyHand(void)
{
    return hand.empty();
}

bool Player::outOfCards(void)
{
    return hand.empty();
}

int Player::playCard(void)
{
    int card = hand.front();
    hand.pop();
    return card;
}

int Player::getHandSize(void)
{
    return hand.size();
}