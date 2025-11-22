# CyberRT-MX
实现 CyberRT


# 环境
```bash
sudo apt-get update
sudo apt-get install uuid-dev
```


```base
cd thirdparty
mkdir foonathan_memory_vendor/build
cd foonathan_memory_vendor/build
cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS/install -DBUILD_SHARED_LIBS=ON
cmake --build . --target install
```

```bash
git pull   
git submodule sync --recursive
git submodule update --init --recursive

cd thirdparty
mkdir Fast-DDS/build
cd Fast-DDS/build
cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS/install -DTHIRDPARTY=FORCE
cmake --build . --target install
```