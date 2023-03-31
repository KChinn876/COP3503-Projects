#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Tile.h"
#include "TextureManager.h"
#include "Functions.h"
using namespace std;

int main()
{
    ifstream inFile;
    vector<string> config;
    inFile.open("boards/config.cfg", ios::in);
    if(inFile.is_open()) {
        string line;
        while(getline(inFile, line)) {
            config.push_back(line);
        }
        inFile.close();
    }
    string numRows = config.at(0);
    int width = stoi(numRows);
    string numColumns = config.at(1);
    int height = stoi(numColumns);
    string numMines = config.at(2);
    int mineNum = stoi(numMines);

    sf::RenderWindow window(sf::VideoMode((width * 32), (height * 32) + 100), "Minesweeper");

    unordered_map<string, sf::Texture> textures;

    // Load Hidden Tile
    sf::Texture tileHiddenTexture(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite tileHidden;
    tileHidden.setTexture(tileHiddenTexture);

    // Load Revealed Tile
    sf::Texture tileRevealedTexture(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite tileRevealed;
    tileRevealed.setTexture(tileRevealedTexture);

    // Load Flag
    sf::Texture flagTexture(TextureManager::GetTexture("flag"));
    sf::Sprite flag;
    flag.setTexture(flagTexture);

    // Load Mine
    sf::Texture mineTexture(TextureManager::GetTexture("mine"));
    sf::Sprite mine;
    mine.setTexture(mineTexture);

    // Load Num1
    sf::Texture num1Texture(TextureManager::GetTexture("number_1"));
    sf::Sprite num1;
    num1.setTexture(num1Texture);

    // Load Num2
    sf::Texture num2Texture(TextureManager::GetTexture("number_2"));
    sf::Sprite num2;
    num2.setTexture(num2Texture);

    // Load Num3
    sf::Texture num3Texture(TextureManager::GetTexture("number_3"));
    sf::Sprite num3;
    num3.setTexture(num3Texture);

    // Load Num4
    sf::Texture num4Texture(TextureManager::GetTexture("number_4"));
    sf::Sprite num4;
    num4.setTexture(num4Texture);

    // Load Num5
    sf::Texture num5Texture(TextureManager::GetTexture("number_5"));
    sf::Sprite num5;
    num5.setTexture(num5Texture);

    // Load Num6
    sf::Texture num6Texture(TextureManager::GetTexture("number_6"));
    sf::Sprite num6;
    num6.setTexture(num6Texture);

    // Load Num7
    sf::Texture num7Texture(TextureManager::GetTexture("number_7"));
    sf::Sprite num7;
    num7.setTexture(num7Texture);

    // Load Num8
    sf::Texture num8Texture(TextureManager::GetTexture("number_8"));
    sf::Sprite num8;
    num8.setTexture(num8Texture);

    // Load Debug
    sf::Texture debugTexture(TextureManager::GetTexture("debug"));
    sf::Sprite debug;
    debug.setTexture(debugTexture);

    // Load Test 1
    sf::Texture test1Texture(TextureManager::GetTexture("test_1"));
    sf::Sprite test1;
    test1.setTexture(test1Texture);

    // Load Test 2
    sf::Texture test2Texture(TextureManager::GetTexture("test_2"));
    sf::Sprite test2;
    test2.setTexture(test2Texture);

    // Load Test 3
    sf::Texture test3Texture(TextureManager::GetTexture("test_3"));
    sf::Sprite test3;
    test3.setTexture(test3Texture);

    // Load Happy Face
    sf::Texture happyFaceTexture(TextureManager::GetTexture("face_happy"));
    sf::Sprite happyFace;
    happyFace.setTexture(happyFaceTexture);

    // Load Sad Face
    sf::Texture loseFaceTexture(TextureManager::GetTexture("face_lose"));
    sf::Sprite loseFace;
    loseFace.setTexture(loseFaceTexture);

    // Load Win Face
    sf::Texture winFaceTexture(TextureManager::GetTexture("face_win"));
    sf::Sprite winFace;
    winFace.setTexture(winFaceTexture);

    // Load Digits
//    sf::Texture digitsTexture(TextureManager::GetTexture("digits"));
//    sf::Sprite digits;
//    digits.setTexture(digitsTexture);

    vector<vector<Tile>> board;
    newBoard(board, mineNum, height, width);
    bool lose = false;
    bool debugMode = false;
    while (window.isOpen()) {
        sf::Event event;
        window.clear();


// Keep all drawings below here

        happyFace.setPosition(((width / 2) - 1) * 32,(height * 32));
        window.draw(happyFace);
        if(height < 16  && width < 22) {
            debug.setPosition(happyFace.getPosition().x + 64, happyFace.getPosition().y);
        }
        else {
            debug.setPosition(happyFace.getPosition().x + 128,happyFace.getPosition().y);
        }
        window.draw(debug);
        test1.setPosition(debug.getPosition().x + 64,happyFace.getPosition().y);
        window.draw(test1);
        test2.setPosition(test1.getPosition().x + 64,happyFace.getPosition().y);
        window.draw(test2);
        test3.setPosition(test2.getPosition().x + 64, happyFace.getPosition().y);
        window.draw(test3);

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                int x = board[i][j].getX();
                int y = board[i][j].getY();
                tileHidden.setPosition(x, y);
                window.draw(tileHidden);
            }
        }

        while (window.pollEvent(event)){

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    int i = (x + 1) / 32;
                    int j = (y + 1) / 32;
                    if(!board[j][i].getClicked()) {
                        board[j][i].setFlag();
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;

                    int i = (x + 1) / 32;
                    int j = (y + 1) / 32;
                    if (inBounds(board,j,i) && board[j][i].getFlag()) {
                        break;
                    }
                    if(!lose) {
                        revealMines(board, j, i);
                    }
                    if (inBounds(board, j, i) && board[j][i].getMine()) { // Click on tile with mine
                        debugMode = true;
                        lose = true;
                    }
                    if (x >= debug.getPosition().x && x <= debug.getPosition().x + 64 &&
                        y >= debug.getPosition().y && y <= debug.getPosition().y + 64) { // Click debug button
                        debugMode = !debugMode;
                    }
                    if (x >= test1.getPosition().x && x <= test1.getPosition().x + 64 &&
                        y >= test1.getPosition().y && y <= test1.getPosition().y + 64) { // Click Test 1 button
                        changeBoard(board, 1);
                        debugMode = true;
                    }

                    if (x >= test2.getPosition().x && x <= test2.getPosition().x + 64 &&
                        y >= test2.getPosition().y && y <= test2.getPosition().y + 64) { // Click Test 2 button
                        changeBoard(board, 2);
                        debugMode = true;
                    }

                    if (x >= test3.getPosition().x && x <= test3.getPosition().x + 64 &&
                        y >= test3.getPosition().y && y <= test3.getPosition().y + 64) { // Click Test 3 button
                        changeBoard(board, 3);
                        debugMode = true;
                    }

                    if (x >= happyFace.getPosition().x && x <= happyFace.getPosition().x + 64 &&
                        y >= happyFace.getPosition().y && y <= happyFace.getPosition().y + 64) { // Click Happy/Sad/Win Face
                        if (lose) {
                            lose = false;
                            debugMode = false;
                        }
                        newBoard(board, mineNum, height, width);
                    }
                }
            }
        }

        int countFlags = 0;
        int countMines = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                int x = board[i][j].getX();
                int y = board[i][j].getY();
                if (lose) {
                    board[i][j].setFlagX(false);
                }
                if (board[i][j].getFlag()) {
                    flag.setPosition(x,y);
                    window.draw(flag);
                    countFlags++;
                }
                if (board[i][j].getMine()) {
                    mine.setPosition(x, y);
                    if (debugMode) {
                        tileRevealed.setPosition(x, y);
                        window.draw(tileRevealed);
                        window.draw(mine);
                    }
                    countMines++;
                }
            }
        }

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j].getClicked()) {
                    int adjacentMines = board[i][j].getNum();
                    int x = board[i][j].getX();
                    int y = board[i][j].getY();
                    tileRevealed.setPosition(x, y);
                    window.draw(tileRevealed);
                    if (adjacentMines == 1) {
                        num1.setPosition(x, y);
                        window.draw(num1);
                    }
                    if (adjacentMines == 2) {
                        num2.setPosition(x, y);
                        window.draw(num2);
                    }
                    if (adjacentMines == 3) {
                        num3.setPosition(x, y);
                        window.draw(num3);
                    }
                    if (adjacentMines == 4) {
                        num4.setPosition(x, y);
                        window.draw(num4);
                    }
                    if (adjacentMines == 5) {
                        num5.setPosition(x, y);
                        window.draw(num5);
                    }
                    if (adjacentMines == 6) {
                        num6.setPosition(x, y);
                        window.draw(num6);
                    }
                    if (adjacentMines == 7) {
                        num7.setPosition(x, y);
                        window.draw(num7);
                    }
                    if (adjacentMines == 8) {
                        num8.setPosition(x, y);
                        window.draw(num8);
                    }
                }
            }
        }
 // Say the number of bombs is 50

        int counterNumber = countMines - countFlags;
        //123
        int onesPlace = counterNumber % 10;
        if(onesPlace < 0)
            onesPlace *= -1;
        int tensPlace = (counterNumber / 10) % 10;
        if(tensPlace < 0)
            tensPlace *= -1;
        int hundredsPlace = counterNumber / 100;
        if(hundredsPlace < 0)
            hundredsPlace += -1;
