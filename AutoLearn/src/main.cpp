#include <windows.h>
#include <opencv2/opencv.hpp>
#include <iostream>

#include "Control.h"
#include "Search.h"

#define ASSET_PREFLIX "C:/Users/Summer/Desktop/AutoLearn/AutoLearn/asset/"
#define ASSET(x) ASSET_PREFLIX x

bool FindAndClick(cv::Mat screen, cv::Mat buttonTemplate, float hold = 0.99f);

enum class State
{
    Playing,
    Complete,
    Unstarted
};

#if 1
int main() {
    SetProcessDPIAware();
    const char* windowTitle = "ѧϰͨ";

    HWND hwnd = FindTargetWindow(windowTitle);
    if (!hwnd) {
        std::cerr << "Window not found: " << windowTitle << "\n";
        return 1;
    }

    SetForegroundWindow(hwnd);

    cv::Mat play = LoadPicture(ASSET("play.png"));
    cv::Mat complete = LoadPicture(ASSET("complete.png"));
    cv::Mat next = LoadPicture(ASSET("next.png"));

    State state = State::Unstarted;

    while (true)
    {
        cv::Mat screen = CaptureScreen();
        switch (state)
        {
            case State::Unstarted:
            {
                if (FindAndClick(screen, play))
                {
                    state = State::Playing;
                }
                else
                {
                    if (FindAndClick(screen, next))
                    {
                        screen = CaptureScreen();
                        FindAndClick(screen, next);
                    }
                    else
                    {
                        SimulateMouseScroll(-240);
                    }
                }
                break;
            }
            case State::Playing:
            {
                if (FindAndClick(screen, complete))
                {
                    state = State::Complete;
                }
                else
                {
                    Sleep(5000); // 每5s检查一次是否结束
                }
                break;
            }
            case State::Complete:
            {
                if (FindAndClick(screen, next))
                {
                    state = State::Unstarted;
                }
                else
                {
                    SimulateMouseScroll(-240);
                }
                break;
            }
        }
    }

    SimulateMouseClick(600, 400);

    return 0;
}
#endif

bool FindAndClick(cv::Mat screen, cv::Mat buttonTemplate, float hold)
{
    cv::Point point = FindButton(screen, buttonTemplate, hold);
    if (point == cv::Point(-1, -1))
    {
        return false;
    }

    SimulateMouseClick(point.x + buttonTemplate.cols / 2, point.y + buttonTemplate.rows / 2);
    Sleep(5000); // 等待加载
    return true;
}