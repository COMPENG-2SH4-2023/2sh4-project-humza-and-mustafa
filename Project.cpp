#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000
#define COLUMNS 15
#define ROWS 30
#define ESC '/'
#define NONE '\0'

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// GLOBALS:
Player *player;
GameMechs *gameState;


int main(void)
{

    Initialize();

    while( !gameState->getExitFlagStatus() && !gameState->getLoseFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // initialize player and game objects
    gameState = new GameMechs(30, 15);
    player = new Player(gameState);

    objPosArrayList* playerPos = player->getPlayerPos();
    gameState->generateFood(playerPos);
}

void GetInput(void)
{
    // Store input in gameMechs object if there is any, else clear.

    if (MacUILib_hasChar())
    {
        gameState->setInput( MacUILib_getChar() );
    }
    else
    {
        gameState->clearInput();
    }
}

void RunLogic(void)
{
    // Process and update player + game states

    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // To avoid repeated function calls
    int rows = gameState->getBoardSizeY();
    int cols = gameState->getBoardSizeX();

    // player and food positions
    objPos foodPos, snakePos;
    objPosArrayList* snake = player->getPlayerPos();
    int snakeSize = snake->getSize();
    gameState->getFoodPos(foodPos);

    // Set empty game board borders
    for(int i = 0; rows > i; i++) 
    {
        for(int j = 0; cols > j; j++)
        {
            if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1)
            {
                gameState->gameBoard[i][j] = '#';
            }
            else
            {
                gameState->gameBoard[i][j] = ' ';
            }
        }
    }

    // Place snake and food onto board
    gameState->gameBoard[foodPos.y][foodPos.x] = foodPos.symbol;
    for(int i = 0; snakeSize > i; i++)
    {
        snake->getElement(snakePos, i);
        gameState->gameBoard[snakePos.y][snakePos.x] = snakePos.symbol; 
    }

    // Print game board
    for (int i = 0; rows > i; i++)
    {
        for (int j = 0; cols > j; j++)
        {
            MacUILib_printf("%c", gameState->gameBoard[i][j]);
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("\n\n\n");
    MacUILib_printf("Score: %d\n\n", gameState->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    if (gameState->getLoseFlagStatus())
    {
        MacUILib_printf("You lost. You scored %d\n", gameState->getScore());
    }
  
    MacUILib_uninit();

    // Delete player and game objects allocated on heap
    delete player;
    delete gameState;
}
