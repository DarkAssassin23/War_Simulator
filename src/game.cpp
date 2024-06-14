#include <iostream>

#include "card.h"
#include "game.h"

#define TURN_LIMIT 10000

Game::Game(void)
{
    deck.dealCards(player1, player2);
    draw = false;
    sim = true;
}

Game::Game(Deck &d, Player &p1, Player &p2, bool simulate)
    : deck(d), player1(p1), player2(p2), draw(false), sim(simulate)
{
    deck.dealCards(player1, player2);
}

Game::Game(Player &p1, Player &p2, bool simulate)
    : player1(p1), player2(p2), draw(false), sim(simulate)
{
}

void Game::play(void)
{
    int count = 1;

    while ((!player1.outOfCards() && !player2.outOfCards()) && !draw)
    {
        takeTurn(count);
        if (count % 350)
        {
            player1.shuffleHand();
            player2.shuffleHand();
        }

        if (count > TURN_LIMIT)
            draw = true;
    }
    if (draw)
        std::cout << "Game Over: Draw\n";
    else if (!player1.outOfCards())
        std::cout << "Game Over: Player 1 Wins!\n";
    else if (!player2.outOfCards())
        std::cout << "Game Over: Player 2 Wins!\n";
}

void Game::takeTurn(int &turnNum)
{
    int p1Card = player1.playCard();
    int p2Card = player2.playCard();

    std::cout << "Turn: " << turnNum << "\n"
              << "Cards Played: " << cardToString(p1Card) << ", "
              << cardToString(p2Card) << "\nWinner: ";

    int cards[] = { p1Card, p2Card };

    if (p1Card > p2Card)
    {
        player1.takeWinnings(cards, 2);
        std::cout << "Player 1\n";
    }
    else if (p1Card < p2Card)
    {
        player2.takeWinnings(cards, 2);
        std::cout << "Player 2\n";
    }
    else
    {
        std::cout << "Tie, It's War!!\n";
        if (player1.getHandSize() == 0 && player2.getHandSize() == 0)
            draw = true;
        else if (player1.getHandSize() == 0)
        {
            player2.takeWinnings(cards, 2);
            std::cout << "Player 2 Wins\n";
        }
        else if (player2.getHandSize() == 0)
        {
            player1.takeWinnings(cards, 2);
            std::cout << "Player 1 Wins\n";
        }
        else
            war(cards, 2);
    }
    std::cout << "Cards Remaining:\n";
    std::cout << "    Player 1: " << player1.getHandSize() << "\n";
    std::cout << "    Player 2: " << player2.getHandSize() << "\n";
    turnNum++;
    if (!sim)
        std::cin.get();
}

void Game::war(int *cards, size_t numCards)
{
    std::queue<int> winningsPot;
    for (int x = 0; x < (int) numCards; x++)
    {
        winningsPot.push(cards[x]);
    }

    int p1Card = 0;
    int p2Card = 0;

    while (p1Card == p2Card)
    {
        int range = (int) cardsToWar(player1.getHandSize(),
                                     player2.getHandSize());
        for (int x = 0; x < range - 1; x++)
        {
            winningsPot.push(player1.playCard());
            winningsPot.push(player2.playCard());
        }

        p1Card = player1.playCard();
        p2Card = player2.playCard();

        std::cout << "Cards Played: " << cardToString(p1Card) << ", "
                  << cardToString(p2Card) << "\nWinner: ";

        winningsPot.push(p1Card);
        winningsPot.push(p2Card);

        size_t potSize = winningsPot.size();
        int *cardWinnings;
        try
        {
            cardWinnings = new int[potSize];
        }
        catch (const std::bad_alloc &e)
        {
            std::cout << "Memory Allocation failed: " << e.what()
                      << "\nAborting...\n";
            exit(-1);
        }

        convertWinningsToArray(winningsPot, cardWinnings);
        if (p1Card > p2Card)
        {
            player1.takeWinnings(cardWinnings, potSize);
            std::cout << "Player 1\n";
        }
        else if (p1Card < p2Card)
        {
            player2.takeWinnings(cardWinnings, potSize);
            std::cout << "Player 2\n";
        }
        else
        {
            std::cout << "Tie, It's War!!\n";
            if (player1.getHandSize() == 0 && player2.getHandSize() == 0)
            {
                draw = true;
                break;
            }
            else if (player1.getHandSize() == 0)
            {
                player2.takeWinnings(cardWinnings, potSize);
                std::cout << "Player 2 Wins War\n";
                p1Card = -1;
            }
            else if (player2.getHandSize() == 0)
            {
                player1.takeWinnings(cardWinnings, potSize);
                std::cout << "Player 1 Wins War\n";
                p2Card = -1;
            }
        }
        delete[] cardWinnings;
    }
}

size_t Game::cardsToWar(size_t p1Cards, size_t p2Cards)
{
    size_t p1p2min = std::min(p1Cards, p2Cards);
    return std::min(p1p2min, static_cast<unsigned long>(4));
}

void Game::convertWinningsToArray(std::queue<int> winningsPot, int *cards)
{
    int index = 0;
    while (!winningsPot.empty())
    {
        cards[index] = winningsPot.front();
        winningsPot.pop();
        index++;
    }
}