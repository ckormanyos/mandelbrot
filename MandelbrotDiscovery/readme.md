ckormanyos/mandelbrot/MandelbrotDiscovery
==================

The `MandelbrotDiscovery` program allows for semi-automated, mouse and command driven
dives into the Mandelbrot fractal world. Using simple commands like **set**, **calc**
and more it is possible so click on a point and calculate the next magnification order
at that point.

## Using the Program

Begin by starting MandelbrotDiscovery.exe. It is a Win32-API-based program.

### The Startup Windows

The startup windows are shown in the image below.
You should see the default Mandelbrot image in square $768{\times}768$ gray-tones to the left.
A secondary console-based read/write command window should appear to the right.

Command-based click and zoom will be exercised in combination with commands entered in
the command window and mouse-clicks in the client area of the Mandelbrot image window.

![](./images/gallery/mandelbrot_discovery_startup.jpg)


### Use the Commands **set** and **calc**

The console begins with the prompt **cmd:**. Enter the command **set**.
Then navigate with the mouse to any given point in the client area of the Mandelbrot image window.
Left-click the point and the clicked coordinates will be printed in the console.

The clicked-on coordinates are expressed as `x_val` and `y_val`. If a different point
is desired to be selected, simply click on the console again and enter the command **set**.
Then click again and see if the coordinates are the right ones for the upcoming
magnification and calculation.

Once suitable coordinates have been set, it is time to magnify and calculate.

Click on the console itself again to select it as the active input window.
Enter the command **calc**. The Mandelbrot calculation will begin with
progress reported to the output console. The calc command magnifies
the picture at the center-point by a factor of $10$.
The center point used is the point previously selected with **set**
and the mouse-click.

The exact command sequence is shown in the image of the console below.

![](./images/gallery/mandelbrot_discovery_set_calc_commands.jpg)

The result of our first **set** and **calc** command sequence is shown below.

![](./images/gallery/mandelbrot_discovery_calc_result.jpg)

### Continue Your Mandelbrot Dive

Iteratively repeas **set** and **calc** commands in combination with
mouse-click upon the **set** command in order to continue your Mandelbrot dive.

The result of a dive is TDOD.

### Additional Commands

TODO describe **itr2000**, **redo** and **out** commands.

### Changing the Resolution

TODO both in docs as well as in the program.
