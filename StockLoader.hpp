#include <string>
#include <iostream>
#include <vector>
#include <future>
#include <thread>


class StockLoader
{
private:
    std::vector<Stock> stockList_;

public:
    StockLoader(){

    };
    ~StockLoader(){
        
    };

    void loadStocks(std::string directory){

        //std::future<int> futures[2] = {std::async([]() { return 1; }),               
        //                            std::async([]() { return 1; })};


//future<vector<future<int>>> any_f = when_any(begin(futures),end(futures));




        /* future from a promise */
        //std::promise<int> p;
        //std::future<int> f = p.get_future();
        //std::thread( [](std::promise<int> p){ p.set_value_at_thread_exit(9); },std::move(p) ).detach();
//
        //std::cout << "Waiting..." << std::flush;
//
        //f.wait();
        //std::cout << "Done!\nResult is: " << f.get() << '\n';

    }
};