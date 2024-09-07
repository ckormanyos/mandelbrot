///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_DISCOVERY_2024_04_12_H
  #define MANDELBROT_DISCOVERY_2024_04_12_H

  #if (defined(_MSC_VER) && (_MSC_VER < 1930))
  #if !defined(NOMINMAX)
  #define NOMINMAX
  #endif
  #endif

  #include <geometry.h>
  #include <utility.h>

  #include <concurrency/stopwatch.h>
  #include <mandelbrot/mandelbrot_generator_perturbative.h>
  #include <mandelbrot/mandelbrot_generator_trivial.h>

  #include <wincodec.h>
  #include <windows.h>

  #include <atomic>
  #include <charconv>
  #include <chrono>
  #include <cstdint>
  #include <cstring>
  #include <functional>
  #include <iomanip>
  #include <limits>
  #include <mutex>
  #include <sstream>
  #include <string>
  #include <thread>
  #include <tuple>

  namespace mandelbrot_discovery_detail
  {
    constexpr char WindowTitleDefault[] = "Mandelbrot Discovery";
  }

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId            = static_cast<int>(INT8_C(0)),
           const int   ScreenCoordinateX = static_cast<int>(UINT16_C(32)),
           const int   ScreenCoordinateY = static_cast<int>(UINT16_C(8))>
  class mandelbrot_discovery final
  {
  public:
    using rectangle_tuple_type = MandelbrotRectangleTupleType;
    using rectangle_00_type    = typename std::remove_reference<typename std::tuple_element<0, rectangle_tuple_type>::type>::type;
    using rectangle_01_type    = typename std::remove_reference<typename std::tuple_element<1, rectangle_tuple_type>::type>::type;
    using rectangle_02_type    = typename std::remove_reference<typename std::tuple_element<2, rectangle_tuple_type>::type>::type;

  private:
    using value_00_type = typename rectangle_00_type::point_type::value_type;
    using value_01_type = typename rectangle_01_type::point_type::value_type;
    using value_02_type = typename rectangle_02_type::point_type::value_type;

    static constexpr int screen_coordinate_x = static_cast<int>(ScreenCoordinateX);    // Screen coordinate X
    static constexpr int screen_coordinate_y = static_cast<int>(ScreenCoordinateY);    // Screen coordinate Y

    static constexpr int client_width        = static_cast<int>(WindowWidth);          // Client window width
    static constexpr int client_height       = static_cast<int>(WindowHeight);         // Total window height

    static constexpr int window_width        = static_cast<int>(client_width  + 18);   // Total window width
    static constexpr int window_height       = static_cast<int>(client_height + 42);   // Total window height

  public:
    using point_00_type            = typename rectangle_00_type::point_type;
    using point_01_type            = typename rectangle_01_type::point_type;
    using point_02_type            = typename rectangle_02_type::point_type;
    using rectangle_tuple_ref_type = std::reference_wrapper<rectangle_tuple_type>;

    mandelbrot_discovery() = default;

    mandelbrot_discovery(const mandelbrot_discovery&) = delete;
    mandelbrot_discovery(mandelbrot_discovery&&) noexcept = delete;

    ~mandelbrot_discovery() = default;

    auto operator=(const mandelbrot_discovery&) -> mandelbrot_discovery = delete;
    auto operator=(mandelbrot_discovery&&) noexcept -> mandelbrot_discovery = delete;

    static constexpr auto default_style() noexcept -> ::DWORD
    {
      return static_cast<::DWORD>(WS_MINIMIZEBOX | WS_CAPTION | WS_POPUP | WS_SYSMENU);
    }

    auto get_handle_to_window() const noexcept -> const HWND { return my_handle_to_window; }

    auto create_window(      ::HINSTANCE hinst,                                                      // Handle to window instance
                       const ::DWORD     basic_style    = default_style(),                           // Window basic style
                       const ::DWORD     extended_style = static_cast<::DWORD>(UINT8_C(0))) -> bool  // Window extended style
    {
      my_handle_to_instance = hinst;

      using local_window_type = mandelbrot_discovery;

      {
        ::WNDCLASS window_class { };

        window_class.style         =  static_cast<::UINT>(CS_HREDRAW | CS_VREDRAW | CS_OWNDC);
        window_class.lpfnWndProc   =  my_window_callback;
        window_class.cbClsExtra    =  static_cast<int>(INT8_C(0));
        window_class.cbWndExtra    =  static_cast<int>(INT8_C(0));
        window_class.hInstance     =  my_handle_to_instance;
        window_class.hIcon         =  ::LoadIcon(my_handle_to_instance, MAKEINTRESOURCE(local_window_type::icon_id()));
        window_class.hCursor       =  ::LoadCursor(nullptr, IDC_ARROW);
        window_class.hbrBackground =  reinterpret_cast<::HBRUSH>(COLOR_APPWORKSPACE);
        window_class.lpszMenuName  =  nullptr;
        window_class.lpszClassName =  local_window_type::window_title();

        const auto register_class_result = ::RegisterClass(&window_class);

        static_cast<void>(register_class_result);
      }

      my_handle_to_window = ::CreateWindowEx(extended_style,
                                             local_window_type::window_title(),
                                             local_window_type::window_title(),
                                             basic_style,
                                             screen_coordinate_x,
                                             screen_coordinate_y,
                                             window_width,
                                             window_height,
                                             nullptr,
                                             nullptr,
                                             my_handle_to_instance,
                                             nullptr);

      bool create_window_is_ok { my_handle_to_window != nullptr };

      if(create_window_is_ok)
      {
        // Show the window.
        const bool
          redraw_window_is_ok
          {
            ::RedrawWindow(my_handle_to_window, nullptr, nullptr, static_cast<::UINT>(UINT8_C(0))) == TRUE
          };

        create_window_is_ok = (redraw_window_is_ok && create_window_is_ok);

        const bool show_window_result_is_ok { ::ShowWindow(my_handle_to_window, SW_SHOW) == TRUE };

        create_window_is_ok = (show_window_result_is_ok && create_window_is_ok);
      }

      const ::HWND handle_to_active_window { ::GetActiveWindow() };

      const bool
        create_window_result
        {
              create_window_is_ok
          && (handle_to_active_window != nullptr)
          && (my_handle_to_window == handle_to_active_window)
        };

      return create_window_result;
    }

    static auto instance() -> mandelbrot_discovery&
    {
      static mandelbrot_discovery mandelbrot_discovery_instance { };

      return mandelbrot_discovery_instance;
    }

    static auto win_main(::HINSTANCE hinst) -> int
    {
      // This implements the standard Win32 API main function.

      using local_window_type = mandelbrot_discovery;

      // Create the window.
      const bool create_window_is_ok = local_window_type::instance().create_window(hinst);

      static_cast<void>(create_window_is_ok);

      // Allocate a console window
      const auto result_alloc_console_is_ok = (::AllocConsole() == TRUE);

      if(result_alloc_console_is_ok)
      {
        constexpr ::UINT
          pos_x
          {
            static_cast<::UINT>
            (
                (screen_coordinate_x + client_width) + static_cast<int>(INT8_C(24))
            )
          };

        ::SetWindowPos(::GetConsoleWindow(), nullptr, pos_x, 64, 768, 512, SWP_NOZORDER);

        // Get handles to the standard output and input.
        console_output() = ::GetStdHandle(STD_OUTPUT_HANDLE);
        console_input () = ::GetStdHandle(STD_INPUT_HANDLE);
      }

      // Start the thread process.
      my_thread = std::thread(thread_process);

      bool get_message_is_ok { true };

      // Enter the Windows message loop.
      while(get_message_is_ok)
      {
        ::MSG message { };

        const auto peek_msg_result =
          ::PeekMessage(&message,
                        nullptr,
                        static_cast<::UINT>(UINT8_C(0)),
                        static_cast<::UINT>(UINT8_C(0)),
                        static_cast<::UINT>(PM_NOREMOVE));

        const auto peek_msg_has_message = (peek_msg_result == TRUE);

        if(!peek_msg_has_message)
        {
          ::Sleep(static_cast<::DWORD>(UINT8_C(50)));
        }
        else
        {
          ::Sleep(static_cast<::DWORD>(UINT8_C(0)));

          const ::BOOL
            get_message_result
            {
              ::GetMessage(&message, nullptr, static_cast<::UINT>(UINT8_C(0)), static_cast<::UINT>(UINT8_C(0)))
            };

          get_message_is_ok = (get_message_result == TRUE);

          if(get_message_is_ok)
          {
            // Process all incoming Win32 API messages (via standard Windows message pump).

            const bool translate_message_is_ok { ::TranslateMessage(&message) == TRUE };
            const bool dispatch_message_is_ok  { ::DispatchMessage (&message) == TRUE };

            static_cast<void>(translate_message_is_ok);
            static_cast<void>(dispatch_message_is_ok);
          }
        }
      }

      if(result_alloc_console_is_ok)
      {
        static_cast<void>(::FreeConsole());

        static_cast<void>(::CloseHandle(console_input()));
        static_cast<void>(::CloseHandle(console_output()));
      }

      return static_cast<int>(INT8_C(0));
    }

    static auto set_rectangle_tuple(rectangle_tuple_type& ref_to_rectangle_tuple) noexcept -> void
    {
      my_ref_to_rectangle_tuple = ref_to_rectangle_tuple;
    }

  private:
    ::HWND                          my_handle_to_window   { nullptr };
    ::HINSTANCE                     my_handle_to_instance { nullptr };

    static point_00_type            my_rectangle_center_00;
    static point_01_type            my_rectangle_center_01;
    static point_02_type            my_rectangle_center_02;
    static rectangle_tuple_ref_type my_ref_to_rectangle_tuple;

    static std::thread              my_thread;
    static std::atomic<bool>        my_thread_wants_exit;
    static std::atomic<bool>        my_thread_did_exit;
    static std::atomic<bool>        my_thread_wait_for_new_set_click;
    static value_00_type            my_mandelbrot_zoom_factor_00;
    static value_01_type            my_mandelbrot_zoom_factor_01;
    static value_02_type            my_mandelbrot_zoom_factor_02;
    static std::uint_fast32_t       my_mandelbrot_iterations;

    static constexpr auto window_title() noexcept -> const char* { return WindowTitle; }
    static constexpr auto icon_id() noexcept -> int { return IconId; }

    auto get_handle_to_instance() const noexcept -> const ::HINSTANCE { return my_handle_to_instance; }

    static auto default_rectangle_tuple() noexcept -> rectangle_tuple_type&;

    static auto console_input () -> ::HANDLE&;
    static auto console_output() -> ::HANDLE&;

    static auto console_sync_mtx() -> std::mutex&;

    static auto set_wait_for_click_response(const bool set_on) noexcept -> bool
    {
      my_thread_wait_for_new_set_click.store(set_on);

      return (get_wait_for_click_response() == set_on);
    }

    static auto get_wait_for_click_response() noexcept -> bool
    {
      return my_thread_wait_for_new_set_click.load();
    }

    static auto zoom_factor_p10() -> int { return ilogb(my_mandelbrot_zoom_factor_02); };

    static auto rectangle_tuple_index() -> int
    {
      const int zoom { zoom_factor_p10() };

      return ((zoom <= 20) ? 0 : (zoom <= 80) ? 1 : 2);
    };

    template<typename MandelbrotGeneratorType>
    static auto mandelbrot_iterate_engine_worker(MandelbrotGeneratorType& mandelbrot_generator) -> void
    {
      util::text::text_output_alloc_console text_out(mandelbrot_discovery::write_string);

      using stopwatch_type = ::stopwatch<std::chrono::high_resolution_clock>;

      stopwatch_type my_stopwatch { };

      // Generate the Mandelbrot image. Note: The filename suffix
      // will be provided by the interface.

            ckormanyos::mandelbrot::color::color_stretch_histogram_method local_color_stretches;
      const ckormanyos::mandelbrot::color::color_functions_bw             local_color_functions;

      mandelbrot_generator.generate_mandelbrot_image("mandelbrot_zooming",
                                                      local_color_functions,
                                                      local_color_stretches,
                                                      text_out);

      const float iteration_time { stopwatch_type::elapsed_time<float>(my_stopwatch) };

      const std::string
        str_iteration_time
        {
          [&iteration_time]()
          {
            std::stringstream strm { };

            strm << std::fixed << std::setprecision(1) << iteration_time;

            return strm.str();
          }()
        };

      write_string("mandelbrot_zoom: " + std::to_string(zoom_factor_p10())        + "\n");
      write_string("mandelbrot_iter: " + std::to_string(my_mandelbrot_iterations) + "\n");
      write_string("iteration_time : " + str_iteration_time                       + "s\n\n");
    }

    static auto mandelbrot_iterate_engine_00() -> void
    {
      constexpr auto MANDELBROT_CALCULATION_PIXELS_X = static_cast<std::uint_fast32_t>(768);
      constexpr auto MANDELBROT_CALCULATION_PIXELS_Y = static_cast<std::uint_fast32_t>(768);

      using mandelbrot_generator_00_type =
        ckormanyos::mandelbrot::mandelbrot_generator_trivial<value_00_type>;

      using local_mandelbrot_config_00_type =
        ckormanyos::mandelbrot::mandelbrot_config<value_00_type,
                                                  typename mandelbrot_generator_00_type::my_iteration_numeric_type,
                                                  static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_PIXELS_X),
                                                  static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_PIXELS_Y)>;

      const rectangle_00_type& local_rectangle_00_ref { std::get<0>(my_ref_to_rectangle_tuple.get()) };

      local_mandelbrot_config_00_type
        mandelbrot_config_object_00
        (
          local_rectangle_00_ref.center().get_x() - local_rectangle_00_ref.dx_half(),
          local_rectangle_00_ref.center().get_x() + local_rectangle_00_ref.dx_half(),
          local_rectangle_00_ref.center().get_y() - local_rectangle_00_ref.dy_half(),
          local_rectangle_00_ref.center().get_y() + local_rectangle_00_ref.dy_half(),
          my_mandelbrot_iterations
        );

      mandelbrot_generator_00_type gen_00 { mandelbrot_config_object_00 };

      mandelbrot_iterate_engine_worker(gen_00);
    }

    static auto mandelbrot_iterate_engine_01() -> void
    {
      constexpr auto MANDELBROT_CALCULATION_PIXELS_X = static_cast<std::uint_fast32_t>(768);
      constexpr auto MANDELBROT_CALCULATION_PIXELS_Y = static_cast<std::uint_fast32_t>(768);

      using mandelbrot_generator_01_type =
        ckormanyos::mandelbrot::mandelbrot_generator_trivial<value_01_type>;

      using local_mandelbrot_config_01_type =
        ckormanyos::mandelbrot::mandelbrot_config<value_01_type,
                                                  typename mandelbrot_generator_01_type::my_iteration_numeric_type,
                                                  static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_PIXELS_X),
                                                  static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_PIXELS_Y)>;

      const rectangle_01_type& local_rectangle_01_ref { std::get<1>(my_ref_to_rectangle_tuple.get()) };

      local_mandelbrot_config_01_type
        mandelbrot_config_object_01
        (
          local_rectangle_01_ref.center().get_x() - local_rectangle_01_ref.dx_half(),
          local_rectangle_01_ref.center().get_x() + local_rectangle_01_ref.dx_half(),
          local_rectangle_01_ref.center().get_y() - local_rectangle_01_ref.dy_half(),
          local_rectangle_01_ref.center().get_y() + local_rectangle_01_ref.dy_half(),
          my_mandelbrot_iterations
        );

      mandelbrot_generator_01_type gen_01 { mandelbrot_config_object_01 };

      mandelbrot_iterate_engine_worker(gen_01);
    }

    static auto mandelbrot_iterate_engine_02() -> void
    {
      constexpr auto MANDELBROT_CALCULATION_PIXELS_X = static_cast<std::uint_fast32_t>(768);
      constexpr auto MANDELBROT_CALCULATION_PIXELS_Y = static_cast<std::uint_fast32_t>(768);

      using mandelbrot_generator_02_type =
        ckormanyos::mandelbrot::mandelbrot_generator_perturbative<value_02_type>;

            ckormanyos::mandelbrot::color::color_stretch_histogram_method local_color_stretches;
      const ckormanyos::mandelbrot::color::color_functions_bw             local_color_functions;

      using local_mandelbrot_config_02_type =
        ckormanyos::mandelbrot::mandelbrot_config<value_02_type,
                                                  typename mandelbrot_generator_02_type::my_iteration_numeric_type,
                                                  static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_PIXELS_X),
                                                  static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_PIXELS_Y)>;

      const rectangle_02_type& local_rectangle_02_ref { std::get<2>(my_ref_to_rectangle_tuple.get()) };

      local_mandelbrot_config_02_type
        mandelbrot_config_object_02
        (
          local_rectangle_02_ref.center().get_x() - local_rectangle_02_ref.dx_half(),
          local_rectangle_02_ref.center().get_x() + local_rectangle_02_ref.dx_half(),
          local_rectangle_02_ref.center().get_y() - local_rectangle_02_ref.dy_half(),
          local_rectangle_02_ref.center().get_y() + local_rectangle_02_ref.dy_half(),
          my_mandelbrot_iterations
        );

      mandelbrot_generator_02_type gen_02 { mandelbrot_config_object_02 };

      mandelbrot_iterate_engine_worker(gen_02);
    }

    static auto CALLBACK my_window_callback(::HWND   handle_to_window,
                                            ::UINT   message,
                                            ::WPARAM w_param,
                                            ::LPARAM l_param) -> ::LRESULT
    {
      // This is the standard Win32 API callback function.

      if(message == static_cast<::UINT>(WM_PAINT))
      {
        ::PAINTSTRUCT ps { };

        const ::HDC hdc { BeginPaint(handle_to_window, &ps) };

        // Load JPEG image.
        const ::HBITMAP hBitmap
        {
          load_jpeg_image
          (
            (my_mandelbrot_zoom_factor_00 > 1) ? L"mandelbrot_zooming.jpg"
                                               : L"mandelbrot_MANDELBROT_01_FULL.jpg"
          )
        };

        // Draw the image onto the window's client area
        ::HDC hdcMem { CreateCompatibleDC(hdc) };
        SelectObject(hdcMem, hBitmap);

        ::BITMAP bitmap { };

        static_cast<void>(::GetObject(hBitmap, static_cast<int>(sizeof(bitmap)), &bitmap));

        const auto result_stretch =
          StretchBlt
          (
            hdc,
            static_cast<int>(INT8_C(0)),
            static_cast<int>(INT8_C(0)),
            static_cast<int>(bitmap.bmWidth),
            static_cast<int>(bitmap.bmHeight),
            hdcMem,
            static_cast<int>(INT8_C(0)),
            static_cast<int>(INT8_C(0)),
            static_cast<int>(bitmap.bmWidth),
            static_cast<int>(bitmap.bmHeight),
            static_cast<::DWORD>(SRCCOPY)
          );

        const auto result_draw_is_ok = (result_stretch == TRUE);

        static_cast<void>(::DeleteDC(hdcMem));
        static_cast<void>(::DeleteObject(hBitmap));

        const auto result_end_paint_is_ok = (::EndPaint(handle_to_window, &ps) == TRUE);

        const auto result_is_ok = (result_draw_is_ok && result_end_paint_is_ok);

        const auto lresult =
          static_cast<::LRESULT>
          (
            result_is_ok ? static_cast<::LRESULT>(INT8_C(0)) : static_cast<::LRESULT>(INT8_C(-1))
          );

        return lresult;
      }

      if(message == static_cast<::UINT>(WM_LBUTTONDOWN))
      {
        ::LRESULT lresult { };

        for(auto     idx = static_cast<unsigned>(UINT8_C(0));
                   ((idx < static_cast<unsigned>(UINT8_C(40))) && (!get_wait_for_click_response()));
                   ++idx)
        {
          ::Sleep(static_cast<::DWORD>(UINT8_C(5)));
        }

        if(get_wait_for_click_response())
        {
          // Display the x,y coordinate.

          const int pixel_x
          {
            static_cast<int>(static_cast<::WORD>(static_cast<::DWORD>(l_param)))
          };

          const int pixel_y
          {
            static_cast<int>(static_cast<::WORD>(static_cast<::DWORD>(l_param) >> static_cast<unsigned>(UINT8_C(16))))
          };

          bool result_is_ok { true };

          result_is_ok = { std::get<0>(my_ref_to_rectangle_tuple.get()).pixel_to_point(pixel_x, pixel_y, my_rectangle_center_00) && result_is_ok };
          result_is_ok = { std::get<1>(my_ref_to_rectangle_tuple.get()).pixel_to_point(pixel_x, pixel_y, my_rectangle_center_01) && result_is_ok };
          result_is_ok = { std::get<2>(my_ref_to_rectangle_tuple.get()).pixel_to_point(pixel_x, pixel_y, my_rectangle_center_02) && result_is_ok };

          if(result_is_ok)
          {
            switch(rectangle_tuple_index())
            {
              case 0:
                result_is_ok = (write_number("x_val  : ", my_rectangle_center_00.get_x())                            && result_is_ok);
                result_is_ok = (write_number("y_val  : ", my_rectangle_center_00.get_y())                            && result_is_ok);
                result_is_ok = (write_number("dx_half: ", std::get<0>(my_ref_to_rectangle_tuple.get()).dx_half(), 3) && result_is_ok);
                result_is_ok = (write_string("\n")                                                                   && result_is_ok);
                break;

            case 1:
              result_is_ok = (write_number("x_val  : ", my_rectangle_center_01.get_x())                            && result_is_ok);
              result_is_ok = (write_number("y_val  : ", my_rectangle_center_01.get_y())                            && result_is_ok);
              result_is_ok = (write_number("dx_half: ", std::get<1>(my_ref_to_rectangle_tuple.get()).dx_half(), 3) && result_is_ok);
              result_is_ok = (write_string("\n")                                                                   && result_is_ok);
              break;

            case 2:
            default:
              result_is_ok = (write_number("x_val  : ", my_rectangle_center_02.get_x())                            && result_is_ok);
              result_is_ok = (write_number("y_val  : ", my_rectangle_center_02.get_y())                            && result_is_ok);
              result_is_ok = (write_number("dx_half: ", std::get<2>(my_ref_to_rectangle_tuple.get()).dx_half(), 3) && result_is_ok);
              result_is_ok = (write_string("\n")                                                                   && result_is_ok);
              break;
            }
          }

          const auto lresult =
            static_cast<::LRESULT>
            (
              result_is_ok ? static_cast<::LRESULT>(INT8_C(0)) : static_cast<::LRESULT>(INT8_C(-1))
            );

          static_cast<void>(set_wait_for_click_response(false));
        }

        return lresult;
      }

      if(message == static_cast<::UINT>(WM_DESTROY))
      {
        // Exit the process thread.
        my_thread_wants_exit.store(true);

        my_thread.join();

        for(auto   i = static_cast<unsigned>(UINT8_C(0));
                   i < static_cast<unsigned>(UINT8_C(200));
                 ++i)
        {
          if(my_thread_did_exit.load())
          {
            break;
          }

          ::Sleep(static_cast<::DWORD>(UINT8_C(5)));
        }

        using local_window_type = mandelbrot_discovery;

        // Clean up the window and exit the program.
        static_cast<void>
        (
          ::UnregisterClass(local_window_type::window_title(),
                            local_window_type::instance().get_handle_to_instance())
        );

        ::PostQuitMessage(static_cast<int>(INT8_C(0)));
      }

      const auto def_window_proc_result = ::DefWindowProc(handle_to_window, message, w_param, l_param);

      return def_window_proc_result;
    }

    static auto thread_process() -> void
    {
      while(my_thread_wants_exit.load() == static_cast<::LONG>(INT8_C(0)))
      {
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<unsigned>(UINT8_C(20))));

        write_string("cmd: ");

        std::string str_cmd { };

        read_string(str_cmd);

        bool do_iterate_and_redraw { };

        if(str_cmd == "set")
        {
          write_string("click to set a point\n");

          static_cast<void>(set_wait_for_click_response(true));

          while(get_wait_for_click_response())
          {
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<unsigned>(UINT8_C(20))));
          }
        }
        else if(   (str_cmd.find("itr", static_cast<std::string::size_type>(UINT8_C(0))) == static_cast<std::string::size_type>(UINT8_C(0)))
                && (str_cmd.length() > static_cast<std::string::size_type>(UINT8_C(3))))
        {
          std::uint_fast32_t iter { };

          const auto result_of_iter_from_chars =
            std::from_chars
            (
              str_cmd.c_str() + static_cast<std::string::size_type>(UINT8_C(3)),
              str_cmd.c_str() + str_cmd.length(),
              iter
            );

          const auto err_code = result_of_iter_from_chars.ec;

          if(err_code == std::errc())
          {
            my_mandelbrot_iterations = iter;

            write_string("new max. iterations: " + std::to_string(iter) + "\n");
          }
        }
        else if(str_cmd == "calc")
        {
          // Rescale and re-center the rectangles.

          util::caller::for_each_in_tuple
          (
            my_ref_to_rectangle_tuple.get(),
            [](auto& obj)
            {
              obj.operator/=(10);
            }
          );

          my_mandelbrot_zoom_factor_00 *= 10;
          my_mandelbrot_zoom_factor_01 *= 10;
          my_mandelbrot_zoom_factor_02 *= 10;

          std::get<0>(my_ref_to_rectangle_tuple.get()).recenter(my_rectangle_center_00);
          std::get<1>(my_ref_to_rectangle_tuple.get()).recenter(my_rectangle_center_01);
          std::get<2>(my_ref_to_rectangle_tuple.get()).recenter(my_rectangle_center_02);

          // Set the flag to redraw the client window with the new JPEG.
          // The redrawing will occur below.
          do_iterate_and_redraw = true;
        }
        else if(str_cmd == "out")
        {
          // Rescale and re-center the rectangles.

          util::caller::for_each_in_tuple
          (
            my_ref_to_rectangle_tuple.get(),
            [](auto& obj)
            {
              obj.operator*=(10);
            }
          );

          my_mandelbrot_zoom_factor_00 /= 10;
          my_mandelbrot_zoom_factor_01 /= 10;
          my_mandelbrot_zoom_factor_02 /= 10;

          // Set the flag to redraw the client window with the new JPEG.
          // The redrawing will occur below.
          do_iterate_and_redraw = true;
        }
        else if(str_cmd == "redo")
        {
          // Set the flag to redraw the client window with the new JPEG.
          // The redrawing will occur below.
          do_iterate_and_redraw = true;
        }
        else if((str_cmd == "help") || (str_cmd == "?"))
        {
          static_cast<void>(print_commands());
        }
        else if(str_cmd == "exit")
        {
          my_thread_wants_exit.store(true);

          using local_window_type = mandelbrot_discovery;

          static_cast<void>
          (
            ::PostMessage(local_window_type::instance().get_handle_to_window(), WM_CLOSE, 0, 0)
          );
        }

        if(do_iterate_and_redraw)
        {
          do_iterate_and_redraw = false;

          // Perform the mandelbrot iteration with the iterate-engine.

          const int local_rectangle_tuple_index { rectangle_tuple_index() };

          if     (local_rectangle_tuple_index == 0) { mandelbrot_iterate_engine_00(); }
          else if(local_rectangle_tuple_index == 1) { mandelbrot_iterate_engine_01(); }
          else                                      { mandelbrot_iterate_engine_02(); }

          // Redraw the client window with the new JPEG.
          using local_window_type = mandelbrot_discovery;

          ::RECT rect { };

          ::GetClientRect(local_window_type::instance().get_handle_to_window(), &rect);

          ::RedrawWindow(local_window_type::instance().get_handle_to_window(), &rect, nullptr, RDW_INVALIDATE);
        }
      }

      my_thread_did_exit.store(true);
    }

    static auto load_jpeg_image(const wchar_t* filename) -> HBITMAP
    {
      // Load JPEG image using WIC.

      ::IWICImagingFactory*    pFactory   { nullptr };
      ::IWICBitmapDecoder*     pDecoder   { nullptr };
      ::IWICBitmapFrameDecode* pFrame     { nullptr };
      ::IWICFormatConverter*   pConverter { nullptr };

      static_cast<void>(::CoInitialize(nullptr));

      static_cast<void>
      (
        ::CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory))
      );

      pFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
      pDecoder->GetFrame(static_cast<::UINT>(UINT8_C(0)), &pFrame);
      pFactory->CreateFormatConverter(&pConverter);

      pConverter->Initialize(pFrame,
                             GUID_WICPixelFormat32bppPBGRA,
                             WICBitmapDitherTypeNone,
                             nullptr,
                             0.0F,
                             WICBitmapPaletteTypeMedianCut);

      ::UINT width  { };
      ::UINT height { };

      pFrame->GetSize(&width, &height);

      const ::DWORD header_area
      {
        static_cast<::DWORD>
        (
          static_cast<::DWORD>(width) * static_cast<::DWORD>(height) * static_cast<::DWORD>(UINT8_C(4))
        )
      };

      ::BITMAPINFOHEADER
        bi
        {
           static_cast<::DWORD>(sizeof(::BITMAPINFOHEADER)),
          +static_cast<::LONG>(width),
          -static_cast<::LONG>(height),
           static_cast<::WORD>(UINT8_C(1)),
           static_cast<::WORD>(UINT8_C(32)),
           static_cast<::DWORD>(BI_RGB),
           header_area,
           static_cast<::LONG>(INT8_C(0)),
           static_cast<::LONG>(INT8_C(0)),
           static_cast<::DWORD>(UINT8_C(0)),
           static_cast<::DWORD>(UINT8_C(0))
        };

      void* pixels { nullptr };

      ::HBITMAP hBitmap
      {
        ::CreateDIBSection
        (
          nullptr,
          static_cast<::BITMAPINFO*>(static_cast<void*>(&bi)),
          DIB_RGB_COLORS,
          &pixels,
          nullptr,
          static_cast<::DWORD>(UINT8_C(0))
        )
      };

      pConverter->CopyPixels(nullptr,
                             static_cast<::UINT>(width * static_cast<::UINT>(UINT8_C(4))),
                             static_cast<::UINT>(header_area),
                             static_cast<::BYTE*>(pixels));

      pFactory->Release();
      pDecoder->Release();
      pFrame->Release();
      pConverter->Release();

      return hBitmap;
    }

    static auto read_string(std::string& str_to_read) -> bool
    {
      constexpr std::size_t input_buffer_size { static_cast<std::size_t>(UINT16_C(2048)) };

      char* input_buffer = new char[input_buffer_size];

      ::DWORD bytes_read { };

      const auto result_read =
        ::ReadConsole(console_input(), input_buffer, input_buffer_size, &bytes_read, nullptr);

      const bool result_read_is_ok = ((result_read == TRUE) && (bytes_read > static_cast<DWORD>(UINT8_C(2))));

      if(result_read_is_ok)
      {
        str_to_read =
          std::string
          (
            input_buffer,
            input_buffer + static_cast<std::size_t>(bytes_read - static_cast<DWORD>(UINT8_C(2)))
          );
      }
      else
      {
        str_to_read.erase();
      }

      return result_read_is_ok;
    }

    static auto print_commands() -> bool
    {
      const bool result_write_is_ok =
      (
           write_string("MandelbrotDiscovery (C) 2024 Christopher Kormanyos.\n")
        && write_string("  help (or ?) - Print this text.\n")
        && write_string("  set         - Select new coordinates with the mouse.\n")
        && write_string("  calc**      - Iterate at the current coordinates and display.\n")
        && write_string("  itrNNNN     - Set max.-iterations, where NNNN is something like 1000\n")
        && write_string("  redo        - Iterate at the current coordinates and scale.\n")
        && write_string("  out         - Backstep one single order of magnification.\n")
      );

      return result_write_is_ok;
    }

    static auto write_string(const std::string& str_to_write) -> bool
    {
      ::DWORD bytes_written { };

      const auto result_write =
        ::WriteConsole
        (
          console_output(),
          str_to_write.c_str(),
          static_cast<::DWORD>(str_to_write.size()),
          &bytes_written,
          nullptr
        );

      const bool result_write_is_ok = (result_write == TRUE);

      return result_write_is_ok;
    }

    template<typename ValueType>
    static auto write_number(const std::string& str_prefix, const ValueType& val, const int prec = -1) -> bool
    {
      using local_value_type = ValueType;

      std::stringstream strm { };

      const std::streamsize my_prec =
        static_cast<std::streamsize>
        (
          (prec == -1) ? std::numeric_limits<local_value_type>::digits10 : prec
        );

      strm << std::setprecision(my_prec) << std::showpos << val;

      const std::string str_val { str_prefix + strm.str() + "\n" };

      return write_string(str_val);
    }
  };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  auto mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::default_rectangle_tuple() noexcept -> typename mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::rectangle_tuple_type&
  {
    static rectangle_00_type
      my_default_rect_00
      {
        point_00_type
        {
          value_00_type { "-0.75" },
          value_00_type { "+0.00" }
        },
        value_00_type { "+1.35" },
        value_00_type { "+1.35" }
      };

    static rectangle_01_type
      my_default_rect_01
      {
        point_01_type
        {
          value_01_type { "-0.75" },
          value_01_type { "+0.00" }
        },
        value_01_type { "+1.35" },
        value_01_type { "+1.35" }
      };

    static rectangle_02_type
      my_default_rect_02
      {
        point_02_type
        {
          value_02_type { "-0.75" },
          value_02_type { "+0.00" }
        },
        value_02_type { "+1.35" },
        value_02_type { "+1.35" }
      };

    static rectangle_tuple_type my_default_rectangle_tuple(my_default_rect_00, my_default_rect_01, my_default_rect_02);

    return my_default_rectangle_tuple;
  }

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  auto mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::console_input() -> HANDLE&
  {
    static ::HANDLE my_handle { };

    return my_handle;
  }

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  auto mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::console_output() -> HANDLE&
  {
    static ::HANDLE my_handle { };

    return my_handle;
  }

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  auto mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::console_sync_mtx() -> std::mutex&
  {
    static std::mutex my_mtx { };

    return my_mtx;
  }

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  std::thread mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_thread;

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  std::atomic<bool> mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_thread_wants_exit { false };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  std::atomic<bool> mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_thread_did_exit { false };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  std::atomic<bool> mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_thread_wait_for_new_set_click;

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  typename mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::point_00_type mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_rectangle_center_00 { };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  typename mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::point_01_type mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_rectangle_center_01 { };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  typename mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::point_02_type mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_rectangle_center_02 { };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  typename mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::rectangle_tuple_ref_type mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_ref_to_rectangle_tuple { default_rectangle_tuple() };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  typename mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::value_00_type mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_mandelbrot_zoom_factor_00 { 1 };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  typename mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::value_01_type mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_mandelbrot_zoom_factor_01 { 1 };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  typename mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::value_02_type mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_mandelbrot_zoom_factor_02 { 1 };

  template<const int   WindowWidth,
           const int   WindowHeight,
           typename    MandelbrotRectangleTupleType,
           const char* WindowTitle,
           const int   IconId,
           const int   ScreenCoordinateX,
           const int   ScreenCoordinateY>
  std::uint_fast32_t mandelbrot_discovery<WindowWidth, WindowHeight, MandelbrotRectangleTupleType, WindowTitle, IconId, ScreenCoordinateX, ScreenCoordinateY>::my_mandelbrot_iterations { static_cast<std::uint_fast32_t>(UINT32_C(400)) };

#endif // MANDELBROT_DISCOVERY_2024_04_12_H
