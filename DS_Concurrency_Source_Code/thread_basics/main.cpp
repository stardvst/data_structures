#include <thread>
#include <Windows.h>

void thread_function()
{
    Sleep(2000);
}

void native_handle_example(std::thread &child)
{
    HANDLE hThread = child.native_handle();
    WaitForSingleObject(hThread, INFINITE);
}

void main()
{
    std::thread child(thread_function);

    bool j1 = child.joinable();

    child.detach();

    bool j2 = child.joinable();

}