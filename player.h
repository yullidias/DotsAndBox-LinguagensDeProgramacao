#ifndef PLAYER_H
#define PLAYER_H

#include "qcolor.h"
class Player
{
    private:
        int number;
        QColor color;
        bool turn;
        int total_boxes;

    public:
        Player(int n, QColor c, bool t);
        int getNumber();
        QColor getColor();
        int getTurn();
        int getTotalBoxes();
        void setTurn(bool value);
        void incrementTotalBoxes();
        void reset();

};

#endif // PLAYER_H
