#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Random.h"
using namespace std;

bool inBounds(vector<vector<Tile>> &thisSpot, int x, int y) {
    return x >= 0 && y >= 0 && x < thisSpot.size() && y < thisSpot[0].size();
}

void randomMines(vector<int> &thisTile,int area, int numMines) {
    while (thisTile.size() < numMines) {
        int random = Random::Int(0, area);
        if(find(thisTile.begin(), thisTile.end(), random) == thisTile.end()) {
            thisTile.push_back(random);
        }
    }
}

void newBoard(vector<vector<Tile>> &board, int numMines, int height, int width) {
    board.clear();
    int area = height * width;
    for (int i = 0; i < height * 32; i += 32) {
        vector<Tile> tiles;
        for (int j = 0; j < width * 32; j += 32) {
            Tile tile = Tile(j, i);
            tiles.push_back(tile);
        }
        board.push_back(tiles);
    }
    vector<int> thisTile;
    randomMines(thisTile, area, numMines);
    for (int i = 0; i < numMines; i++) {
        int x = thisTile[i] % height;
        int y = thisTile[i] % width;
        board[x][y].setMine(true);
    }
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            board[i][j].setNum(board, i, j);
        }
    }
}

void revealMines(vector<vector<Tile>> &vec, int x, int y) {
    if (inBounds(vec, x, y) && vec[x][y].getNum() == 0
        && !vec[x][y].getClicked() && !vec[x][y].getFlag()) {
        vec[x][y].setClicked();
        revealMines(vec, x - 1, y - 1);
        revealMines(vec, x - 1, y);
        revealMines(vec, x - 1, y + 1);
        revealMines(vec, x, y - 1);
        revealMines(vec, x, y + 1);
        revealMines(vec, x + 1, y - 1);
        revealMines(vec, x + 1, y);
        revealMines(vec, x + 1, y + 1);
    }
    else if (inBounds(vec, x, y) && vec[x][y].getNum() != 0 && vec[x][y].getNum() != -1) {
        vec[x][y].setClicked();
    }
}

void changeBoard(vector<vector<Tile>> &board, int testBoard) {
    string str;
    if (testBoard == 1) {
        str = "boards/testboard1.brd";
    }
    else if (testBoard == 2) {
        str = "boards/testboard2.brd";
    }
    else if(testBoard == 3) {
        str = "boards/testboard3.brd";
    }
    fstream inFile(str, ios_base::in);
    string line;
    vector<vector<string>> allTiles;
    while (getline(inFile, line)) {
        vector<string> tile;
        for (int i = 0; i < line.length(); i++)
            tile.push_back(line.substr(i, 1));
        allTiles.push_back(tile);
    }
    board.clear();
    for (int i = 0; i < 512; i += 32) {
        vector<Tile> tile;
        for (int j = 0; j < 800; j += 32) {
            Tile x = Tile(j, i);
            tile.push_back(x);
        }
        board.push_back(tile);
    }
    for (int i = 0; i < allTiles.size(); i++) {
        for (int j = 0; j < allTiles[0].size(); j++) {
            if (allTiles[i][j].compare("1") == 0)
                board[i][j].setMine(true);
        }
    }
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            board[i][j].setNum(board, i, j);
        }
    }
}

bool checkWin(vector<vector<Tile>> &board, int area) {
    int count = 0;
    int numMines = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j].getClicked())
                count++;
            if (board[i][j].getMine())
                numMines++;
        }
    }
    if (count == (area - numMines)) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * TODO: Random Mines
 */