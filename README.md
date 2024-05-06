# hw-memory3

- 代码解释和运行结果解释放在实验报告，这里不再赘述。

- 这里只简单说明如何复现实验报告中的结果。

1. 下载：
使用`scp`指令将代码传到服务器，或者从github克隆我的代码。
```
git clong https://github.com/1lancerZ/hw-memory3.git
```

2. 运行：
除了`exp1/task3/`中的代码，其他文件夹中都有一个`run.sh`文件，`./run.sh`运行即可。
如果提示权限不够，输入以下命令改变文件权限。
```
chmod 777 run.sh
```
运行`exp/task3/`中的代码则需要输入`make`编译后再运行程序`./test`。