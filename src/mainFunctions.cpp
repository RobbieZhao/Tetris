//
//  mainFunctions.cpp
//  testSFML
//
//  Created by Zixuan Zhao on 9/16/19.
//

#include "mainFunctions.hpp"


/**
 These are all the functions of the Tetromino class and Background class,
 along with some functions that deal with basic SFML components
 */
Tetromino::Tetromino(string str, sf::Color clr) {
    shape = str;
    for (int i = 0; i < vecShape.size(); i++) {
        if (vecShape[i] == str) {
            block_positions = initialPositions[i];
        }
    }
    color = clr;
}

vector<sf::RectangleShape> Tetromino::numToBlocks() {
    vector<sf::RectangleShape> vec;
    for (int i = 0; i < block_positions.size(); i++) {
        sf::RectangleShape rectangle(sf::Vector2f(70.f, 70.f));
        rectangle.setPosition(block_positions[i] % 10 * 72 + 2, (19 - block_positions[i] / 10)* 72 + 2);
        rectangle.setFillColor(color);
        vec.push_back(rectangle);
    }
    return vec;
}

void Tetromino::moveleft() {
    for (int i = 0; i < block_positions.size(); i++) {
        block_positions[i]--;
    }
}

void Tetromino::moveright() {
    for (int i = 0; i < block_positions.size(); i++) {
        block_positions[i]++;
    }
}

void Tetromino::movedown() {
    for (int i = 0; i < block_positions.size(); i++) {
        block_positions[i] -= 10;
    }
}

int Tetromino::getNumOfBlocks() {
    return block_positions.size();
}

bool Tetromino::touchLeft() {
    int min_columnNumber = block_positions[0] % 10;
    for (int i = 1; i < block_positions.size(); i++) {
        if (block_positions[i] % 10 < min_columnNumber) {
            min_columnNumber = block_positions[i] % 10;
        }
    }
    return min_columnNumber == 0;
}

bool Tetromino::touchRight() {
    int max_columnNumber = block_positions[0] % 10;
    for (int i = 1; i < block_positions.size(); i++) {
        if (block_positions[i] % 10 > max_columnNumber) {
            max_columnNumber = block_positions[i] % 10;
        }
    }
    return max_columnNumber == 9;
}

bool Tetromino::touchBottom() {
    int min_rowNumber = block_positions[0] / 10;
    for (int i = 1; i < block_positions.size(); i++) {
        if (block_positions[i] / 10 < min_rowNumber) {
            min_rowNumber = block_positions[i] / 10;
        }
    }
    return min_rowNumber == 0;
}

vector<int> Tetromino::getBlockPositions() {
    return block_positions;
}

sf::Color Tetromino::getColor() {
    return color;
}

void Tetromino::resetPositions() {
    int randNumber = rand() % 7;
//    randNumber = 6;
    block_positions = initialPositions[randNumber];
    shape = vecShape[randNumber];

}

void Tetromino::resetColor() {
    color = vecColor[rand() % 5];
}

