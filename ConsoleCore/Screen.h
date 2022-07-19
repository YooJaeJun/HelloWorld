#pragma once

class Screen
{
public:
	void Init();
	void Flipping();
	void Clear();
	void Release();
	void Print(const int x, const int y, string str);
	void SetColor(unsigned short color);
};

