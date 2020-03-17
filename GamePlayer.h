//
// Created by ilong on 2020/3/17.
//

#ifndef EFFECTIVE_C_GAMEPLAYER_H
#define EFFECTIVE_C_GAMEPLAYER_H

#include <string>
#include <stdlib.h>

constexpr double AspectRatio = 1.653;

const  char * const authorName = "Scott Meyers";

const std::string authorNameStr = "Scott Meyers";


class GamePlayer {
private:
    enum{NumTurns = 5};
    int scores[NumTurns];
};

class CostEstimate{
private:
    static const double FudgeFactor;
};

#endif //EFFECTIVE_C_GAMEPLAYER_H
