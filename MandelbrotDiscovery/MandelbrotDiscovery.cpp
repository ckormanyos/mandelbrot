// MandelbrotDiscovery.cpp : Defines the entry point for the application.
//

#include <framework.h>
#include <MandelbrotDiscovery.h>

// Load JPEG image using WIC
auto LoadJPEGImage(const wchar_t* filename) -> HBITMAP
{
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

  BITMAPINFOHEADER
    bi
    {
       sizeof(BITMAPINFOHEADER),
      +static_cast<LONG>(width),
      -static_cast<LONG>(height),
      1,
      32,
      BI_RGB,
      width * height * 4,
      0,
      0,
      0,
      0
    };

  void* pixels { nullptr };

  HBITMAP hBitmap
  {
    CreateDIBSection(nullptr, (BITMAPINFO*) &bi, DIB_RGB_COLORS, &pixels, nullptr, 0)
  };

  pConverter->CopyPixels(nullptr, width * 4, width * height * 4, static_cast<BYTE*>(pixels));

  pFactory->Release();
  pDecoder->Release();
  pFrame->Release();
  pConverter->Release();

  return hBitmap;
}

auto CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
{
  switch (uMsg)
  {
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      // Load JPEG image
      HBITMAP hBitmap = LoadJPEGImage(L"mandelbrot_MANDELBROT_05_SEAHORSES.jpg");

      // Draw the image onto the window's client area
      HDC hdcMem = CreateCompatibleDC(hdc);
      SelectObject(hdcMem, hBitmap);
      BITMAP bitmap;
      GetObject(hBitmap, sizeof(bitmap), &bitmap);
      StretchBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

      DeleteDC(hdcMem);
      DeleteObject(hBitmap);

      EndPaint(hwnd, &ps);
      return 0;
    }
    case WM_DESTROY:
    {
      PostQuitMessage(0);

      return 0;
    }
    default:
    {
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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
      L"WindowClass",
      LoadIcon(nullptr, IDI_APPLICATION)
    };

  if(!RegisterClassEx(&wc))
  {
    MessageBox(nullptr, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);

    return 0;
  }

  HWND
    handle_to_window
    {
      ::CreateWindowEx
      (
        0,
        L"WindowClass",
        L"Window Title",
        WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, CW_USEDEFAULT,
        CW_USEDEFAULT,
        1024,
        1024,
        nullptr,
        nullptr,
        hInstance,
        nullptr
      )
    };

  if(handle_to_window == nullptr)
  {
    ::MessageBox(nullptr, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);

    return 0;
  }

  ShowWindow(handle_to_window, nCmdShow);

  UpdateWindow(handle_to_window);

  MSG msg { };

  while(::GetMessage(&msg, nullptr, 0, 0))
  {
    TranslateMessage(&msg);

    DispatchMessage(&msg);
  }

  return 0;
}
