#include <future>
#include<iostream>
/*

    option 1: one after the other. Always complete one thing before starting the next task
    Concept 1-> Single thread Technique 

///////////////////////////////////////////////////////////////////

    option 2: I will complete all task in such a way that I practically start all of them
            at the same time "But keep juggling them based on some criteria"
    Concept 2-> Multi thread Technique ###########

//////////////////////////////////////////////////////////////////

    option 3: map number of task amongst number of avalaible "workers"
    Concept 3-> Parallel execution ##############

////////////////////////////////////////////////////////////////

    option 4: Start a task. Either delegate it to another worker OR do it yourself after some time

        If someone else is doing the task monitor it, wait for their work to be done,
        take following actions accordingly
    Concept 4-> Asynchronus execution ############


*/


/*
    2 tasks:
    calculate factorial of 5 
    calculate square of a number given by the user
*/

int square( std::future<int>& ft){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Hello from square! I have started my work\n";
    int number = ft.get();
    return number*number;
}

int Factorial(int number){
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if(number < 0){
        throw std::runtime_error("negative number error!");
    }
    else if(number ==0 || number ==1){
        return 1;
    }
    else{
        return number * Factorial(number -1);
    }
}
int main()
{
    //step 1 -> make a promise 
    std::promise<int> pr;

    //step 2 -> A future linked to a promise 
    std::future<int> ft = pr.get_future();

    //OS: launch square(if possible as a new thread)
    std::future<int> result_ft =  std::async(std::launch::async,&square,std::ref(ft));
    std::cout<<Factorial(5)<<"!"<<std::endl;

    int val = 0;
    std::cin>> val;
    pr.set_value(val); // here our promised is fullfilled so thats why it will give result
    // this value is given to function using set where get() is written to accept the value

    std::cout<<"Result of Factorial is: "<< result_ft.get();
}

/* 
    Client Server Architecture

Future Promise model

-Square calculation
-man needs to delegate the task of square calculations

---> new thread for square is regsitered with OS


*/

