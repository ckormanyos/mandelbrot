// MandelbrotDiscovery.cpp : Defines the entry point for the application.
//

#include <framework.h>
#include <MandelbrotDiscovery.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace local
{
  auto load_jpeg_image(const wchar_t* filename) -> HBITMAP
  {
    // Load JPEG image using WIC

    IWICImagingFactory*    pFactory   { nullptr };
    IWICBitmapDecoder*     pDecoder   { nullptr };
    IWICBitmapFrameDecode* pFrame     { nullptr };
    IWICFormatConverter*   pConverter { nullptr };

    static_cast<void>(CoInitialize(nullptr));

    static_cast<void>
    (
      CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory))
    );

    pFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
    pDecoder->GetFrame(0, &pFrame);
    pFactory->CreateFormatConverter(&pConverter);

    pConverter->Initialize(pFrame,
                           GUID_WICPixelFormat32bppPBGRA,
                           WICBitmapDitherTypeNone,
                           nullptr,
                           0.0F,
                           WICBitmapPaletteTypeMedianCut);

    UINT width  { };
    UINT height { };

    pFrame->GetSize(&width, &height);

    const DWORD header_area
    {
      static_cast<DWORD>
      (
        static_cast<DWORD>(width) * static_cast<DWORD>(height) * static_cast<DWORD>(UINT8_C(4))
      )
    };

    BITMAPINFOHEADER
      bi
      {
         sizeof(BITMAPINFOHEADER),
        +static_cast<LONG>(width),
        -static_cast<LONG>(height),
         static_cast<WORD>(UINT8_C(1)),
         static_cast<WORD>(UINT8_C(32)),
         static_cast<DWORD>(BI_RGB),
         header_area,
         static_cast<LONG>(INT8_C(0)),
         static_cast<LONG>(INT8_C(0)),
         static_cast<DWORD>(UINT8_C(0)),
         static_cast<DWORD>(UINT8_C(0))
      };

    void* pixels { nullptr };

    HBITMAP hBitmap
    {
      CreateDIBSection(nullptr, (BITMAPINFO*) &bi, DIB_RGB_COLORS, &pixels, nullptr, 0)
    };

    pConverter->CopyPixels(nullptr,
                           static_cast<UINT>(width * static_cast<UINT>(UINT8_C(4))),
                           static_cast<UINT>(header_area),
                           static_cast<BYTE*>(pixels));

    pFactory->Release();
    pDecoder->Release();
    pFrame->Release();
    pConverter->Release();

    return hBitmap;
  }
} // namespace local

auto CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
  LRESULT result { static_cast<LRESULT>(INT8_C(0)) };

  switch(uMsg)
  {
    case WM_PAINT:
    {
      PAINTSTRUCT ps { };

      HDC hdc { BeginPaint(hwnd, &ps) };

      // Load JPEG image
      const HBITMAP hBitmap { local::load_jpeg_image(L"mandelbrot_MANDELBROT_05_SEAHORSES.jpg") };

      // Draw the image onto the window's client area
      HDC hdcMem { CreateCompatibleDC(hdc) };
      SelectObject(hdcMem, hBitmap);

      BITMAP bitmap { };
      GetObject(hBitmap, sizeof(bitmap), &bitmap);

      StretchBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

      DeleteDC(hdcMem);
      DeleteObject(hBitmap);

      EndPaint(hwnd, &ps);

      break;
    }
    case WM_DESTROY:
    {
      PostQuitMessage(static_cast<int>(INT8_C(0)));

      break;
    }
    default:
    {
      result = static_cast<LRESULT>(DefWindowProc(hwnd, uMsg, wParam, lParam));

      break;
    }
  }

  return result;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
  WNDCLASSEX
    wc
    {
      sizeof(WNDCLASSEX),
      CS_HREDRAW | CS_VREDRAW,
      WindowProc,
      0,
      0,
      GetModuleHandle(nullptr),
      LoadIcon(nullptr, IDI_APPLICATION),
      LoadCursor(nullptr, IDC_ARROW),
      (HBRUSH)(COLOR_WINDOW + 1),
      nullptr,
      "WindowClass",
      LoadIcon(nullptr, IDI_APPLICATION)
    };

  if(!RegisterClassEx(&wc))
  {
    MessageBox(nullptr, "Window Registration Failed!", "Error!", static_cast<UINT>(MB_ICONEXCLAMATION | MB_OK));

    return 0;
  }

  HWND
    handle_to_window
    {
      ::CreateWindowEx
      (
        static_cast<DWORD>(UINT8_C(0)),
        "WindowClass",
        "Window Title",
        static_cast<DWORD>(WS_OVERLAPPEDWINDOW /*| WS_HSCROLL | WS_VSCROLL*/),
        static_cast<int>(CW_USEDEFAULT),
        static_cast<int>(CW_USEDEFAULT),
        static_cast<int>(INT16_C(768)),
        static_cast<int>(INT16_C(768)),
        nullptr,
        nullptr,
        hInstance,
        nullptr
      )
    };

  if(handle_to_window == nullptr)
  {
    ::MessageBox(nullptr, "Window Creation Failed!", "Error!", static_cast<UINT>(MB_ICONEXCLAMATION | MB_OK));

    return 0;
  }

  ShowWindow(handle_to_window, nShowCmd);

  UpdateWindow(handle_to_window);

  // Allocate a console window
  AllocConsole();

  // Get handles to the standard output
  HANDLE hConsoleInput  = GetStdHandle(STD_INPUT_HANDLE);
  HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

  // Display some text
  DWORD bytesWritten;
  const char* message = "Hello, console!";
  WriteConsole(hConsoleOutput, message, static_cast<DWORD>(std::strlen(message)), &bytesWritten, nullptr);

  // Read input from the console
  char buffer[static_cast<std::size_t>(UINT16_C(256))];
  DWORD bytesRead;
  ReadConsole(hConsoleInput, buffer, sizeof(buffer), &bytesRead, nullptr);
  buffer[bytesRead - 2] = '\0'; // Remove newline character from input

  MSG msg { };

  while(::GetMessage(&msg, nullptr, 0, 0))
  {
    TranslateMessage(&msg);

    DispatchMessage(&msg);
  }

  // Keep the console window open until a key is pressed
  //getchar();

  // Free the console window
  FreeConsole();

  return 0;
}
