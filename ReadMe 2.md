
### ogre v2.1 构建ios

```
OgrePlatforminformation.h
line98: 删除 'OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS && '
```

```
$cd Ogre  
$mkdir build-ios  
$cmake -D CMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS} -v -stdlib=libc++ -std=c++11" -D BOOST_ROOT=/Users/lvjiaming/WorkSpace/ogre/iOSDependencies/include/boost -D BOOST_INCLUDEDIR=/Users/lvjiaming/WorkSpace/ogre/iOSDependencies/include/boost -D BOOST_LIBRARYDIR=/Users/lvjiaming/WorkSpace/ogre/iOSDependencies/lib -D OGRE_DEPENDENCIES_DIR=/Users/lvjiaming/WorkSpace/ogre/iOSDependencies -D OGRE_BUILD_RENDERSYSTEM_GLES2=1 -D OGRE_BUILD_RENDERSYSTEM_METAL=1 -D OGRE_STATIC=1 -D OGRE_BUILD_SAMPLES=1 -D OGRE_BUILD_PLATFORM_APPLE_IOS=1 -G Xcode ..
```

cmake -D CMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -D BOOST_ROOT=/Users/lvjiaming/WorkSpace/ogre/iOSDependencies/include/boost -D BOOST_INCLUDEDIR=/Users/lvjiaming/WorkSpace/ogre/iOSDependencies/include/boost -D BOOST_LIBRARYDIR=/Users/lvjiaming/WorkSpace/ogre/iOSDependencies/lib -D OGRE_DEPENDENCIES_DIR=/Users/lvjiaming/WorkSpace/ogre/iOSDependencies -D OGRE_BUILD_RENDERSYSTEM_GLES2=1 -D OGRE_BUILD_RENDERSYSTEM_METAL=1 -D OGRE_STATIC=1 -D OGRE_BUILD_SAMPLES=1 -D OGRE_BUILD_PLATFORM_APPLE_IOS=1 -G Xcode ..

```
使用真机调试，模拟器不可用

```