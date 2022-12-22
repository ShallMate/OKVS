# How to use LibOTE with Silent OT on Ubuntu
```shell
git clone --recursive https://github.com/osu-crypto/libOTe.git
cd libOTE
mkdir -p out/build/linux
cmake -S . -B out/build/linux -DENABLE_ASAN=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo -DFETCH_AUTO=ON -DENABLE_RELIC=ON -DENABLE_ALL_OT=ON -DCOPROTO_ENABLE_BOOST=ON -DENABLE_SILENT_VOLE=ON
cmake --build out/build/linux 
su (enter your password)
cmake --install out/build/linux 
```

# Call SilentOT
```shell
git clone https://github.com/ShallMate/SilentOT.git
cd SilentOT
mkdir build
cd build
cmake ..
make
./main
```
