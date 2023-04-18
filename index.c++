
#include <iostream>
#include <iterator>
#include <list>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

std::mutex mtx;

class Task
{
private:

    int index;
    

public:
   

    Task( int index)
    {
        
        this->index = index;
       
    }

    void run()
    {
        mtx.lock();

        if(index == 5){
            _sleep(500);
        }
        
        if(isPrime(index)){
            cout<<"O numero "<<index<<" eh primo" <<endl;
        }
        
        mtx.unlock();
        
    }


    bool isPrime(int index){
        
        bool prime = true;

        for (int j = 2; j <= (index / 2); ++j)
        {
            if ((index % j) == 0)
            {
                prime = false;
                break;
            }
        }
        return prime;
        
    }
    
};

int main()
{
    int a = 1;
    int b = 10000;

    list<thread *> threads;
    list<Task *> tasks;

    for(int i = b; i >= a; i--)
    {
        Task* task = new Task(i);
        thread *taskThread = new thread(&Task::run, task);

        tasks.push_back(task);
        threads.push_back(taskThread);
    }
    
    for (list<thread *>::iterator it = threads.begin(); it != threads.end(); ++it)
    {
        (*it)->join();
        delete (*it);
    }

    for (list<Task *>::iterator it = tasks.begin(); it != tasks.end(); ++it)
    {
        delete (*it);
    }

    return 0;
}
