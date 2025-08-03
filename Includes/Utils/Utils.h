#pragma once

#include <Windows.h>
#include "Math/Vector2.h"
#include "Math/Color.h"

// ������Ʈ���� �پ��ϰ� ����� ��ƿ��Ƽ �Լ� ����.
namespace Utils
{
	// �� ���� ���� �ٲ� �� ����ϴ� �Լ�.
	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// �ܼ� ��� �ڵ� �������� �Լ�.
	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	// �ܼ� �ؽ�Ʈ ���� ���� �Լ�.
	inline void SetConsoleTextColor(WORD color)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleTextAttribute(handle, color);
	}

	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextColor(static_cast<WORD>(color));
	}

	//���� �߶��ִ� �Լ�
	template<typename T>
	std::vector<std::vector<T>> Slice2DVector(
		const std::vector<std::vector<T>>& src,
		int startRow, int startCol,
		int height, int width)
	{
		std::vector<std::vector<T>> result;
		int srcHeight = (int)src.size();
		int srcWidth = (int)(src.empty() ? 0 : src[0].size());

		for (int r = startRow; r < startRow + height && r < srcHeight; ++r)
		{
			std::vector<T> row;
			for (int c = startCol; c < startCol + width && c < srcWidth; ++c)
			{
				row.push_back(src[r][c]);
			}
			result.push_back(std::move(row));
		}

		return result;
	}
}