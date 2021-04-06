sudo apt-get install libgtest-dev

sudo apt-get install cmake # install cmake

cd /usr/src/gtest

sudo cmake CMakeLists.txt

sudo make

sudo mkdir /usr/lib/gtest/

cd /usr/src/gtest/lib

sudo cp *.a /usr/lib/gtest/

sudo mkdir /usr/local/lib/gtest/

sudo ln -s /usr/lib/gtest/libgtest.a /usr/local/lib/gtest/libgtest.a

sudo ln -s /usr/lib/gtest/libgtest_main.a /usr/local/lib/gtest/libgtest_main.a
