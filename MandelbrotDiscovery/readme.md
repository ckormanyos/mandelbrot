MandelbrotDiscovery
==================

The `MandelbrotDiscovery` program allows for semi-automated, mouse and command-driven
dives into the Mandelbrot fractal world. Using simple commands like **set**, **calc**
and more it is possible to click on a point and subsequently
calculate the next magnification order at that point.

In this way, you can conveniently dive deeper and deeper
into the Mandelbrot set in a guided fashion.

## Using the Program

Begin by starting `MandelbrotDiscovery.exe`. It is a Win32-API-based program.
Zooming is accomplished with commands entered in the command window
in combination with mouse-clicks in the client area of the Mandelbrot image window.

### The Startup Windows

Upon startup, you should see the default Mandelbrot image. It is a square, gray-tone JPEG
having $768{\times}768$ pixels. The Mandelbrot image window is
initially located on the left. A secondary console-based read/write command
window should appear to the right. These windows can be moved around based
on client preference during the course of program operation.

The startup windows are shown in the image below.

![](https://github.com/ckormanyos/mandelbrot/blob/main/images/discovery/mandelbrot_discovery_startup.jpg)

### Use the Commands **set** and **calc**

The console accepts input with its prompt **cmd:**. To get started diving,
enter the command **set**. Then navigate with the mouse to any given point
in the client area of the Mandelbrot image window. Left-click the point.
The clicked-on coordinates will be printed in the console.
The most-recently clicked-on coordinates are expressed as `x_val` and `y_val`.

If a different point is desired to be selected,
simply click on the console again and enter the command **set**.
Then click in the client area of the Mandelbrot image window again.
In this way, try to obtain the coordinates that seem to be the right ones
for the upcoming magnification and calculation.

Once suitable coordinates have been set, it is time to magnify and calculate.
The upcoming calculation will zoom by a factor of $10$, calculate the new image
and display it.

Click on the console itself again to select it as the active input window.
Enter the command **calc**. The Mandelbrot calculation will begin.
Progress is reported on the output console. As previously mentioned,
the **calc** command proceeds to magnify the picture about its center-point
by a factor of $10$. The center point that is used is the exact point
previously selected with **set** command and its subsequent mouse-click.

The exact command sequence is shown in the image of the console below.

![](https://github.com/ckormanyos/mandelbrot/blob/main/images/discovery/mandelbrot_discovery_set_calc_commands.jpg)

### Our First Magnification

The result of our first **set** and **calc** command sequence is shown below.

![](https://github.com/ckormanyos/mandelbrot/blob/main/images/discovery/mandelbrot_discovery_calc_result.jpg)

### Continue Your Mandelbrot Dive

Iteratively repeat **set** and **calc** command sequences
in combination with mouse-click (upon the **set** command).
In doing so, you will continue your Mandelbrot dive.

Fine tuning can be accomplished with additional commands such as
**itr2000**, **redo** or **out**.

  - The **itrNNNN** command sets the maximum number of iterations to the appended number. The command **itr2000**, for instance, sets the maximum number of iterations to $2,000$. Switch $2,000$ for another number like $40,000$ to obtain a maximum iteration count of $40,000$ and so on.
  - The default iteration count at program start is modestly set to $400$. So don't be surprised if higher iteration counts are required for deeper and deeper dives.
  - The command **redo** simply performs, yet again, the iteration at the coordinate point that is already set. This might be done if, for example, the image was not resolved and the iteration count needs to be increased. You can also exercise the **set** command one or more times prior to exercising the **redo** command.
  - With **out** you can backstep one single order of magnification at the point that has been set and clicked. This can be done repeatedly if a different zoom pathway is desired even after zooming in to a point.
  - So if you've taken a bit of a wrong turn, just zoom **out** one or more times and refine your coordinate search.

### The Results of a Completed Dive

The result of a dive is shown in the image below. In this particular dive,
the iteration ended in a little Mandelbrot figurine at magnification $10^{26}$.
So I panned **out** one order of magnitude in order to retrieve the image.

The coordinates and iteration count retrieved from `MandelbrotDiscovery`
can be supplied to the _real_ `ckormanyos/mandelbrot` program.
Use this program to obtain a higher resolution image once the coordinates
have been identified with `MandelbrotDiscovery`. A special configuration
specifically intended for trying out newly found points is available
in the`ckormanyos/mandelbrot` program. This configuration file is called
[mandelbrot_cfg_MANDELBROT_99_TRY_POINTS.h](https://github.com/ckormanyos/mandelbrot/blob/main/mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_99_TRY_POINTS.h).
This file can be adapted to try out the new point.

We did not really penetrate that deeply into the complex plane
in this particular dive. But a potential point for producing a somewhat fascinating
picture was, nonetheless, characterized.

The result of this dive ended up being:

  - The square image has $768 {\times} 768$ pixels.
  - Centered at the point $(-0.748389448460435356972905199130859375+i~0.164838521607763200186858879533203125)$.
  - Uses a half-width of $1.1{\times}10^{25}$.
  - Computed with $6,000$ iteratons using the internals of Mandelbrot Discovery (`cpp_dec_float` type from [`Boost.Multiprecision`](https://www.boost.org/doc/libs/1_84_0/libs/multiprecision/doc/html/index.html) instantiated with $112$ decimal digits of precision).

![](https://github.com/ckormanyos/mandelbrot/blob/main/images/discovery/mandelbrot_discovery_dive_example.jpg)

### Changing the Resolution

This is TODO both in docs as well as in the program.

## Program Defaults and Dynamic Behavior

This is TODO both in docs as well as in the program.