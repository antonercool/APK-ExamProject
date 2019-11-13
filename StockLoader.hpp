#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem; 

class StockLoader
{
private:
  std::vector<Stock> stockList_;

public:
  StockLoader(){

  };
  ~StockLoader(){

  };

  void loadStocks(std::string directory)
  {
    stockList_.clear();

    

    //std::ifstream pFile( fileName.c_str() );
//
    //std::copy(std::istream_iterator<Product>(pFile),
    //     std::istream_iterator<Product>(),
    //     std::back_inserter(pl));

    //boost::filesystem::path p = boost::filesystem::current_path();
    //boost::filesystem::directory_iterator it{p};
    //while (it != boost::filesystem::directory_iterator{})
    //std::cout << *it++ << '\n';

    boost::filesystem::path path = "./stockDb";
    for (const auto & entry : boost::filesystem::directory_iterator(path))
        std::cout << entry.path() << std::endl;
//
    //for (const auto & entry : fs::directory_iterator(path))
    //    std::cout << entry.path() << std::endl;
         
//path p("D:/AnyFolder");
    //for (auto i = boost::filesystem::directory_iterator(path); i != boost::filesystem::directory_iterator(); i++)
    //{
    //    if (!is_directory(i->path())) //we eliminate directories
    //    {
    //        std::cout << i->path().filename().string() << std::endl;
    //    }
    //}


    
    //for (const auto & entry : boost::filesystem::directory_iterator(path)){
    //    std::cout << entry.path() << std::endl;
    //}
        


  //while( !pFile.eof() )
  //{
  //  Product p;
  //  pFile >> p;
  //  if( pFile ) pl.push_back( p );
  //}

  //pFile.close();

    //std::future<int> futures[] = {std::async([]() { return 1; }),
    //                              std::async([]() { return 1; })};

    //std::future<std::vector<std::future<int>>> any_f = when_any(begin(futures), end(futures));

    /* future from a promise */
    //std::promise<int> p;
    //std::future<int>  f = p.get_future();
    //std::thread([](std::promise<int> p) { p.set_value_at_thread_exit(9); },
    //            std::move(p))
    //    .detach();
    //
    // std::cout << "Waiting..." << std::flush;
    //
    // f.wait();
    // std::cout << "Done!\nResult is: " << f.get() << '\n';
  }
};