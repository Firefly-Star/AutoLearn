#pragma once

#include <string>

namespace cv
{
	class Mat;
}

cv::Mat LoadPicture(std::string const& path);
void SimulateMouseClick(int x, int y);
void SimulateMouseScroll(int scrollAmount);