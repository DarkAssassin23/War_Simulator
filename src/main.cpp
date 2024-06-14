#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "card.h"
#include "deck.h"
#include "game.h"
#include "player.h"

/// @struct SimResults
/// @brief Struct to hold the Game results from a given threads runs
typedef struct
{
    int p1; //!< Player 1 wins
    int p2; //!< Player 2 wins
    int t;  //!< Ties
} SimResults;
std::vector<SimResults> sr;

/// @brief Convert the given string to lower case and return the result
/// @param s The string to convert to lower case
/// @return The string in all lower case
std::string strLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return s;
}

/// @brief The main sim loop for running games of war
/// @param simulated Should the Game be simulated or interactive
/// @param rigged Should the Game be rigged for Player 1
/// @param verbose Should a turn-by-turn summary be printed
/// @return The result of the game
int simLoop(bool simulated, bool rigged, bool verbose)
{
    Player p1, p2;
    Deck d;

    d.dealCards(p1, p2);
    if (rigged)
        d.rigDeck(p1, p2);

    Game g = Game(p1, p2, simulated, verbose);
    g.play();

    return g.getWinner();
}

/// @brief Function for threads running the simulation loop
/// @param rigged Should the Game be rigged for Player 1
/// @param sims The number of simulations this thread is running
/// @param id The id of the thread and corresponding SimResults
void threadFunc(bool rigged, int sims, int id)
{
    while (sims-- > 0)
    {
        switch (simLoop(true, rigged, false))
        {
            case GAME_RESULT_TIE:
                sr[id].t++;
                break;
            case GAME_RESULT_P1_W:
                sr[id].p1++;
                break;
            case GAME_RESULT_P2_W:
                sr[id].p2++;
                break;
            default:
                break;
        }
    }
}

/// @brief Create, and start, the threads to run the war simulation loop
/// @param rounds The number of simulations to run
/// @param rigged Should the Game be rigged for Player 1
void startThreads(int rounds, bool rigged)
{
    const auto cores = std::min(rounds,
                                (int) std::thread::hardware_concurrency());
    std::vector<std::thread> threads(cores);
    int perThread = rounds / cores;
    int extra = rounds % cores;

    for (int t = 0; t < (int) cores; t++)
    {
        int sims = perThread;
        if (extra > 0)
        {
            extra--;
            sims++;
        }

        sr.emplace_back(SimResults());
        threads[t] = std::thread(threadFunc, rigged, sims, t);
    }

    for (int t = 0; t < (int) cores; t++)
        threads[t].join();
}

/// @brief Output the results of the War Game(s) to the console
/// @param rounds The number of simulations to run
/// @param p1 Number of wins for Player 1
/// @param p2 Number of wins for Player 2
/// @param t Number of ties
void outputResults(int rounds, int p1, int p2, int t)
{
    const int pad = 8;
    printf("%sStats:\n", (rounds == 1) ? "\n" : "");
    printf("%*s%*s%*s%*s\n", pad, "Player", pad, "Wins", pad, "Losses", pad,
           "Ties");
    printf("%*s%*d%*d%*d\n", pad, "Player 1", pad, p1, pad, (rounds - p1) - t,
           pad, t);
    printf("%*s%*d%*d%*d\n", pad, "Player 2", pad, p2, pad, (rounds - p2) - t,
           pad, t);
    printf("Overall Winner: ");
    if (p1 == p2)
        printf("Tie\n");
    else
        printf("%s\n", (p1 > p2) ? "Player 1" : "Player 2");
}

int main(int argc, char **argv)
{
    bool simulated = true, rigged = false, threadded = false;
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
                printf("Error: Missing argument for \'-s\'\n");
                return 1;
            }
            try
            {
                int tmp = std::stoi(argv[x + 1]);
                rounds = std::max(tmp, rounds);
                x++;
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error: Invalid argument after \'-s\'\n"
                          << e.what() << "\n";
                return 1;
            }
        }
        else if (arg == "-t")
            threadded = true;
        else if (arg == "-h" || arg == "--help")
        {
            printf("Usage: %s [-m] [-r] [-s sims] [-t]\n", argv[0]);
            printf("  -m       Enable manual mode and step through the game "
                   "turn-by-turn\n");
            printf("  -r       Rig the deck in favor of Player 1\n");
            printf("  -s sims  The number of simulations to run\n");
            printf("  -t       Run in multithreaded mode\n");
            printf("\n");
            return 0;
        }
    }

    int p1Wins = 0, p2Wins = 0, ties = 0;
    if (threadded && rounds > 1)
    {
        startThreads(rounds, rigged);
        for (int x = 0; x < (int) sr.size(); x++)
        {
            p1Wins += sr[x].p1;
            p2Wins += sr[x].p2;
            ties += sr[x].t;
        }
    }
    else
    {
        int remaining = rounds;
        while (remaining > 0)
        {
            switch (simLoop(simulated, rigged, (rounds == 1)))
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
            remaining--;
        }
    }

    outputResults(rounds, p1Wins, p2Wins, ties);

    return 0;
}