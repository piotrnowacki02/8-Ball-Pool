
# 8 Ball Pool - pool table simulator

8 Ball Pool is a pool table simulator that tries to realistically replicates ball movement, sounds and interactions with the environment. The project is developed in C++ and utilizes the SFML library for graphics and physics simulation.


I was developing it mostly to better understand OOP.


## Run Locally

You need to have c++ compiler and cmake already installed.
I was using dependencies from Microsoft Visual Studio:
 - Desktop development with C++
 - C++ CMake tools for Windows
 - Windows 10 SDK


Clone the project

```bash
  git clone https://github.com/piotrnowacki02/8-Ball-Pool.git
```

Go to the project directory

```bash
  cd 8-Ball-Pool
```

Create a build directory

```bash
  mkdir build
  cd build
```

Generate Visual Studio project files

```bash
  cmake .. -G "Visual Studio 17 2022" -A x64
```

Build the project

```bash
  cmake --build . --config Release
```

To run the project i usually just click the icon "launch" but you can also do it from the terminal go to the build and debug directory and type
```bash
  .\Gra.exe
```



