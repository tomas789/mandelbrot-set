//
//  main.h
//  mandel
//
//  Created by Tomáš Krejčí on 4/26/13.
//  Copyright (c) 2013 Tomas Krejci. All rights reserved.
//

#ifndef mandel_main_h
#define mandel_main_h

#define cimg_use_png
#include "CImg.h"

//#define TEST

#include <iostream>
#include "Mandelbrot.h"


using namespace cimg_library;

struct Mandelbrot_Policy {
    using signed_type = int;
    using unsigned_type = unsigned int;
    using double_type = double;
    
    using image_type = CImg<unsigned_type>;
    using image_reference = image_type &;
    
    constexpr static const short debug_level = 1;
    static void log(std::string str) {
        std::cerr << "LOG: " << str << std::endl;
    }
    
    /* Must be power of two */
    constexpr static const double_type radius = 4.0;
    
    constexpr static const unsigned_type init_zoom = 9;
    constexpr static const unsigned_type max_zoom = 9;
    
    constexpr static const unsigned_type max_iterations = 2;
};

#endif