//        cout << counterNumber << endl;
//        cout << onesPlace << endl;
//        cout << tensPlace << endl;
//        cout << hundredsPlace << endl;

        // Minus Sign
        if (counterNumber < 0) {
            sf::Texture negativeDigitTexture;
            negativeDigitTexture.loadFromFile("images/digits.png", sf::IntRect(210, 0, 21, 32));
            sf::Sprite negativeDigit;
            negativeDigit.setTexture(negativeDigitTexture);
            negativeDigit.setPosition(21, happyFace.getPosition().y);
            window.draw(negativeDigit);
        }

        // Hundreds Digit
        sf::Texture hundredsDigitTexture;
        hundredsDigitTexture.loadFromFile("images/digits.png", sf::IntRect(hundredsPlace * 21, 0, 21, 32));
        sf::Sprite hundredsDigit;
        hundredsDigit.setTexture(hundredsDigitTexture);
        hundredsDigit.setPosition(42, happyFace.getPosition().y);
        window.draw(hundredsDigit);

        // Tens Digit
        sf::Texture tensDigitTexture;
        tensDigitTexture.loadFromFile("images/digits.png", sf::IntRect(tensPlace * 21, 0, 21, 32));
        sf::Sprite tensDigit;
        tensDigit.setTexture(tensDigitTexture);
        tensDigit.setPosition(hundredsDigit.getPosition().x + 21, happyFace.getPosition().y);
        window.draw(tensDigit);

        // Ones Digit
        sf::Texture onesDigitTexture;
        onesDigitTexture.loadFromFile("images/digits.png", sf::IntRect(onesPlace * 21, 0, 21, 32));
        sf::Sprite onesDigit;
        onesDigit.setTexture(onesDigitTexture);
        onesDigit.setPosition(tensDigit.getPosition().x + 21, happyFace.getPosition().y);
        window.draw(onesDigit);



        if (lose) {
            loseFace.setPosition(happyFace.getPosition().x, happyFace.getPosition().y);
            window.draw(loseFace);
        }

        if (!lose && checkWin(board, width * height)) {
            winFace.setPosition(happyFace.getPosition().x, happyFace.getPosition().y);
            window.draw(winFace);
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board[0].size(); j++) {
                    if (board[i][j].getMine()) {
                        debugMode = false;
                        board[i][j].setFlagX(true);
                    }
                }
            }
        }

// Keep all drawings above here

        window.display();
    }

    TextureManager::Clear();
    return 0;
}