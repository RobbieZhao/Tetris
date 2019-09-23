//
//  mainFunctions.hpp
//  testSFML
//
//  Created by Zixuan Zhao on 9/16/19.
//

#ifndef mainFunctions_hpp
#define mainFunctions_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <cmath>


using namespace std;

/**
 for simplicity, we made some global const variables
 */
const vector<vector<int>> initialPositions = {
    {214, 203, 204, 205},
    {214, 215, 204, 205},
    {215, 203, 204, 205},
    {214, 204, 205, 206},
    {214, 215, 203, 204},
    {213, 214, 204, 205},
    {203, 204, 205, 206},
};


const vector<string> vecShape = {"tu", "tian", "L", "reverseL", "S", "reverseS", "I"};

const vector<sf::Color> vecColor = {
    sf::Color::White,
    sf::Color::Blue,
    sf::Color::Green,
    sf::Color::Red,
    sf::Color::Yellow
};

const int NUMROWS = 20;

const int NUMCOLS = 10;

const int CELLSIZE = 70;

const int GRIDTHICKNESS = 2;

const double LEFTRIGHTRATIO = 3.0 / 5;

const sf::Color OUTLINECOLOR = sf::Color::Blue;

const sf::Color GRIDFILLCOLOR = sf::Color(192, 192, 192);

const sf::Color RIGHTHANDCOLOR = sf::Color(96, 96, 96);


class Background;

class Tetromino {
    
public:
    Tetromino(string str, sf::Color clr);
    
    vector<sf::RectangleShape> numToBlocks();
    
    void moveleft();
    
    void moveright();
    
    void movedown();
    
    bool touchLeft();
    
    bool touchRight();
    
    bool touchBottom();
    
    int getNumOfBlocks();
    
    vector<int> getBlockPositions();
    
    sf::Color getColor();
    
    void resetColor();
    
    void resetPositions();
    
    void rotate(Background& background);
    
private:
    vector<int> block_positions;
    sf::Color color;
    string shape;
    
};

class Background {

public:
    
    void addTetromino(Tetromino tetro);
    
    vector<sf::RectangleShape> numToBlocks();
    
    bool aboutToOverLap(Tetromino tetro);
    
    vector<int> filledLines();
    
    void removeFilledLines();
    
    bool overlapIfMoveLeft(Tetromino tetro);
    
    bool overlapIfMoveRight(Tetromino tetro);
    
    bool reachTop();
    
    void randomBlink();
    
    int getScore();
    
    map<int, sf::Color> getbackgroundBlocksMap();
    
private:
    map<int, sf::Color> backgroundBlocksMap;
    int score = 0;
};


sf::Text createText(string str, int size, int xPos, int yPos, sf::Color clr, sf::Font &font);

sf::Texture loadBackgroundImage(string IMG_PATH, sf::IntRect positions);

sf::Font loadFont(string FONT_PATH);

sf::SoundBuffer loadScoreSound(string SOUND_PATH);



#endif /* mainFunctions_hpp */