void Tetromino::rotate(Background& background) {
    
    sort(block_positions.begin(), block_positions.end());
    int minimum = block_positions[0];
    int maximum = block_positions[getNumOfBlocks() - 1];
    
    vector<int> new_blockpositions;
    
    if (shape == "I") {
        if (block_positions[0] / 10 == block_positions[1] / 10) { // horizontal
            new_blockpositions = {minimum, minimum + 10, minimum + 20, minimum + 30};
        } else if (minimum % 10 < 7) { // vertical
            new_blockpositions = {minimum, minimum + 1, minimum + 2, minimum + 3};
        } else if (minimum % 10 >= 7) {
            new_blockpositions = {(minimum / 10) * 10 + 6, (minimum / 10) * 10 + 7, (minimum / 10) * 10 + 8, (minimum / 10) * 10 + 9};
        }
    }
    if (shape == "S"){
        if(maximum/10 - minimum/10 == 1) {
            new_blockpositions = {minimum + 2, minimum + 11, minimum + 12, minimum + 21};
        } else {
            new_blockpositions = {minimum - 2, minimum - 1, minimum + 9, minimum + 10};
            if (minimum % 10 == 1) {
                for (int i = 0; i < new_blockpositions.size(); i++) {
                    new_blockpositions[i]++;
                }
            }
        }
    }
    
    if (shape == "reverseS") {
        if(maximum/10 - minimum/10 == 1) {
            new_blockpositions = {minimum, minimum + 10, minimum + 11, minimum + 21};
        } else {
            new_blockpositions = {minimum, minimum + 1, minimum + 9, minimum + 10};
            if (minimum % 10 == 0) {
                for (int i = 0; i < new_blockpositions.size(); i++) {
                    new_blockpositions[i]++;
                }
            }
        }
    }
    
    if (shape == "tu") {
        if (maximum - minimum == 11) {
            if (block_positions[1] == minimum + 1) {
                new_blockpositions = {minimum - 9, minimum + 1, minimum + 2, minimum + 11};
            } else {
                new_blockpositions = {minimum, minimum + 9, minimum + 10, minimum + 20};
            }
        } else {
            if (block_positions[1] == minimum + 10) {
                new_blockpositions = {minimum, minimum + 9, minimum + 10, minimum + 11};
                if (minimum % 10 == 0) {
                    for (int i = 0; i < new_blockpositions.size(); i++) {
                        new_blockpositions[i]++;
                    }
                }
            } else {
                new_blockpositions = {minimum + 9, minimum + 10, minimum + 11, minimum + 20};
                if (minimum % 10 == 9) {
                    for (int i = 0; i < new_blockpositions.size(); i++) {
                        new_blockpositions[i]--;
                    }
                }
            }
        }
    }
    
    if (shape == "L") {
        if (maximum / 10 - minimum / 10 == 1) {
            if (block_positions[1] == minimum + 1) {
                new_blockpositions = {minimum + 1, minimum + 2, minimum + 11, minimum + 21};
            } else {
                new_blockpositions = {minimum + 1, minimum + 11, minimum + 20, minimum + 21};
            }
        } else {
            if (block_positions[1] == minimum + 1) {
                new_blockpositions = {minimum, minimum + 10, minimum + 11, minimum + 12};
                if (minimum % 10 == 8) {
                    for (int i = 0; i < new_blockpositions.size(); i++) {
                        new_blockpositions[i]--;
                    }
                }
            } else {
                new_blockpositions = {minimum - 2, minimum - 1, minimum, minimum + 10};
                if (minimum % 10 == 1) {
                    for (int i = 0; i < new_blockpositions.size(); i++) {
                        new_blockpositions[i]++;
                    }
                }
            }
        }
    }
    
    if (shape == "reverseL") {
        if (maximum / 10 - minimum / 10 == 1) {
            if (block_positions[1] == minimum + 1) {
                new_blockpositions = {minimum, minimum + 10, minimum + 20, minimum + 21};
            } else {
                new_blockpositions = {minimum - 1, minimum, minimum + 10, minimum + 20};
            }
        } else {
            if (block_positions[1] == minimum + 1) {
                new_blockpositions = {minimum, minimum + 1, minimum + 2, minimum + 10};
                if (minimum % 10 == 8) {
                    for (int i = 0; i < new_blockpositions.size(); i++) {
                        new_blockpositions[i]--;
                    }
                }
            } else {
                new_blockpositions = {minimum + 1, minimum + 9, minimum + 10, minimum + 11};
                if (minimum % 10 == 0) {
                    for (int i = 0; i < new_blockpositions.size(); i++) {
                        new_blockpositions[i]++;
                    }
                }
            }
        }
    }
    
    if (shape == "tian") {
        return;
    }
    
    map<int, sf::Color> backgroundmap = background.getbackgroundBlocksMap();
    for (int i = 0; i < new_blockpositions.size(); i++) {
        if (backgroundmap.find(new_blockpositions[i]) != backgroundmap.end()) {
            return;
        }
    }
    block_positions = new_blockpositions;
}


void Background::addTetromino(Tetromino tetro) {
    int numOfBlocks = tetro.getNumOfBlocks();
    vector<int> tetro_positions = tetro.getBlockPositions();
    sf::Color color = tetro.getColor();
    for (int i = 0; i < numOfBlocks; i++) {
        backgroundBlocksMap[tetro_positions[i]] = color;
    }
}

vector<sf::RectangleShape> Background::numToBlocks() {
    vector<sf::RectangleShape> vec;
    
    for (auto pr : backgroundBlocksMap) {
        sf::RectangleShape rectangle(sf::Vector2f(70.f, 70.f));
        rectangle.setPosition(pr.first % 10 * 72 + 2, (19 - pr.first / 10) * 72 + 2);
        rectangle.setFillColor(pr.second);
        vec.push_back(rectangle);

    }
    return vec;
}


bool Background::aboutToOverLap(Tetromino tetro) {
    vector<int> tetro_positions = tetro.getBlockPositions();
    for (int i = 0; i < tetro_positions.size(); i++) {
        int positionIfDown = tetro_positions[i] - 10;
        if (backgroundBlocksMap.find(positionIfDown) != backgroundBlocksMap.end()) {
            return true;
        }
    }
    return false;
}

