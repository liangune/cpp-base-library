mkdir build_windows64
cd build_windows64
cmake -G "Visual Studio 15 2017 Win64"  -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release ../ 