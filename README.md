# 随机密码

**慕课 西安交通大学 计算机程序设计（C++）第一期 编程练习**

*https://www.icourse163.org/course/XJTU-46006?tid=47003*

密码程序，生成随机密码，功能如下：

1. 密码的形式可以选择：  
    数字密码；数字小写字母混合密码；数字大写字母混合码；
    数字大小写字母混合秘密；数字、大小写字母、特殊字符（ ! @ # $ % &）混合码。
2. 可以设置密码的长度（即位数），如4位、5位、6位等。
3. 设定密码形式、密码长度后，可以生成多组密码，直到用户确认退出。
    但不退出程序，还可以继续选择密码形式和长度，再生成密码。
4. 保存密码文件到硬盘  
**版本：2.0**  
    合并了随机字符串生成函数和合格判断函数到randomTemp()中，代价是randomTemp()稍显复杂。  
**版本：3.0**  
    完成了main函数，编译后的文件（假设文件名：password.exe）可以在终端使用命行参数调用。  
    如：  
    > password  
    > password -5 -6 -7 -0
    > password /4 /5 -3 /1  
    > password -5 -6 -7 -0  
    > password -5 -6  
    > 甚至 password asdfg 等等。
