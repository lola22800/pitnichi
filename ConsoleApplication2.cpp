#include "TXLib.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>   

using namespace std;

const COLORREF MY_DEEP_ROMANTIC_PINK = RGB(128, 0, 128);

void patnacha(int i, int j, int c)
{
    txRectangle(266 * j + 10, 266 * i + 10, 266 * (j + 1) - 10, 266 * (i + 1) - 10);
    txSelectFont("Comic Sans MS", 200);


    txDrawText(266 * j + 10, 266 * i + 10, 266 * (j + 1) - 10, 266 * (i + 1) - 10, to_string(c).c_str());
}

void pole3(int arr[][3], int size)
{
    txSetColor(RGB(0, 128, 128), 6);
    txLine(266, 0, 266, 800);
    txLine(532, 0, 532, 800);
    txLine(0, 266, 800, 266);
    txLine(0, 532, 800, 532);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] != 0)
            {
                patnacha(i, j, arr[i][j]);
            }
        }
    }
}

void Update()
{
    txSleep(10);
    txSetFillColor(TX_BLUE);
    txClear();
}

void swapp(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

bool checkWin(int arr[][3])
{
    int counter = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] != counter)
            {
                return false;
            }
            counter++;
        }
    }
    return true;
}

void moveEmptySpace(int arr[][3], int& emptyRow, int& emptyCol)
{
    if (txGetAsyncKeyState(VK_LEFT) && emptyCol != 0) // verx
    {
        swapp(arr[emptyRow][emptyCol], arr[emptyRow][emptyCol - 1]);
        emptyCol--;
        while (txGetAsyncKeyState(VK_LEFT))
        {
            Sleep(10);
        }
    }
    else if (txGetAsyncKeyState(VK_DOWN) && emptyRow != 2) // Вниз
    {
        swapp(arr[emptyRow][emptyCol], arr[emptyRow + 1][emptyCol]);
        emptyRow++;
        while (txGetAsyncKeyState(VK_DOWN))
        {
            Sleep(10);
        }
    }
    else if (txGetAsyncKeyState(VK_UP) && emptyRow != 0) // levo
    {
        swapp(arr[emptyRow][emptyCol], arr[emptyRow - 1][emptyCol]);
        emptyRow--;
        while (txGetAsyncKeyState(VK_UP))
        {
            Sleep(10);
        }
    }
    else if (txGetAsyncKeyState(VK_RIGHT) && emptyCol != 2) // Вправо
    {
        swapp(arr[emptyRow][emptyCol], arr[emptyRow][emptyCol + 1]);
        emptyCol++;
        while (txGetAsyncKeyState(VK_RIGHT))
        {
            Sleep(10);
        }
    }
}

void shufflePuzzle(int arr[][3], int& emptyRow, int& emptyCol)
{
    srand(time(0));
    for (int i = 0; i < 100; ++i)
    {
        int move = rand() % 4;
        switch (move)
        {
        case 0:
            if (emptyRow != 0)
            {
                swapp(arr[emptyRow][emptyCol], arr[emptyRow - 1][emptyCol]);
                emptyRow--;
            }
            break;
        case 1:
            if (emptyRow != 2)
            {
                swapp(arr[emptyRow][emptyCol], arr[emptyRow + 1][emptyCol]);
                emptyRow++;
            }
            break;
        case 2:
            if (emptyCol != 0)
            {
                swapp(arr[emptyRow][emptyCol], arr[emptyRow][emptyCol - 1]);
                emptyCol--;
            }
            break;
        case 3:
            if (emptyCol != 2)
            {
                swapp(arr[emptyRow][emptyCol], arr[emptyRow][emptyCol + 1]);
                emptyCol++;
            }
            break;
        }
    }
}
void ShowMenu()
{
    txSetColor(MY_DEEP_ROMANTIC_PINK);
    txSelectFont("Comic Sans MS", 80);
   

    txTextOut(200, 200, "игра пятнашки ");
    txTextOut(280, 300, "1. Играть");
    txTextOut(280, 350, "2. Выйти");
    
}
int main()
{
    txCreateWindow(800, 800);
    int choice;
    
    do
    {
        ShowMenu();
        choice = 0;
        while (choice != 1 && choice != 2)
        {
            if (txGetAsyncKeyState('1'))
            {
                choice = 1;
            }
            if (txGetAsyncKeyState('2'))
            {
                choice = 2;
            }
        }

        switch (choice)
        {
        case 1:
           
            break;
        case 2:
            return 0;
        }
    } while (choice != 1);
    txPlaySound("popa.wav", SND_ASYNC | SND_LOOP);
    int counter = 0;
    const int rows = 3;
    const int cols = 3;
    int a[rows][cols];
    int emptyRow = 0;
    int emptyCol = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            a[i][j] = counter;
            counter++;
        }
    }

    shufflePuzzle(a, emptyRow, emptyCol);

    while (true)
    {
        moveEmptySpace(a, emptyRow, emptyCol);

        Update();
        pole3(a, rows);

        if (checkWin(a))
        {
            txMessageBox("Victory");
            break;          
        }
    }
    return 0;
}илья гандон