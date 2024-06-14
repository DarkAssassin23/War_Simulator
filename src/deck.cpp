#include <iostream>

#include "card.h"
#include "deck.h"

Deck::Deck(void)
{
    initDeck();
    shuffle();
}

void Deck::initDeck(void)
{
    int count = 0;
    for (int cardVal = 2; cardVal <= ACE; cardVal++)
    {
        for (int x = 0; x < 4; x++)
        {
            deck[count] = cardVal;
            count++;
        }
    }
    for (int x = 0; x < NUM_JOKERS; x++)
    {
        deck[count] = JOKER;
        count++;
    }
}

void Deck::shuffle(void)
{
    for (int x = 0; x < DECK_SIZE; x++)
    {
        int temp = deck[x];
        int randNum = genRandomNum(0, DECK_SIZE - 1);
        deck[x] = deck[randNum];
        deck[randNum] = temp;
    }
}

void Deck::printDeck(void)
{
    for (int x = 0; x < DECK_SIZE; x++)
    {
        if ((x + 1) == DECK_SIZE)
            std::cout << cardToString(deck[x]);
        else
            std::cout << cardToString(deck[x]) << ", ";
    }
    std::cout << "\n";
}

void Deck::dealCards(Player &p1, Player &p2)
{
    for (int x = 0; x < DECK_SIZE; x++)
    {
        if (x % 2 == 0)
            p1.addToHand(deck[x]);
        else
            p2.addToHand(deck[x]);
    }
}

void Deck::rigDeck(Player &p1, Player &p2)
{
    int size = p1.getHandSize();
    uint8_t *p1Hand, *p2Hand;
    try
    {
        p1Hand = new uint8_t[size];
        p2Hand = new uint8_t[size];
    }
    catch (const std::bad_alloc &e)
    {
        std::cout << "Memory Allocation failed: " << e.what()
                  << "\nAborting...\n";
        exit(-1);
    }

    int index = 0;
    while (!p1.emptyHand())
    {
        p1Hand[index] = p1.playCard();
        p2Hand[index] = p2.playCard();

        // Swap Joker to player 1's hand
        if (p2Hand[index] == JOKER)
        {
            p2Hand[index] = p1Hand[index];
            p1Hand[index] = JOKER;
        }
        index++;
    }

    for (int x = size - 1; x >= 0; x--)
    {
        p1.addToHand(p1Hand[x]);
        p2.addToHand(p2Hand[x]);
    }
    delete[] p1Hand;
    delete[] p2Hand;
}