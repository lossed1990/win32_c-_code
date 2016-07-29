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

**。TimeHelper.h【时间常见操作函数】**

*类*

- CTimeCounter 程序运行计时帮助类 

*函数*

- 获取昨日时间区间


**。LogHelper.h【日志记录帮助类】**


**。DumpHelper.h【dump生成帮助类】**


**。TTSHelper.h【文本语音转换帮助类】**

