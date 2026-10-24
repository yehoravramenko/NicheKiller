#pragma comment(lib, "shell32")

#include <Windows.h>
#include <cassert>

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                                LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        return TRUE;
    case WM_DESTROY:
        PostQuitMessage(0);
        return TRUE;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine,
                   int nCmdShow)
{
    // constexpr NOTIFYICONDATA iconData = {
    //     .cbSize = sizeof(NOTIFYICONDATA),
    //     .uFlags = NIF_ICON,

    //};
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

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}