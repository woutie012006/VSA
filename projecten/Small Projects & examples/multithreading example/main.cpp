#include <string>
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

// The function we want to execute on the new thread.
void task1()
{
    cout << "task1 says: " <<std::endl;
}
void task2()
{
    cout << "task2 says: " <<std::endl;
}

int main()
{
    // Constructs the new thread and runs it. Does not block execution.
    thread t1(task1);

    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.

    std::cout << "main says" << std::endl;

    sleep( 1 );
    thread t2(task2);

    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    t1.join();
    t2.join();
    return 0;
}
