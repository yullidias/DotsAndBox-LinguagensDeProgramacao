#include "player.h"


Player::Player(int n, QColor c, bool t) : number(n), color(c), turn(t), total_boxes(0) {
}

int Player::getNumber(){ return number; }
QColor Player::getColor(){ return color; }
int Player::getTurn(){ return turn; }
int Player::getTotalBoxes(){ return total_boxes; }
void Player::setTurn(bool value){ turn=value; }
void Player::incrementTotalBoxes(){ total_boxes+=1; }
void Player::reset() { total_boxes=0; }
