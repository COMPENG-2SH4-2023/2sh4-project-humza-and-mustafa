#include "Player.h"

#define NONE '\0'
#define ESC '/'

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Create list and snake head
    playerPosList = new objPosArrayList();
    playerPosList->insertHead( *new objPos(15, 10, '*') );

    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
    delete[] playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic using 'wasd' controls
    switch (mainGameMechsRef->getInput())
    {
        case ESC:
            // exit

            mainGameMechsRef->setExitTrue();
            break;

        case NONE:
            // keep current myDir

            break;

        case 'w':
            // up

            if (myDir == STOP || myDir == LEFT || myDir == RIGHT)
            {
                myDir = UP;
            }
            break;

        case 'a':
            // left

            if (myDir == STOP || myDir == UP || myDir == DOWN)
            {
                myDir = LEFT;
            }
            break;

        case 's':
            // down

            if (myDir == STOP || myDir == LEFT || myDir == RIGHT)
            {
                myDir = DOWN;
            }
            break;

        case 'd':
            // right

            if (myDir == STOP || myDir == UP || myDir == DOWN)
            {
                myDir = RIGHT;
            }
            break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
        
    // Update based on direction and speed

    objPos newHead;
    playerPosList->getHeadElement(newHead);

    if (myDir == LEFT)
    {
        newHead.x -= 1;
    }
    else if (myDir == RIGHT)
    {
        newHead.x += 1;
    }
    else if (myDir == UP)
    {
        newHead.y -= 1;
    }
    else if (myDir == DOWN)
    {
        newHead.y += 1;
    }

    // Border wrap-around logic
    if (newHead.x <= 0)
    {
        newHead.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    else if (newHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
    {
        newHead.x = 1;
    }
    else if (newHead.y <= 0)
    {
        newHead.y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    else if (newHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
    {
        newHead.y = 1;
    }


    // Snake update algorithm. Insert head, remove tail if no food collision
    playerPosList->insertHead(newHead);

    // If player does not eat food, keep length the same. Else add one and generate new food.
    if (!checkFoodConsumption())
    {
        playerPosList->removeTail();
    }
    else
    {
        mainGameMechsRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore();
    }

    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseTrue();
    }
}

bool Player::checkFoodConsumption()
{
    // Check if snake head collides with food object

    objPos newHead, foodPos;
    playerPosList->getHeadElement(newHead);
    mainGameMechsRef->getFoodPos(foodPos);

    return newHead.isPosEqual(&foodPos);
}

bool Player::checkSelfCollision()
{
    // Check if snake head collides with body

    int size = playerPosList->getSize();
    objPos snakeBody, snakeHead;
    playerPosList->getElement(snakeHead, 0);

    for (int i = 1; size > i; i++) 
    {
        playerPosList->getElement(snakeBody, i);
        if (snakeBody.isPosEqual(&snakeHead)) 
        {
            return true;
        }
    }

    return false;
}