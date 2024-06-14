#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

#include "card.h"
#include "deck.h"
#include "game.h"
#include "player.h"

std::string strLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return s;
}

int main(int argc, char **argv)
{
    bool simulated = true, rigged = false;
    int rounds = 1;

    for (int x = 1; x < argc; x++)
    {
        std::string arg = strLower(argv[x]);
        if (arg == "-m")
            simulated = false;
        else if (arg == "-r")
            rigged = true;
        else if (arg == "-s")
        {
            if ((x + 1) == argc)
            {
                printf("Error: Missing argument for \'-s\'");
                return 1;
            }
            int tmp = std::stoi(argv[x + 1]);
            rounds = std::max(tmp, rounds);
            x++;
        }
        else if (arg == "-h" || arg == "--help")
        {
            printf("Usage: %s [-m] [-r] [-s sims]\n", argv[0]);
            printf("  -m       Enable manual mode and step through the game "
                   "turn-by-turn\n");
            printf("  -r       Rig the deck in favor of Player 1\n");
            printf("  -s sims  The number of simulations to run\n");
            printf("\n");
            return 0;
        }
    }

    int p1Wins = 0, p2Wins = 0, ties = 0;
    for (int x = 0; x < rounds; x++)
    {
        Player p1, p2;
        Deck d;
        d.dealCards(p1, p2);
        if (rigged)
            d.rigDeck(p1, p2);

        Game g = Game(p1, p2, simulated, (rounds == 1));
        g.play();
        switch (g.getWinner())
        {
            case GAME_RESULT_TIE:
                ties++;
                break;
            case GAME_RESULT_P1_W:
                p1Wins++;
                break;
            case GAME_RESULT_P2_W:
                p2Wins++;
                break;
            default:
                break;
        }
    }
    const int pad = 8;
    printf("%sStats:\n", (rounds == 1) ? "\n" : "");
    printf("%*s%*s%*s%*s\n", pad, "Player", pad, "Wins", pad, "Losses", pad,
           "Ties");
    printf("%*s%*d%*d%*d\n", pad, "Player 1", pad, p1Wins, pad,
           (rounds - p1Wins) - ties, pad, ties);
    printf("%*s%*d%*d%*d\n", pad, "Player 2", pad, p2Wins, pad,
           (rounds - p2Wins) - ties, pad, ties);
    printf("Overall Winner: ");
    if (p1Wins == p2Wins)
        printf("Tie\n");
    else
        printf("%s\n", (p1Wins > p2Wins) ? "Player 1" : "Player 2");

    return 0;
}