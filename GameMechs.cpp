#include "GameMechs.h"

#define NONE '\0'

GameMechs::GameMechs()
{
    // Default constructor, recommended board size

    boardSizeX = 30;
    boardSizeY = 15;

    exitFlag = false;
    loseFlag = false;

    input = NONE;
    score = 0;
    speed = 1;

    // Allocate memory for board array on heap
    gameBoard = new char*[boardSizeY];
    for (int i = 0; boardSizeY > i; i++)
    {
        gameBoard[i] = new char[boardSizeX];
    }

    foodPos = new objPos();
}

GameMechs::GameMechs(int boardX, int boardY)
{
    // Can create custom board size

    boardSizeX = boardX;
    boardSizeY = boardY;

    exitFlag = false;
    input = NONE;
    score = 0;
    speed = 1;

    gameBoard = new char*[boardSizeY];
    for (int i = 0; boardSizeY > i; i++)
    {
        gameBoard[i] = new char[boardSizeX];
    }

    foodPos = new objPos();
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    // Free memory allocated on heap for game board
    for (int i = 0; boardSizeY > i; i++)
        delete[] gameBoard[i];

    delete[] gameBoard;
    delete foodPos;
}

bool GameMechs::getExitFlagStatus()
{
    // Return exit flag status

    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    // Return lose flag status

    return loseFlag;
}

char GameMechs::getInput()
{
    // Return most recent input

    return input;
}

int GameMechs::getBoardSizeX()
{
    // Return board height

    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    // Return board width

    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    // Set exit status to true

    exitFlag = true;
}

void GameMechs::setLoseTrue()
{
    // Set lose flag to true

    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    // Update most recent input

    input = this_input;
}

void GameMechs::clearInput()
{
    // Clear most recent input

    input = NONE;
}

int GameMechs::getScore()
{
    // Return score

    return score;
}

void GameMechs::incrementScore()
{
    // Increment score by 1

    score++;
}


void GameMechs::generateFood(objPosArrayList* blockOff)
{
    // Generate food in random position on board, except for one occupied by player
    srand(time(NULL));

    bool invalid = true;
    int x_food, y_food;
    objPos snakePart;
    int snakeSize = blockOff->getSize();

    while (invalid) 
    {
        invalid = false;
        x_food = (rand() % (boardSizeX - 2)) + 1; // [1, boardSizeX - 1]
        y_food = (rand() % (boardSizeY - 2)) + 1; // [1, boardSizeY - 1]

        // Check entire snake to avoid placing food here
        for(int i = 0; snakeSize > i; i++)
        {
            blockOff->getElement(snakePart, i);
            if (x_food == snakePart.x && y_food == snakePart.y)
            {
                invalid = true;
                break;
            }
        }
    }

    foodPos->setObjPos(x_food, y_food, 'F');
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(*foodPos);
}