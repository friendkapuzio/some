#include <iostream>
#include <thread>
#include <cmath>
#include <iomanip>
#include <vector>
#include <atomic>
#include <chrono>
#include <mutex>


double pi(0);

std::mutex mutex;

std::pair<int,int> blocks[1000];

std::atomic<int> curBlock(0);

void PI()
{
    double sum=0;
    int block;
    while(curBlock>0)
    {
        block=--curBlock;
        for(long j=blocks[block].first; j<blocks[block].second; ++j)
        {
            sum+=(1.0/pow(16.0, j))*(8.0/(8*j+2)+4.0/(8*j+3)+4.0/(8*j+4)-1.0/(8*j+7))/2;
        }
    }
    std::unique_lock<std::mutex> lock(mutex);
    pi = pi + sum;
    lock.unlock();
}




int main()
{
    std::vector<std::thread> threads;
    int N;
    std::cin>>N;
    for (int i=0; i<1000; ++i)
    {
        blocks[i]=std::make_pair(140000*i, 140000*(i+1));
        ++curBlock;
    }
    auto start=std::chrono::system_clock::now();
    for (int i=0; i<N; ++i)
        threads.push_back(std::thread(PI));
    for(auto& it:threads) it.join();
    auto end=std::chrono::system_clock::now();
    auto dif=end-start;
    std::cout<<std::setprecision(16)<<pi<<std::endl<<std::chrono::duration_cast<std::chrono::milliseconds>(dif).count()<<std::endl;
    return 0;
}
