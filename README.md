# How to use LibOTE with OKVS on Ubuntu
```shell
git clone https://github.com/ridiculousfish/libdivide.git
cd libdivide
cmake .
make -j
sudo make install
git clone --recursive https://github.com/osu-crypto/libOTe.git
cd libOTE
mkdir -p out/build/linux
cmake -S . -B out/build/linux -DENABLE_ASAN=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo -DFETCH_AUTO=ON -DENABLE_RELIC=ON -DENABLE_ALL_OT=ON -DCOPROTO_ENABLE_BOOST=ON -DENABLE_SILENT_VOLE=ON -DENABLE_SSE=ON
cmake --build out/build/linux 
su (enter your password)
cmake --install out/build/linux 
```

# Call OKVS
```shell
git clone https://github.com/ShallMate/OKVS.git
cd OKVS
mkdir build
cd build
cmake ..
make
./main
```
