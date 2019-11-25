#include "Render/UIProvider.hpp"
#include "Render/StockRender.hpp"
#include "Simulator/StockSimulator.hpp"
#include <iostream>
#include <boost/array.hpp>

struct X{
    void operator()(){
        std::cout << "bla bla" << std::endl;
    }
};

int main(){


    Render::UIProvider cmdRender;

    cmdRender.setColor(Render::Color::BLUE);
    cmdRender.print("This should be blue\n");


    cmdRender.setColor(Render::Color::RED);
    cmdRender.print("This should be red\n");


    cmdRender.setColor(Render::Color::GREEN);
    cmdRender.print("This should be Green\n");
    
   
    cmdRender.outPutWithColor(Render::Color::GREEN, "HelloWorld\n");
    cmdRender.resetToDefaultColor();
    cmdRender.print("This should have default color\n");





    StockLoader stockLoader;
    std::vector<Stock> stocks = stockLoader.loadStocks("./stockDb");

    //for(auto stock: stocks){
    //    std::cout << stock << std::endl;
    //}

    
    Simulator::StockSimulator stockSimulator(stocks);  
    Analyser::StockAnalyser stockAnalyser/*(stockSimulator)*/;

    stockSimulator.attach(stockAnalyser);
    
    
    Render::StockRender stockRender;
    stockAnalyser.attach(boost::bind(&Render::StockRender::render, &stockRender, _1));

    stockSimulator.start();
    
    //getchar();
}