#pragma once

#include "Windows.h"
#include "opencv2/opencv.hpp"

HWND FindTargetWindow(const char* windowTitle);

cv::Mat CaptureScreen();

cv::Point FindButton(cv::Mat screen, cv::Mat buttonTemplate, double threshold = 0.9999);