## Adding Libraries

To compile this project, you'll need to install the correct libraries. I used **MinGW** for compiling, so here’s how you can get set up:

1. Visit the [official SDL GitHub page](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.8).
2. Navigate to the **Releases** section.
3. Download the **SDL2-devel-2.30.8-mingw.zip** file.  
   _Note: This project was built using version 2.30.8 of SDL. It’s recommended that you use the same version to avoid compatibility issues._
4. Once downloaded, extract the files. You’ll find a folder named `x86_64-w64-mingw32`, which contains the necessary `lib` folder.
5. Copy all the `.a` files from this `lib` folder to your project’s `lib` directory.

After setting up the libraries, you’ll be ready to compile the project using MinGW.
