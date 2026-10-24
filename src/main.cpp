#pragma comment(lib, "shell32")

#include <Windows.h>
#include <cassert>

#define WM_TRAYICON (WM_APP + 1)
#define IDM_EXIT    1001

void ShowContextMenu(HWND hWnd)
{
    POINT pt{};
    GetCursorPos(&pt);

    auto hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING, IDM_EXIT, L"Exit");

    SetForegroundWindow(hWnd);

    int clickedCommand = TrackPopupMenu(hMenu, (TPM_LEFTBUTTON | TPM_RETURNCMD),
                                        pt.x, pt.y, 0, hWnd, nullptr);

    DestroyMenu(hMenu);

    if (clickedCommand == IDM_EXIT)
        DestroyWindow(hWnd);
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                                LPARAM lParam)
{
    static NOTIFYICONDATA iconData{};

    switch (uMsg)
    {
    case WM_CREATE: {
        iconData.cbSize           = sizeof(NOTIFYICONDATA);
        iconData.hWnd             = hWnd;
        iconData.uFlags           = NIF_ICON | NIF_MESSAGE;
        iconData.uCallbackMessage = WM_TRAYICON;
        iconData.hIcon            = LoadIcon(nullptr, IDI_APPLICATION);

        Shell_NotifyIcon(NIM_ADD, &iconData);
        return TRUE;
    }
    case WM_CLOSE:
        Shell_NotifyIcon(NIM_DELETE, &iconData);
        DestroyWindow(hWnd);
        return TRUE;
    case WM_DESTROY:
        PostQuitMessage(0);
        return TRUE;

    case WM_TRAYICON:
        if (lParam == WM_RBUTTONUP || lParam == WM_LBUTTONUP)
        {
            ShowContextMenu(hWnd);
        }
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    const WNDCLASSEX wc{
        .cbSize        = sizeof(WNDCLASSEX),
        .lpfnWndProc   = WndProc,
        .hInstance     = hInstance,
        .hIcon         = LoadIcon(nullptr, IDI_APPLICATION),
        .lpszClassName = L"MainWindow",
    };
    HWND hWnd{};
    MSG msg{};

    auto res = RegisterClassEx(&wc);
    assert(res);

    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"MainWindow", L"Niche Killer",
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                          800, 600, nullptr, nullptr, hInstance, nullptr);
    assert(hWnd);

    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}