#include "Utils.h"

//ȭ���� ����� �Լ�, system('cls') ���̱� ������ ���ӿ��� ���� ���� �ȵ�
void Utils::ClearScreen()
{
    HANDLE hConsole = GetConsoleHandle();
    CONSOLE_SCREEN_BUFFER_INFO csbi; //ȭ���� ����,����,Ŀ����ġ,���������� �����ϴ� ����ü
    DWORD count;
    DWORD cellCount;
    COORD zeroCoords = { 0, 0 };

    if (hConsole == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return; //���� �ܼ��� ������ ������
    cellCount = csbi.dwSize.X * csbi.dwSize.Y; //�ܼ�â ����*���� �� ���� ���

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, zeroCoords, &count);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, zeroCoords, &count);
    SetConsoleCursorPosition(hConsole, zeroCoords);
}
