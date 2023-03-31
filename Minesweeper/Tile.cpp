#include "Tile.h"

bool inBounds(vector<vector<Tile>> &thisSpot, int x, int y);

Tile::Tile(){}

Tile::Tile(int x, int y) {
    this->x = x;
    this->y = y;
    flag = false;
    mine = false;
    clicked = false;
}

int Tile::getX() {
    return x;
}

int Tile::getY() {
    return y;
}

bool Tile::getFlag() {
    return flag;
}

void Tile::setFlag() {
    flag = !flag;
}

void Tile::setFlagX(bool a) {
    flag = a;
}

bool Tile::getMine() {
    return mine;
}
void Tile::setMine(bool a) {
    mine = a;
}

bool Tile::getClicked() {
    return clicked;
}

void Tile::setClicked() {
    clicked = true;
}

void Tile::setNum(vector<vector<Tile>> &thisTile, int i, int j) {
    int count = 0; // number of bombs adjacent
    if (thisTile[i][j].getMine())
        count = -1; // no mines
    else {
        if (inBounds(thisTile, i - 1, j - 1) && thisTile[i - 1][j - 1].getMine()) // top left
            count++;
        if (inBounds(thisTile, i - 1, j) && thisTile[i - 1][j].getMine()) // middle left
            count++;
        if (inBounds(thisTile, i - 1, j + 1) && thisTile[i - 1][j + 1].getMine()) // bottom left
            count++;
        if (inBounds(thisTile, i, j - 1) && thisTile[i][j - 1].getMine()) // top middle
            count++;
        if (inBounds(thisTile, i, j + 1) && thisTile[i][j + 1].getMine()) // bottom middle
            count++;
        if (inBounds(thisTile, i + 1, j - 1) && thisTile[i + 1][j - 1].getMine()) // top right
            count++;
        if (inBounds(thisTile, i + 1, j) && thisTile[i + 1][j].getMine()) // middle right
            count++;
        if (inBounds(thisTile, i + 1, j + 1) && thisTile[i + 1][j + 1].getMine()) // bottom right
            count++;
    }
    num = count;
}

int Tile::getNum() {
    return num;
}