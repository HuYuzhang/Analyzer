# Analyzer
用于视频分析的一些自己手写的类
---
## YUVReader
* 用于从420视频序列中读取指定编号的帧，编号从0开始
### 修改
* 10.27将原先读取数据用到的ifstream.get函数改成ifstream.read函数。实际测试中发现前者会出现数据仅仅读取一部分的问题。
查了函数原型之后看到实际上还有第三个默认参数，delim='\n'，所以可能的情况是某个像素值恰等于'\n'，所以终止了数据读取。
而read函数纯粹就是指定大小之后进行二进制数据的读取。
## Spliter
* 之前已经把每个CU的预测模式全部dump下来了，这里就是根据预测模式，从重建视频和原始视频中分别切割出input和label。
### 修改
* 10.27重载了split函数，增加了不指定帧数的版本，因为现在已经将帧编号的信息一并dump到文件中去了
## EdgeDrawer
* 之前打算dump出CU的划分策略，然后自己在图像上用这个类划线，检查和Elecard HEVC Analyzer的结果是否相同。但是现在已经限制CU大小的情况下好像已经没用了。
