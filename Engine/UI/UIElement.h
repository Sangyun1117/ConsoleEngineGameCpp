#pragma once
#include "Engine.h"
#include <string>
#include <vector>

class UIElement{
public:
	UIElement(const std::string& imageLink);
	virtual void Render()=0;
	virtual ~UIElement() {};
public:
	bool isVisible = true;
protected:
	std::vector<std::vector<char>> image;
	std::string imageLink;
};