You can use this tool to generate frames of a zoom sequence of the mandelbrot set, or individual images.

For creating a zoom sequence, execute "zoom_sequence.exe". It asks for the required information, and produces a file, which must be renamed to "inp.txt". Then, execute "mandel.exe". The output will be several bmp files, named in order.

To generate individual images of a specified region of the mandelbrot set:
The folder of the executable "mandel.exe" should contain an input file named "inp.txt".
Each line of the input file should conatain one command in the following format:
\<output filename\> \<image width\> \<image height\> \<real axis min\> \<real axis max\> \<imag. axis min\> \<imag. axis max\> \<iterations\> \<red\> \<blue\> \<green\>

Due to a quartic polynomial shading method, currently the images tend to have a purple-ish shade. I'm working on that as of now.
Feel free to suggest any other methods for shading. Email me at info@keshlabs.in

I have included a sample "inp.txt" file. It produces 7 sample images. 

Hope you like my work :)'
