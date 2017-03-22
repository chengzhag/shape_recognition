# shape_recognition

> 形状识别，使用qt、opencv、matlab、vs
> 于电子科技大学2017年寒假

## 概述

参加通信学院P2P项目：
- 掌握C++面向对象的编程
- 学习了OpenCV的使用
- 熟悉了Visual Studio集成开发环境
- 了解了QT的编程方法
- 熟悉了matlab的使用

## 演示程序
- 打开\shape_recognition\build\shape_recognition.exe
- 在图像浏览窗口按esc可关闭窗口
- \shape_recognition\build\im中有示例图片供测试
- 所需dll动态库已经拷贝到exe所在文件夹

## 文件夹结构
- shape_recognition包含所有工程文件
- shape_recognition\build为vs的编译输出文件夹，也包含了程序运行必备文件
    - im文件夹包含了示例图片
    - classifier包含了神经网络xml文件
    - sample包含了所有样本，是由matlab随机生成的
    - vector包含了存储的特征向量，包括程序运行新增的

## 想编译工程？
- 你需要配置好vs2015 + opencv3.2.0开发环境
- 你需要配置好vs2015 + qt5.8开发环境
