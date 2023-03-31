#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Tile {
private:
    int x;
    int y;
    int num;
    string str;
    bool flag;
    bool mine;
    bool clicked;
public:
    Tile();
    Tile(int x, int y);
    int getX();
    int getY();
    bool getFlag();
    void setFlag();
    void setFlagX(bool a);
    bool getMine();
    void setMine(bool a);
    bool getClicked();
    void setClicked();
    void setNum(vector<vector<Tile>> &thisTile, int i, int j);
    int getNum();
};