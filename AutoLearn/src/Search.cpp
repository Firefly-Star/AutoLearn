#include "Search.h"

HWND FindTargetWindow(const char* windowTitle) {
    return FindWindowA(NULL, windowTitle);
}

cv::Mat CaptureScreen() {
    HWND hwndDesktop = GetDesktopWindow(); 
    HDC hdcScreen = GetDC(hwndDesktop);    
    HDC hdcMemory = CreateCompatibleDC(hdcScreen); 

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, screenWidth, screenHeight); 
    SelectObject(hdcMemory, hBitmap); 
    BitBlt(hdcMemory, 0, 0, screenWidth, screenHeight, hdcScreen, 0, 0, SRCCOPY);

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenWidth;
    bi.biHeight = -screenHeight; 
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    cv::Mat mat(screenHeight, screenWidth, CV_8UC3); 
    GetDIBits(hdcMemory, hBitmap, 0, (UINT)screenHeight, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS); 

    DeleteObject(hBitmap);
    DeleteDC(hdcMemory);
    ReleaseDC(hwndDesktop, hdcScreen);

    return mat;
}

cv::Point FindButton(cv::Mat screen, cv::Mat buttonTemplate, double threshold) {
    cv::Mat result;
    cv::matchTemplate(screen, buttonTemplate, result, cv::TM_CCOEFF_NORMED);

    std::vector<cv::Point> matchedPoints;

    for (int y = 0; y < result.rows; y++) {
        for (int x = 0; x < result.cols; x++) {
            double matchValue = result.at<float>(y, x);
            if (matchValue >= threshold) {
                matchedPoints.push_back(cv::Point(x, y));
            }
        }
    }

    if (!matchedPoints.empty()) {
        auto topPoint = *std::min_element(matchedPoints.begin(), matchedPoints.end(),
            [](const cv::Point& a, const cv::Point& b) {
                return a.y < b.y;
            });
        return topPoint;
    }

    return cv::Point(-1, -1);
}
