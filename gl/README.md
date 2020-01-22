sudo apt install cmake
sudo apt install libgl1-mesa-dev
sudo apt install libx11-dev
sudo apt install libxi-dev
sudo apt install libwayland-dev
sudo apt install libegl1-mesa-dev
sudo apt install libxkbcommon-dev

- Make sure you have cmake installed. Examples:
  - Debian/Ubuntu: apt-get install cmake
  - Fedora: yum install cmake
  - FreeBSD: cd /usr/ports/devel/cmake && make install
  Or directly from their website:
  http://www.cmake.org/cmake/resources/software.html
- Make sure you have the basics for compiling code, such as C compiler
  (e.g., GCC) and the make package.
- Also make sure you have packages installed that provide the relevant
  header files for opengl (e.g., libgl1-mesa-dev on Debian/Ubuntu) and
  the chosen backend :
  - X11: x11 (e.g., libx11-dev, libxrandr-devel on Debian/Ubuntu) and
  XInput (libxi-dev / libXi-devel)
  - Wayland: wayland (e.g., libwayland-dev and libegl1-mesa-dev on
  Debian/Ubuntu) and xkbcommon (libxkbcommon-dev /libxkbcommon-devel)
- Run 'cmake .' (or 'cmake . -DFREEGLUT_WAYLAND=ON' for Wayland) in the
  freeglut directory to generate the makefile.
- Run 'make' to build, and 'make install' to install freeglut.
- If you wish to change any build options run 'ccmake .'



sudo apt install cmake libx11-dev xorg-dev libglu1-mesa-dev freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev
