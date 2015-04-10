#include <iostream>
#include <thread>
#include <cmath>
#include <iomanip>
#include <vector>
#include <atomic>
#include <chrono>
#include <mutex>


std::atomic<double> pi(0);

std::mutex mutex;

void PI(int i, int N)
{
    for(int j=14*i/N; j<14*(i+1)/N; ++j)
    {
        std::unique_lock<std::mutex> lock(mutex, std::defer_lock);
        lock.lock();
        pi = pi + (1.0/pow(16.0, j))*((double)8/(8*j+2)+(double)4/(8*j+3)+(double)4/(8*j+4)-(double)1/(8*j+7))/2;
        lock.unlock();
    }

}




int main()
{
    std::vector<std::thread> threads;
    int N;
    std::cin>>N;
    auto start=std::chrono::system_clock::now();
    for (int i=0; i<N; ++i)
        threads.push_back(std::thread(PI, i, N));
    for(auto& it:threads) it.join();
    auto end=std::chrono::system_clock::now();
    auto dif=end-start;
    std::cout<<std::setprecision(16)<<pi<<std::endl<<std::chrono::duration_cast<std::chrono::microseconds>(dif).count()<<std::endl;
    return 0;
}