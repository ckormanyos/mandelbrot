#include <MandelbrotDiscovery.h>

auto WINAPI WinMain(HINSTANCE h_wnd, ::HINSTANCE, LPSTR, int) -> int
{
  using local_window_type = mandelbrot_discovery<static_cast<int>(UINT16_C(800))>;

  const auto result_win_main = local_window_type::win_main(h_wnd);

  return result_win_main;
}
