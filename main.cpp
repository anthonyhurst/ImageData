#define cimg_use_jpeg
#include "CImg.h" 
#include <iostream>
#include <boost/unordered_map.hpp>


int main(int argc, char** argv) {
    for(int i = 0; i < argc; ++i) {
        std::cout << "arg" << i << ": " << argv[i] << std::endl;
    }
    cimg_library::CImg<unsigned char> image("text.jpg");
    std::cout << "Width: " << image.width() << " Height: " << image.height() << std::endl;
    double red=0.0, blue=0.0, green=0.0;
    boost::unordered_map<uint64_t, int> colorFrequency;
    int lightBlue = 0;
    for(int row = 0; row < image.height(); ++row) {
        for(int column = 0; column < image.width(); ++column) {
            red=image(column,row,0,0);
            green=image(column,row,0,1);
            blue=image(column,row,0,2);
            std::cout << "Pixel (" << column << "," << row << ") RGB(" << red << "," << green << "," << blue << ")" << std::endl;
            uint64_t n = 0; 
            n += green;
            n += blue * 1000;
            n += red * 1000000;
            if ( red < 100 && green > 100 && green < 200 && blue > 200) {
                std::cout << "lightBlue" << std::endl;
                lightBlue++;
            }
            boost::unordered_map<uint64_t,int>::iterator it = colorFrequency.find(n);
            if (it == colorFrequency.end()) {
                colorFrequency[n] = 0;
            }
            colorFrequency[n]++;
            std::cout << "\tFreq: " << colorFrequency[n] << std::endl;
        }
    }
    std::list<int> freqs;
    for(boost::unordered_map<uint64_t,int>::iterator it = colorFrequency.begin(); it != colorFrequency.end(); ++it) {
        std::cout << "Color: " << it->first << " Frequency: " << it->second << " Percent: " << ((double)it->second)/(image.width()*image.height())*100.0 << std::endl;
        freqs.push_back(it->second);
    }
    freqs.sort();
    int i = 0;
    for (std::list<int>::iterator it = freqs.begin(); it != freqs.end(); ++it) {
        std::cout << *it << std::endl;
        if (i > 9)
            break; 
    }
    std::cout << "lightBlue: " << lightBlue << std::endl;
}
