# ICSExport

![GitHub](https://img.shields.io/github/license/lcp29/ICSExport)![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/lcp29/icsexport)![GitHub closed pull requests](https://img.shields.io/github/issues-pr-closed/lcp29/icsexport)

**md怎么这学期的课表还有单双周，就真得直接读网页吗QAQ**

**需要对表格进行人工修改，规则如下：**

**转换之前把单双周改成实际的周数，如 单周-->1,3,5,7周**

**这学期的课表又有了奇怪的现象，相同时间不同周数的不同课不再用逗号分离了，人工分一下**

**表格里有没被中括号括起来的X-X节，也要去掉**

ICS课表制作工具，从自写脚本或Excel表格(*.xlsx)文件生成.ics文件，可直接导入iOS日历。

**只支持哈尔滨工业大学（深圳）教务系统导出的Excel表格。**

**运行效果：**

GUI:

![](/doc/img/gui.png)

脚本：

![](/doc/img/script.png)

生成的ics文件：

![](/doc/img/ics.png)

日历效果：

![](/doc/img/calendar.png)

**从源码运行：**

目前只在windows下进行过测试

在Linux、Mac OS等操作系统下运行时，请修改makefile里的输出可执行文件名与对应操作系统相匹配，再在根目录下

```
make build
```

将生成的可执行文件与rx.py放到同一目录下，并修改rx.py中的可执行文件名称。

从源码运行可视化xlsx导入工具时，需要安装

```
pip install xlrd
```

打包成可执行文件需要安装

```
pip install pyinstaller
```

**注意：** icsexport.exe默认采用UTF-8输出（v0.0.1除外），在Windows Powershell的默认设置下可能会出现乱码问题（不会影响使用）。请更改默认代码页或在运行前执行`chcp 65001`来解决问题。
