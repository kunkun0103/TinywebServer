#pragma once
#include <functional>

// 定义函数指针
// typedef int(*handleFunc)(void* arg);
// using handleFunc = int(*)(void*);

// 定义文件描述符的读写事件
//强类型枚举
enum class FDEvent
{
    TimeOut = 0x01,
    ReadEvent = 0x02,
    WriteEvent = 0x04
};

class Channel
{
public:
    using handleFunc = std::function<int(void*)>;//函数包装器相当于只是另外起一个名字需要自己调用
    Channel(int fd, FDEvent events, handleFunc readFunc, handleFunc writeFunc, handleFunc destroyFunc, void* arg);
    // 回调函数
    handleFunc readCallback;
    handleFunc writeCallback;
    handleFunc destroyCallback;
    // 修改fd的写事件(检测 or 不检测)
    void writeEventEnable(bool flag);
    // 判断是否需要检测文件描述符的写事件
    bool isWriteEventEnable();
    // 取出私有成员的值
    inline int getEvent()//内联函数,直接会在调用原地展开而不会去调用,好处:节省时间优化.坏处:占内存
    {
        return m_events;
    }
    inline int getSocket()
    {
        return m_fd;
    }
    inline const void* getArg()
    {
        return m_arg;
    }
private:
    // 文件描述符
    int m_fd;
    // 事件
    int m_events;
    // 回调函数的参数
    void* m_arg;
};

