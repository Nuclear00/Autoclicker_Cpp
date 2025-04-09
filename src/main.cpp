#include <iostream>
#include <windows.h>
#include <thread>

// mouse click simulation
void MouseClick() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    std::cout << "AutoClickerProcess started!" << std::endl;
    std::cout << "Press F10 to start/stop clicking. Press F9 to exit." << std::endl;

    bool clicking = false;
    bool running = true;

    while (running) {
        // check that f10 is pressed
        if (GetAsyncKeyState(VK_F10) & 0x8000) {
            clicking = !clicking;
            std::cout << (clicking ? "Clicking started." : "Clicking stopped.") << std::endl;
            Sleep(100); //prevent rapid toggle
        }

        // checks when f9 pressed
        if (GetAsyncKeyState(VK_F9) & 0x8000) {
            running = false;
            std::cout << "Exiting AutoClickerProcess." << std::endl;
            break;
        }

        // clicks if f10 pressed
        if (clicking) {
            MouseClick();
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // adjust clicking interval
        }

        // small delay to avoid excessive processor usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
