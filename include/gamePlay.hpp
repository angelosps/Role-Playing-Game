/* file: gamePlay.hpp */

#ifndef __GAMEPLAY_HPP_INCLUDED__
#define __GAMEPLAY_HPP_INCLUDED__

#include "../include/game.hpp"
#include "../include/rndGen.hpp"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

extern std::vector<Hero*> myHeroes;
extern std::vector<Monster*> availableMonsters;

static RndGen rnd1(0,1);
static RndGen rnd3(0,2);
static RndGen rnd5(0,4);
static RndGen rndMAX(0,RAND_MAX);
static RndGen rndMon(0,availableMonsters.size());

void gamePlay(Market *);
#endif