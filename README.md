<a name="readme-top"></a>

<div align="center">
  <a href="https://github.com/jonahwoodley/Chip8-Emulator">
    <img src="https://github.com/user-attachments/assets/94856234-31a2-48c5-869f-573f64e4186f" alt="Logo" width="140" height="140">
  </a>
  <h3 align="center">Chip8 Emulator</h3>

  <p align="center">
    Chip-8 is an interpreted programming language from the 1970s, originally designed for creating simple games on 8-bit systems. It's now popular for learning emulation and low-level programming due to its simplicity and small instruction set.
  </p>
</div>

## About The Project
<div align="center">
  <img src="https://github.com/user-attachments/assets/4986475f-cf6e-48b8-bde8-92c8470522be" alt="Project Banner">
</div>

<br />
This Chip-8 emulator was my first project in C++ (you can probably tell by the awful code :D ), created to learn low-level programming and understand how emulation works. I wanted to explore how simple hardware interprets instructions and handles memory, and building this "emulator" was a great way to gain that knowledge.

### Features

- **Adjustable CPU Cycles Per Frame:**
  Control the speed of the emulation by tweaking how many cycles are executed each frame.

- **Audio**
  Most Chip-8 ROMs don't have audio but some do, the audio currently is very temperamental at the moment.
 
- **Changing ROM's**
  You can change ROM by going to the menu toolbar selecting file then open rom, no need to keep reopening the executable

- **Memory Viewer**
  Visualize the memory used by the Chip-8 (4kb total RAM)

- **Stack Viewer**
  Monitor the contents of the call stack.

- **V Register Viewer**
  Inspect the Chip-8's registers (V0-VF)


### TODO
There are several features and improvements planned for future updates to this project:

- **Switch to CMake**: Use CMake as the build system
- **Cross-Platform Support**: Ensure the emulator works on Linux and macOS.
- **Additional Settings**: Add more configuration options, such as changing the game window size and adjusting FPS.
- **Sound Emulation**: Implement more accurate sound emulation for games that use it.
- **Save States**: Save and load the emulator’s state for quicker testing and game progression.
- **Debugger**: Build an integrated debugger for easier troubleshooting and development.
- **Documentation**: Document all the code.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Building The Project
This project has only been tested on Windows, using **MinGW64** as the compiler, if you only want to run the program you can download the pre-built binary from the releases tab. Follow the steps below to build and compile the project:

1. **Install MinGW64**: Ensure you have MinGW64 installed on your system. You can download it from [here](https://www.mingw-w64.org/downloads/#mingw-w64-builds).

2. **Add SDL2 Libraries**:
   - Visit the [official SDL GitHub page](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.8).
   - Download the **SDL2-devel-2.30.8-mingw.zip** file.
   - Extract the files, and find the `x86_64-w64-mingw32` folder.
   - Copy all the `.a` files from the `lib` folder inside `x86_64-w64-mingw32` to your project’s `lib` directory.
   - Copy the **SDL2.dll** from the `bin` folder to your `build` directory. This DLL is required to run the emulator.

3. **Run Make**:  
   In the root of the project, run the `make` command to compile the emulator. If the libraries and dependencies are set up correctly, the executable will be built.

4. **Running the Emulator**:  
   Ensure that the **SDL2.dll** file is in the `build` directory when running the executable, or the emulator won’t start properly.


<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## License

Distributed under the MIT License. See `LICENSE` for more information.


## Acknowledgments

A list of resources we found helpful and would like to give credit to.

- [Tobias V, Langhoff Blog](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)
- [Wikipedia](https://en.wikipedia.org/wiki/CHIP-8)
- [Cowgod's Chip-8 Technical Reference](https://en.wikipedia.org/wiki/CHIP-8](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM))
- [CHIP-8 virtual machine specification](https://tonisagrista.com/blog/2021/chip8-spec/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


