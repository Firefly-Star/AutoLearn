#include "Control.h"

#include <windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat LoadPicture(std::string const& path)
{
    cv::Mat result = cv::imread(path, cv::IMREAD_COLOR);
    if (result.empty())
    {
        std::cerr << "Failed to load the picture at: " << path << "\n";
    }
    return result;
}

void SimulateMouseClick(int x, int y) {
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void SimulateMouseScroll(int scrollAmount) {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.mouseData = scrollAmount;

    SendInput(1, &input, sizeof(INPUT));
}