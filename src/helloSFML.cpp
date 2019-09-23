#include "mainFunctions.hpp"


/** This is the Tetris game by Zixuan Zhao and Jun Shen
 The project uses two classes: Tetromino and Background
 The idea is to operate on numbers and convert them to rectangles
 */

int main() {
    // Set the window parameters
    sf::RenderWindow window(sf::VideoMode((NUMCOLS * CELLSIZE + (NUMCOLS + 1) * GRIDTHICKNESS) * (1 + LEFTRIGHTRATIO),
                                          NUMROWS * CELLSIZE + (NUMROWS + 1) * GRIDTHICKNESS),
                                          "Tetris Game",
                                          sf::Style::Default);

    // To center the window
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i((desktop.width - window.getSize().x) / 2.0,
                                    (desktop.height - window.getSize().y) / 2.0));

    // Synchronize the application's refresh rate as 60 to avoid overheat of CPU
    window.setFramerateLimit(10);
    
    // Load the font, audio, and the background image
    sf::Font font = loadFont("./ttf/consola.ttf");
    
    sf::SoundBuffer buffer = loadScoreSound("./audio/removelines.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);
    
    sf::Music music;
    if (!music.openFromFile("./audio/bgm.wav")){
        return -1;
    }
    music.play();
    music.setLoop(true);
    
    // Initialize a Tetromino and the Background class
    int randForShape = rand() % 7;
    int randForColor = rand() % 5;
    
    Tetromino tetro(vecShape[randForShape], vecColor[randForColor]);
    vector<sf::RectangleShape> vecTetromino = tetro.numToBlocks();
    
    Background background;
    vector<sf::RectangleShape> vecBackground = background.numToBlocks();
    
    // Start timing
    sf::Clock clock;
    
    // This variable is meant to prevent a sfml bug from disturbing our program
    double secondsLastTime = 0;
    
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left && !tetro.touchLeft() && !background.overlapIfMoveLeft(tetro)) {
                    tetro.moveleft();
                    vecTetromino = tetro.numToBlocks();
                }
                if (event.key.code == sf::Keyboard::Right && !tetro.touchRight() && !background.overlapIfMoveRight(tetro)) {
                    tetro.moveright();
                    vecTetromino = tetro.numToBlocks();
                }
                if (event.key.code == sf::Keyboard::Down && !tetro.touchBottom() && !background.aboutToOverLap(tetro)) {
                    while (!tetro.touchBottom() && !background.aboutToOverLap(tetro)) {
                        tetro.movedown();
                    }
                }
                if (event.key.code == sf::Keyboard::Up) {
                    tetro.rotate(background);
                    vecTetromino = tetro.numToBlocks();
                }
            }
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Draw static text
        
        window.clear(RIGHTHANDCOLOR);
        
        sf::Vector2f cellSize(CELLSIZE, CELLSIZE);
        sf::RectangleShape grid[NUMROWS][NUMCOLS];
        for(int i = 0; i < NUMROWS; i++){
            for(int j = 0; j < NUMCOLS; j++){
                grid[i][j].setSize(cellSize);
                grid[i][j].setOutlineColor(OUTLINECOLOR);
                grid[i][j].setOutlineThickness(GRIDTHICKNESS);
                grid[i][j].setFillColor(GRIDFILLCOLOR);
                grid[i][j].setPosition(j * (cellSize.x + GRIDTHICKNESS) + GRIDTHICKNESS,
                                       i * (cellSize.y + GRIDTHICKNESS) + GRIDTHICKNESS);
                window.draw(grid[i][j]);
            }
        }
        
        sf::Text ScoreText = createText("Score", 100, 800, 300, sf::Color::White, font);
        window.draw(ScoreText);

        if (background.reachTop()) {
            
            int final_score = background.getScore();

            background.randomBlink();
            vecBackground = background.numToBlocks();
            for (int i = 0; i < 200; i++) {
                window.draw(vecBackground[i]);
            }
            
            sf::Text GameOverText = createText("Game Over!", 120, 60, 600, sf::Color::Blue, font);
            sf::Text ScoreNumberText = createText(to_string(final_score), 100, 880, 500, sf::Color::White, font);
            window.draw(GameOverText);
            window.draw(ScoreNumberText);
            
            
        } else {
            sf::Text ScoreNumberText = createText(to_string(background.getScore()), 100, 880, 500, sf::Color::White, font);
            window.draw(ScoreNumberText);

            double secondsPassed = clock.getElapsedTime().asSeconds();
            
            // The time has reached a new int

            cout << secondsPassed <<" " << secondsLastTime << " "
            << !tetro.touchBottom() << " " << !background.aboutToOverLap(tetro) << endl;
            if (floor(secondsPassed) > secondsLastTime && !tetro.touchBottom() && !background.aboutToOverLap(tetro)) {
                tetro.movedown();
                vecTetromino = tetro.numToBlocks();
//                TimeMarker ++;
                secondsLastTime = floor(secondsPassed);
            }
            
            if (background.aboutToOverLap(tetro) || tetro.touchBottom()) {
                background.addTetromino(tetro);
                if (background.filledLines().size() != 0) {
                    background.removeFilledLines();
                    sound.play();
                }
                vecBackground = background.numToBlocks();
                
                tetro.resetPositions();
                tetro.resetColor();
            }
            
            for (int i = 0; i < vecTetromino.size(); i++) {
                window.draw(vecTetromino[i]);
            }
        
            for (int i = 0; i < vecBackground.size(); i++) {
                window.draw(vecBackground[i]);
            }
        }
        window.display();
    }
    return 0;
}
