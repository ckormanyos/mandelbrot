ckormanyos/mandelbrot/MandelbrotDiscovery
==================

The `MandelbrotDiscovery` program allows for semi-automated, mouse and command driven
dives into the Mandelbrot fractal world. Using simple commands like **set**, **calc**
and more it is possible so click on a point and calculate the next magnification order
at that point. In this way it is possible to iteratively dive deeper and deeper
into the Mandelbrot set.

## Using the Program

Begin by starting MandelbrotDiscovery.exe. It is a Win32-API-based program.
Zooming is accomplished with commands entered in the command window
in combination with mouse-clicks in the client area of the Mandelbrot image window.

### The Startup Windows

You should see the default Mandelbrot image. It is a square, gray-tone JPEG
having $768{\times}768$ pixels. The Mandelbrot Mandelbrot image window is
initially located on the left. A secondary console-based read/write command
window should appear to the right. These windows can be moed around based
on client preference during the course of program operation.

The startup windows are shown in the image below.

![](https://github.com/ckormanyos/mandelbrot/blob/main/images/discovery/mandelbrot_discovery_startup.jpg)

### Use the Commands **set** and **calc**

The console accepts input with its prompt **cmd:**. To get started diving,
enter the command **set**. Then navigate with the mouse to any given point
in the client area of the Mandelbrot image window. Left-click the point
and the clicked coordinates will be printed in the console.

The clicked-on coordinates are expressed as `x_val` and `y_val`. If a different point
is desired to be selected, simply click on the console again and enter the command **set**.
Then click in the client area of the Mandelbrot image window again.
Obtain the coordinates that seem to be the right ones for the upcoming
magnification and calculation.

Once suitable coordinates have been set, it is time to magnify and calculate.
The upcoming calculation will zoom by a factor of $10$, calculate the new image
and display it.

Click on the console itself again to select it as the active input window.
Enter the command **calc**. The Mandelbrot calculation will begin with
progress reported to the output console. As previously mentioned,
the **calc** command proceeds to magnify the picture about its center-point
by a factor of $10$. The center point that is used is the exact point
previously selected with **set** command and its subsequent mouse-click.

The exact command sequence is shown in the image of the console below.

![](https://github.com/ckormanyos/mandelbrot/blob/main/images/discovery/mandelbrot_discovery_set_calc_commands.jpg)

### The First Magnification

The result of our first **set** and **calc** command sequence is shown below.

![](https://github.com/ckormanyos/mandelbrot/blob/main/images/discovery/mandelbrot_discovery_calc_result.jpg)

### Continue Your Mandelbrot Dive

Iteratively repeas **set** and **calc** commands in combination with
mouse-click upon the **set** command in order to continue your Mandelbrot dive.

The result of a dive is TDOD.

### Additional Commands

TODO describe **itr2000**, **redo** and **out** commands.

### Changing the Resolution

TODO both in docs as well as in the program.

## Program Defaults and Dynamic Behavior

TODO
