## simple atoi and itoa implement

* itoa的实现中使用对称的数组搞定了负数转换的边界条件。
* atoi的实现中需要处理传入的数组为空，有空前缀，以及负数溢出的情况。因为使用long存储中间结果，所以不用处理溢出。