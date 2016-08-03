##win32_cplusplus_code##

windows下常用c++代码整理，用以之后快速搭建项目

整理思路：<br>
1、将常用函数归类于不同的帮助类中<br>
例如：<br>
- SystemHelper.h 主要包含一些系统常用函数，例如判断程序是否已运行、程序互斥等；<br>
- StringHelper.h 主要包含一些常用的字符函数，当然boost里面挺全的，如何整理大家也可以提提建议<br>
- ...<br>

2、提供函数使用文档<br>
目前使用doxygen通过注释生成帮助文档，希望整理出来的函数，使用中方便查看。<br>

3、提供使用demo<br>
项目里面建了一个空的win32项目，用以调用整理的函数，提供使用的示例。

##主要帮助文件如下：##

**。SystemHelper.h【系统常见操作函数】**

*函数* 

- 检查当前程序互斥量
- 检查进程是否存在
- 打开进程
- 销毁进程
- 开机自运行本程序
- 取消开机自运行本程序
- 重新运行一个本程序实例
- 打开某个文件夹

**。FileHelper.h【文件常见操作函数】**

*函数* 

- 获取文件版本描述
- 获取当前应用程序版本描述
- 获取当前应用程序路径
- 获取当前应用程序上层目录

**。StringHelper.h【字符常见操作函数】**

*函数* 

- 根据单个分隔符，分隔字符串
- 判断字符串是否全为数字
- 判断字符串是否为合法的e_mail地址
- 判断字符串是否为合法的固定电话地址
- 判断字符串是否为合法的手机号码
- 判断字符串是否为长时间字符格式
- 判断字符串是否为合法的IP地址
- 使用MD5算法转换字符串
- 去除字符串左边的特殊字符
- 去除字符串右边的特殊字符
- 去除字符串两侧的特殊字符
- Utf转成Unicode
- Unicode转成Ascii
- Utf转成Ascii
- Ascii转成Unicode
- Unicode转成Utf
- Ascii转成Utf

**。TimeHelper.h【时间常见操作函数】**

*类*

- CTimeCounter 程序运行计时帮助类 

*函数*

- 获取当日时间区间
- 获取昨日时间区间
- 获取前几日时间区间
- 获取本周时间区间
- 获取上周时间区间
- 获取本月时间区间
- 获取上月时间区间
- 获取本季度时间区间
- 获取上季度时间区间
- 获取本年时间区间
- 获取上年时间区间


**。LogHelper.h【日志记录帮助类】**

*说明*

1、本类主要封装谷歌glog日志库的初始化及设置相关操作，简化使用，使用时需包含glog文件夹头文件，运行时需包含libglog.dll

**。DumpHelper.h【dump生成帮助类】**

*说明*

dump文件创建帮助类,用于程度异常时创建dump文件


**。TTSHelper.h【文本语音转换帮助类】**

*说明*

1、单例类，便于全局使用；

2、异步播报，以防阻塞；

3、目前只封装了播放、停止两个接口，设置速度（SetRate）、设置音量（SetVolume）暂时省略

**。MonitorHelper.h【显示器操作帮助类】**

*说明*

1、单例类，便于全局使用；

2、构造时枚举所有显示器，方便操作；