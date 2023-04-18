
#include <iostream>
#include <iterator>
#include <list>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;
ofstream outputFile("primes.txt");
std::mutex mtx;

class Task
{
private:

    int index;
    int final;
    int inicio;
    

public:
   

    Task( int index, int final, int inicio)
    {
        
        this->index = index;
        this->final = final;
        this->inicio = inicio;
    }

    void run()
    {
        
        /* Teste para verificar o paralelismo
        if(index == 953){
            _sleep(50);
        }
        */

        if(isPrime(index)){
            //cout<<"O numero "<<index<<" eh primo" <<endl;
           
            if(outputFile.is_open())
            {
                outputFile << index << " ";
                if(index == final ){//fecho o arquivo quando estiver no ultimo número
                    outputFile.close();
                }
            }
            else
            {
                cout << "Erro ao gravar o arquivo final" << endl;
            }
        }

        
        
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

    for(int i = a; i <b; i++)
    {
        Task* task = new Task(i,b,a);
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
