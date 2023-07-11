#include <Windows.h>
#include <GL/gl.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class
    const wchar_t CLASS_NAME[] = L"OpenGL Window";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"OpenGL Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hWnd == NULL)
        return 0;

    // Get the device context
    HDC hDC = GetDC(hWnd);

    // Set the pixel format for the device context
    PIXELFORMATDESCRIPTOR pfd = {};

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int format = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, format, &pfd);

    // Create and activate the OpenGL rendering context
    HGLRC hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    // Show the window
    ShowWindow(hWnd, nCmdShow);

    // Enter the message loop
    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
    DestroyWindow(hWnd);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // Initialize OpenGL here
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        break;

    case WM_CLOSE:
        // Destroy the window
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        // Clean up OpenGL resources here
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDC = BeginPaint(hWnd, &ps);

        // Render OpenGL here
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the back buffer to the front
        SwapBuffers(hDC);

        EndPaint(hWnd, &ps);
    }
    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
