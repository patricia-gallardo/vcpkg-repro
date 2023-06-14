# Vcpkg repro steps for https://github.com/microsoft/vcpkg/issues/31962

## Ubuntu 22.04

### Get deps

~~~bash
pip3 install wheel setuptools
pip3 install ninja --upgrade
~~~

~~~bash
sudo apt-get update && sudo apt-get install -y curl zip unzip tar libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libudev-dev clang-12 make ninja-build cmake autoconf libtool mesa-common-dev libglu1-mesa-dev libfreetype6-dev libopenal-dev libsndfile1-dev
~~~

### Clean up previous build

~~~bash
rm -rf build
~~~

### CMake configure first time: WILL FAIL

~~~bash
cmake --preset linux-gcc-11 -DCMAKE_BUILD_TYPE=Debug
~~~

~~~
ERROR

CMake Error at build/linux-gcc-11/vcpkg_installed/x64-linux/share/sfml/SFMLConfig.cmake:144 (message):
SFML found but some of its dependencies are missing ( OpenGL FreeType)
Call Stack (most recent call first):
build/linux-gcc-11/_deps/vcpkg-src/scripts/buildsystems/vcpkg.cmake:852 (_find_package)
lib/CMakeLists.txt:1 (find_package)


CMake Error at build/linux-gcc-11/_deps/vcpkg-src/scripts/buildsystems/vcpkg.cmake:852 (_find_package):
Found package configuration file:

    /mnt/c/Users/patricia/Code/vcpkg-repro/build/linux-gcc-11/vcpkg_installed/x64-linux/share/sfml/SFMLConfig.cmake

but it set SFML_FOUND to FALSE so package "SFML" is considered to be NOT
FOUND.
Call Stack (most recent call first):
lib/CMakeLists.txt:1 (find_package)


-- Configuring incomplete, errors occurred!
See also "/mnt/c/Users/patricia/Code/vcpkg-repro/build/linux-gcc-11/CMakeFiles/CMakeOutput.log".
See also "/mnt/c/Users/patricia/Code/vcpkg-repro/build/linux-gcc-11/CMakeFiles/CMakeError.log".
~~~

### CMake configure second time: WILL PASS

~~~bash
cmake --preset linux-gcc-11 -DCMAKE_BUILD_TYPE=Debug
~~~

### CMake Build

~~~bash
cmake --build --preset linux-gcc-build-11 --config Debug
~~~

### CMake Run tests

~~~bash
ctest --preset linux-gcc-test-11 -C Debug
~~~

## MacOS

### Clean up previous build

~~~bash
rm -rf build
~~~

### CMake configure first time: WILL FAIL

~~~bash
cmake --preset osx -DCMAKE_BUILD_TYPE=Debug
~~~

~~~
-- Found SFML 2.5.1 in /Users/patricia-gallardo/Code/vcpkg-repro/build/osx/vcpkg_installed/x64-osx/share/sfml
CMake Error at build/osx/vcpkg_installed/x64-osx/share/sfml/SFMLConfig.cmake:144 (message):
  SFML found but some of its dependencies are missing ( OpenGL FreeType)
Call Stack (most recent call first):
  build/osx/_deps/vcpkg-src/scripts/buildsystems/vcpkg.cmake:852 (_find_package)
  lib/CMakeLists.txt:1 (find_package)


CMake Error at build/osx/_deps/vcpkg-src/scripts/buildsystems/vcpkg.cmake:852 (_find_package):
  Found package configuration file:

    /Users/patricia-gallardo/Code/vcpkg-repro/build/osx/vcpkg_installed/x64-osx/share/sfml/SFMLConfig.cmake

  but it set SFML_FOUND to FALSE so package "SFML" is considered to be NOT
  FOUND.
Call Stack (most recent call first):
  lib/CMakeLists.txt:1 (find_package)


-- Configuring incomplete, errors occurred!
See also "/Users/patricia-gallardo/Code/vcpkg-repro/build/osx/CMakeFiles/CMakeOutput.log".
See also "/Users/patricia-gallardo/Code/vcpkg-repro/build/osx/CMakeFiles/CMakeError.log".
~~~

### CMake configure second time: WILL PASS

~~~bash
cmake --preset osx -DCMAKE_BUILD_TYPE=Debug
~~~

### CMake Build

~~~bash
cmake --build --preset osx-build --config Debug
~~~

### CMake Run tests

~~~bash
ctest --preset osx-test -C Debug
~~~