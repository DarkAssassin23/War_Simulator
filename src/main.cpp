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
    Player p1, p2;
    Deck d;
    bool simulated = true, rigged = false;

    for (int x = 1; x < argc; x++)
    {
        std::string arg = strLower(argv[x]);
        if (arg == "-m")
            simulated = false;
        else if (arg == "-r")
            rigged = true;
        else if (arg == "-h" || arg == "--help")
        {
            printf("Usage: %s [-m] [-r]\n", argv[0]);
            printf("  -m      Enable manual mode and step through the game "
                   "turn-by-turn\n");
            printf("  -r      Rig the deck in favor of Player 1\n");
            printf("\n");
            return 0;
        }
    }

    d.dealCards(p1, p2);
    if (rigged)
        d.rigDeck(p1, p2);

    Game g = Game(p1, p2, simulated);
    g.play();

    return 0;
}