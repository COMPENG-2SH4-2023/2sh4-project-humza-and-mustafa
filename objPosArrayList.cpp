#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
#include <iostream>
#include <stdexcept>

using namespace std;

// Check lecture contents on general purpose array list construction,
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    // Default capacity of 200. Initialize array as such.

    listSize = 0;
    arrayCapacity = 200;
    aList = new objPos[arrayCapacity];
    throwExceptions = false;
}

objPosArrayList::~objPosArrayList()
{
    // Free memory allocated on heap to hold objPos objects;

    delete[] aList;
}

int objPosArrayList::getSize()
{
    // Return number of valid objPos objects, NOT arraylist capacity.

    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Insert new objPos to start of array. Re-shuffle all other elements to make room.

    // Throw exception if there is no more space in ArrayList.
    if (throwExceptions && listSize == arrayCapacity)
    {
        throw std::out_of_range("ArrayList is full.");
    }

    // Move all elements 'up' to make space at front of list.
    for (int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Insert new objPos to end of array. No need to re-shuffle elements here.

    // Throw exception if there is no more space in ArrayList.
    if (throwExceptions && listSize == arrayCapacity)
    {
        throw std::out_of_range("ArrayList is full.");
    }

    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    // Remove new objPos from head of array. Need to re-shuffle elements here.

    // Can over-write element
    for (int i = 0; listSize - 1 > i; i++)
    {
        aList[i] = aList[i + 1];
    }

    listSize--;
}

void objPosArrayList::removeTail()
{
    // Set tail to zero-initialized objPos, lower listSize.

    objPos zeroPos;
    aList[listSize - 1] = zeroPos;
    listSize--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    // Return exception if list is empty, otherwise write into given address.

    if (throwExceptions && listSize == 0)
    {
        throw std::out_of_range("ArrayList is empty.");
    }

    returnPos.x = aList[0].x;
    returnPos.y = aList[0].y;
    returnPos.symbol = aList[0].symbol;
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    // Return exception if list is empty, otherwise write into given address.

    if (throwExceptions && listSize == 0)
    {
        throw std::out_of_range("ArrayList is empty");
    }

    objPos element = aList[listSize - 1];
    returnPos.x = element.x;
    returnPos.y = element.y;
    returnPos.symbol = element.symbol;
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    // Return exception if access is out of bounds, otherwise write into given address.
    
    if (throwExceptions && listSize > index) 
    {
        throw std::out_of_range("Out of ArrayList bounds.");
    }

    objPos element = aList[index];
    returnPos.x = element.x;
    returnPos.y = element.y;
    returnPos.symbol = element.symbol;
}