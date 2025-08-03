#include "UIElement.h"
#include <fstream>
#include <iostream>
#include <locale>
#include <codecvt>  // C++17 ���������� �ʿ�

UIElement::UIElement(const std::string& imageLink) : imageLink(imageLink)
{
    std::ifstream file(imageLink);
    if (!file.is_open()) {
        std::cerr << "������ �� �� �����ϴ�: " << imageLink << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        image.push_back(line);
    }

    file.close();
}
