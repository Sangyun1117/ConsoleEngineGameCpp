#include "Utils.h"

//화면을 지우는 함수, system('cls') 무겁기 때문에 게임에서 쓰면 절대 안됨
void Utils::ClearScreen()
{
    HANDLE hConsole = GetConsoleHandle();
    CONSOLE_SCREEN_BUFFER_INFO csbi; //화면의 가로,세로,커서위치,색상정보를 저장하는 구조체
    DWORD count;
    DWORD cellCount;
    COORD zeroCoords = { 0, 0 };

    if (hConsole == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return; //현재 콘솔의 정보를 가져옴
    cellCount = csbi.dwSize.X * csbi.dwSize.Y; //콘솔창 가로*세로 총 개수 계산

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, zeroCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, zeroCoords, &count);
    SetConsoleCursorPosition(hConsole, zeroCoords);
}
