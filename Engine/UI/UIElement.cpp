#include "UIElement.h"
#include <fstream>
#include <iostream>
#include <locale>
#include <codecvt>  // C++17 이전에서는 필요

UIElement::UIElement(const std::string& imageLink) : imageLink(imageLink)
{
    std::ifstream file(imageLink);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << imageLink << std::endl;
        return;
    }

    std::string line;
    size_t maxWidth = 0;
    std::vector<std::string> tempLines;

    file.close();
}
