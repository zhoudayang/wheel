### windows Thread 类实现

1. 封装了windows的线程操作，提供了start,join等方法。还封装了一些工具方法，包括getpid(),tid()等。
2. 线程库传入的参数是boost::function类型，方便调用。

> 依赖：boost, 可以调整为只依赖 c++11。

### 注意事项
若出现了链接错误，请执行下述操作：
1. 设置vs项目属性，调整预处理器中的预处理器定义，将WINDOWS修改为_CONSOLE。![](http://i.imgur.com/XS5twNr.png)
2. 转到链接器选项，将系统中的子系统选项调整为控制台(/SUBSYSTEM:CONSOLE)![](http://i.imgur.com/EiwxM4P.png)
