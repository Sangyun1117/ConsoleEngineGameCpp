#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include "Math/Color.h"
#include <filesystem>

class ImageManager {
public:
	// �̱��� �ν��Ͻ� ���
	static ImageManager& Get() {
		static ImageManager instance;
		return instance;
	}

	std::string NormalizePath(const std::string& path) { //��ΰ� \\�� ���ͼ� /�� �ٲٴ� �Լ��� �ʿ�����
		std::string normalized = path;
		std::replace(normalized.begin(), normalized.end(), '\\', '/');
		return normalized;
	}

	bool LoadImagesFromFolder(const std::string& imageFolderPath, const std::string& colorFolderPath) {
		bool allLoaded = true;

		// �̹��� ���ϵ� �ε�
		for (const auto& entry : std::filesystem::directory_iterator(imageFolderPath)) {
			if (entry.is_regular_file() && entry.path().extension() == ".txt") {
				const std::string pathStr = NormalizePath(entry.path().string());
				if (!LoadImage(pathStr)) {
					allLoaded = false;
				}
			}
		}

		// �÷� ���ϵ� �ε�
		for (const auto& entry : std::filesystem::directory_iterator(colorFolderPath)) {
			if (entry.is_regular_file() && entry.path().extension() == ".txt") {
				const std::string pathStr = NormalizePath(entry.path().string());
				if (!LoadColor(pathStr)) {
					allLoaded = false;
				}
			}
		}

		return allLoaded;
	}

	// �ϵ��ڵ��� �̹��� �ε�
	//bool LoadHardcodedImages() {
	//	// �ϵ��ڵ��� �̹��� ��� ���
	//	const std::vector<std::string> imagePaths = {
	//		"../Assets/Images/AmongUs.txt",
	//		"../Assets/Images/Item.txt",
	//		"../Assets/Images/GrassBlock.txt"
	//	};

	//	const std::vector<std::string> colorPaths = {
	//		"../Assets/Colors/PlayerFgColors.txt",
	//		"../Assets/Colors/GrassBlockBgColors.txt",
	//	};

	//	bool allLoaded = true;
	//	for (const auto& path : imagePaths) {
	//		if (!LoadImage(path)) {
	//			allLoaded = false;
	//		}
	//	}

	//	for (const auto& path : colorPaths) {
	//		if (!LoadColor(path)) {
	//			allLoaded = false;
	//		}
	//	}

	//	return allLoaded;
	//}

	// Ư�� �̹��� ���� �ε�
	bool LoadImage(const std::string& filePath) {
		m_images[filePath] = LoadTextFile(filePath);
		if (m_images[filePath].empty()) {
			std::cerr << "Failed to load image: " << filePath << std::endl;
			return false;
		}
		return true;
	}

	// Ư�� �÷� ���� �ε�
	bool LoadColor(const std::string& filePath) {
		m_colors[filePath] = LoadColorsImage(filePath);
		if (m_colors[filePath].empty()) {
			std::cerr << "Failed to load image: " << filePath << std::endl;
			return false;
		}
		return true;
	}

	// �̹��� ��������
	const std::vector<std::vector<char>>& GetImage(const std::string& filePath) const {
		static const std::vector<std::vector<char>> empty;
		auto it = m_images.find(filePath);
		return it != m_images.end() ? it->second : empty;
	}

	//�÷� ��������
	const std::vector<std::vector<Color>>& GetColor(const std::string& filePath) const {
		static const std::vector<std::vector<Color>> empty;
		auto it = m_colors.find(filePath);
		return it != m_colors.end() ? it->second : empty;
	}

private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;

	// �ؽ�Ʈ ���� �ε�
	std::vector<std::vector<char>> LoadTextFile(const std::string& filePath) {
		std::ifstream file(filePath);
		std::vector<std::vector<char>> result;  // �� ���⿡ �����ϰ� ����

		if (!file.is_open()) {
			std::cerr << "������ �� �� �����ϴ�: " << filePath << std::endl;
			return result;
		}

		std::string line;
		size_t maxWidth = 0;
		std::vector<std::string> tempLines;

		// ���� �ٵ��� �а� �ִ� �ʺ� ���ϱ�
		while (std::getline(file, line)) {
			if (line.size() > maxWidth) maxWidth = line.size();
			tempLines.push_back(line);
		}

		// �������� �е��ؼ� result�� ����
		for (const auto& l : tempLines) {
			std::vector<char> row;
			for (size_t i = 0; i < maxWidth; ++i) {
				if (i < l.size())
					row.push_back(l[i]);
				else
					row.push_back(' ');
			}
			result.push_back(std::move(row));
		}

		return result;
	}

	//�÷� �ؽ�Ʈ ���� �ε�
	std::vector<std::vector<Color>> LoadColorsImage(const std::string& filePath)
	{
		std::ifstream file(filePath);
		std::vector<std::vector<Color>> result;
		if (!file.is_open()) {
			std::cerr << "�÷� ������ �� �� �����ϴ�: " << filePath << std::endl;
			return result;
		}

		std::string line;
		size_t maxWidth = 0;
		std::vector<std::string> tempLines;

		// 1. ���Ͽ��� ��� �� �б� & �ִ� �ʺ� ���
		while (std::getline(file, line)) {
			if (line.size() > maxWidth) maxWidth = line.size();
			tempLines.push_back(line);
		}

		// 2. �е� ó���Ͽ� ��� ����
		for (const auto& l : tempLines) {
			std::vector<Color> row;
			for (size_t i = 0; i < maxWidth; ++i) {
				if (i < l.size()) {
					row.push_back(ConvertHexCharToColor(l[i]));
				}
				else {
					row.push_back(Color::Transparent); // �е� �κ��� ���� ó��
				}
			}
			result.push_back(std::move(row));
		}

		return result;
	}
private:
	std::unordered_map<std::string, std::vector<std::vector<char>>> m_images;
	std::unordered_map<std::string, std::vector<std::vector<Color>>> m_colors;
};