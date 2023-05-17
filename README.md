# FlipGreenChannelTool 

能把图片的绿色通道反转的工具，用于OpenGL和DirectX法线贴图的相互转换。支持JPG/PNG/TIFF/EXR图片格式。

A tool which can invert the green channel of pictures in order to convert normal maps between format OpenGL and DirectX. Support JPG/PNG/TIFF/EXR.

## 如何使用？ How to use it?

把图片拖到FlipGreenChannelToolPack.exe上即可转换，另存为新的文件。

Drag the image to 'FlipGreenChannelToolPack.exe', then it will invert its green channel and save as another file.

## 为何使用？Why use it?

OpenGL和DirectX法线贴图只有绿色通道是相反的，可以互相转换。在Unreal Engine中是可以在导入设置中设置“反转绿色通道”来完成转换的，很方便，不需要使用该程序，但是其他情况下可能需要这样一个软件了。

The only difference between OpenGL and DirectX Normal maps is the opposite green channel, and they can be converted to each other. In Unreal Engine, it is possible to set the "Invert Green Channel" in the import settings to complete the conversion, which is convenient and does not require the this program. However, in other cases, such a program may be useful.

## 下载 Download

[下载 Download](https://github.com/Mario-Hero/FlipGreenChannelTool/releases/download/Main/FlipGreenChannelToolPack.exe)

## 依赖 Dependency

Windows x64

OpenCV 4.7 (Maybe OpenCV 4+ is ok)

## 编译 Build

本程序需要OpenCV开启EXR支持，所以需要手动编译OpenCV并添加OpenEXR支持。

This program requires EXR format support, so you need to manually compile OpenCV and add OpenEXR support.

## License

This project is licensed under the Apache License, Version 2.0
