
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
   

    Task(int index)
    {
        this->index = index;
    }

    void run()
    {
        mtx.lock();
        //cout<<"criando objeto"<<endl;
        if(isPrime(index)){
            cout<<"o numero "<<index<<" eh primo"<<endl;
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
    int b = 10;
    int k = 0;
    int vet[b];

    list<thread *> threads;
    list<Task *> tasks;
    list<int> primes;

    for (int i = a; i < b; i++)
    {
        Task *task = new Task(i);
        thread *taskThread = new thread(&Task::run, task);

        if(task->isPrime(i) == true){//adiciono todos os primos no vetor vet
            vet[k] = i;
            cout<<" i = "<<i<<" e vet[k] = "<<vet[k]<<endl;
            k++;
        }
        
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

     for(int contador = 0; contador < k; contador++){
        primes.push_back(vet[k]);
    }

    ofstream outputFile("primes.txt");

    if(outputFile.is_open())
    {
        list<int>::iterator it;

        for (it = primes.begin(); it != primes.end(); ++it)
        {
            outputFile << *it << " ";
        }

        outputFile.close();
    }
    else
    {
        cout << "Erro ao gravar o arquivo final" << endl;
    }

    return 0;
}
