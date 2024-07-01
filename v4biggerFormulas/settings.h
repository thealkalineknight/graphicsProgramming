#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>
using namespace std;


class Settings {
public:
	Color darkGreen = Color{ 20, 160, 133, 255 };
	Color green = Color{ 43, 51, 24, 255 };
	Color aColor = Color{ 56, 45, 23, 67 };
	const int scrWid = 1300;
	const int scrHei = 800;
	const int scale = 300;
};