vector<int> Background::filledLines() {
    
    vector<vector<int>> positionsInLines;
    
    for (int i = 0; i < 20; i++) {
        positionsInLines.push_back({});
        for (auto pr : backgroundBlocksMap) {
            if (pr.first / 10 == i) {
                positionsInLines[i].push_back(pr.first);
            } else if (pr.first / 10 > i){
                break;
            }
        }
    }
    
    vector<int> filledLinesNumber;
    for (int i = 0; i < 20; i++) {
        if (positionsInLines[i].size() == 10) {
            filledLinesNumber.push_back(i);
        }
    }
    return filledLinesNumber;
}

void Background::removeFilledLines() {
    vector<int> filledLinesNumber = filledLines();
    
    for (int lineNumber : filledLinesNumber) {
        for (int i = 0; i < 10; i++) {
            int number = lineNumber * 10 + i;
            auto it = backgroundBlocksMap.find(number);
            backgroundBlocksMap.erase(it);
        }
    }
    
    int numOfFilledLines = filledLinesNumber.size();
    
    int lastFilledLineNumber = filledLinesNumber[numOfFilledLines - 1];
    
    vector<int> tempPositions;
    vector<sf::Color> tempColors;
    
    for (auto pr : backgroundBlocksMap) {
        if (pr.first >= (lastFilledLineNumber + 1) * 10) {
            tempPositions.push_back(pr.first - 10 * numOfFilledLines);
        } else {
            tempPositions.push_back(pr.first);
        }
        tempColors.push_back(pr.second);
    }
    backgroundBlocksMap.clear();
    for (int i = 0; i < tempPositions.size(); i++) {
        backgroundBlocksMap[tempPositions[i]] = tempColors[i];
    }

    
    score += numOfFilledLines * numOfFilledLines;
}

bool Background::overlapIfMoveRight(Tetromino tetro) {
    vector<int> block_positions = tetro.getBlockPositions();
    int biggestColNumber = block_positions[0] % 10;
    for (int i = 1; i < block_positions.size(); i++) {
        if (block_positions[i] % 10 > biggestColNumber) {
            biggestColNumber = block_positions[i] % 10;
        }
    }
    
    vector<int> positionsWithBiggestColNumber;
    for (int i = 0; i < block_positions.size(); i++) {
        if (block_positions[i] % 10 == biggestColNumber) {
            positionsWithBiggestColNumber.push_back(block_positions[i]);
        }
    }
    
    for (int i = 0; i < positionsWithBiggestColNumber.size(); i++) {
        if (backgroundBlocksMap.find(positionsWithBiggestColNumber[i] + 1) != backgroundBlocksMap.end()) {
            return true;
        }
    }
    return false;
}

bool Background::overlapIfMoveLeft(Tetromino tetro) {
    vector<int> block_positions = tetro.getBlockPositions();
    int smallestColNumber = block_positions[0] % 10;
    for (int i = 1; i < block_positions.size(); i++) {
        if (block_positions[i] % 10 < smallestColNumber) {
            smallestColNumber = block_positions[i] % 10;
        }
    }
    
    vector<int> positionsWithSmallestColNumber;
    for (int i = 0; i < block_positions.size(); i++) {
        if (block_positions[i] % 10 == smallestColNumber) {
            positionsWithSmallestColNumber.push_back(block_positions[i]);
        }
    }
    
    for (int i = 0; i < positionsWithSmallestColNumber.size(); i++) {
        if (backgroundBlocksMap.find(positionsWithSmallestColNumber[i] - 1) != backgroundBlocksMap.end()) {
            return true;
        }
    }
    return false;
}

bool Background::reachTop() {
    
    return backgroundBlocksMap.size() != 0 && backgroundBlocksMap.rbegin()->first > 199;
}

void Background::randomBlink() {
    for (int i = 0; i < 200; i++) {
        backgroundBlocksMap[i] = vecColor[rand() % 5];
    }
}

int Background::getScore() {
    return score;
}

map<int, sf::Color> Background::getbackgroundBlocksMap() {
    return backgroundBlocksMap;
}

sf::Text createText(string str, int size, int xPos, int yPos, sf::Color clr, sf::Font &font) {
    sf::Text text;
    text.setString(str);
    text.setCharacterSize(size);
    text.setPosition(xPos, yPos);
    text.setFillColor(clr);
    text.setFont(font);
    return text;
}


sf::Texture loadBackgroundImage(string IMG_PATH, sf::IntRect positions) {
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(IMG_PATH, positions)) {
        cout << "The img doesn't exist!" << endl;
        exit(1);
    }
    return backgroundTexture;
}


sf::Font loadFont(string FONT_PATH) {
    sf::Font font;
    if (!font.loadFromFile(FONT_PATH)) {
        cout << "The ttf file doesn't exist!" << endl;
        exit(1);
    }
    return font;
}

sf::SoundBuffer loadScoreSound(string SOUND_PATH) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("./audio/removelines.wav")) {
        cout << "The score sound file doesn't exist!" << endl;
        exit(1);
    }
    return buffer;
    
}
