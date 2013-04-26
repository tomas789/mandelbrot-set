//
//  Mandelbrot.h
//  mandel
//
//  Created by Tomáš Krejčí on 4/26/13.
//  Copyright (c) 2013 Tomas Krejci. All rights reserved.
//

#ifndef __mandel__Mandelbrot__
#define __mandel__Mandelbrot__

#define cimg_use_png
#include "CImg.h"

#include <complex>
#include <string>
#include <sstream>

template <typename Policy>
class Mandelbrot {
public:
    using signed_point = std::pair<typename Policy::signed_type, typename Policy::signed_type>;
    using unsigned_point = std::pair<typename Policy::unsigned_type, typename Policy::unsigned_type>;
    using complex_point = std::complex<typename Policy::double_type>;
#ifdef TEST
public:
#else
private:
#endif
    typename Policy::unsigned_type in_mandel(complex_point z);
    std::complex<double> transform_coord(unsigned zoom_lvl, unsigned x, unsigned y);
public:
    void operator()(std::string dir);
    void draw(std::string dir, unsigned zoom_level, Mandelbrot<Policy>::unsigned_point upper_left, Mandelbrot<Policy>::unsigned_point bottom_right);
};

template <typename Policy>
typename Policy::unsigned_type Mandelbrot<Policy>::in_mandel(Mandelbrot<Policy>::complex_point c) {
    if (Policy::debug_level >= 3)
        Policy::log(std::string("in_mandel"));
    
    decltype(c) z(0, 0);
    
    for (typename Policy::unsigned_type i = 0; i < Policy::max_iterations; ++i) {
        if (std::abs(z) >= 200) return i;
        else {
            z *= z;
            z += c;
        }
    }
    
    if (Policy::debug_level >= 2)
        Policy::log("In mandel");
    return Policy::max_iterations;
}

template <typename Policy>
std::complex<double> Mandelbrot<Policy>::transform_coord(unsigned zoom_lvl, unsigned x, unsigned y) {
    if (Policy::debug_level >= 3)
        Policy::log(std::string("transform_coord"));
    
    double o = std::pow(2.0, zoom_lvl - 1.0);
    return std::complex<double>((Policy::radius*(x-o))/(o), Policy::radius*(y-o)/(o));
}

template <typename Policy>
void Mandelbrot<Policy>::operator()(std::string dir) {
    if (Policy::debug_level >= 3)
        Policy::log(std::string("operator ()"));
    
    Mandelbrot<Policy>::unsigned_point upper_left(0, 0);
    Mandelbrot<Policy>::unsigned_point bottom_right(std::pow(2, Policy::init_zoom), std::pow(2, Policy::init_zoom));
    draw(dir, Policy::init_zoom, upper_left, bottom_right);
}

template <typename Policy>
void Mandelbrot<Policy>::draw(std::string dir, unsigned zoom_level, Mandelbrot<Policy>::unsigned_point upper_left, Mandelbrot<Policy>::unsigned_point bottom_right) {
    if (Policy::debug_level >= 3)
        Policy::log(std::string("draw"));
    
    typename Policy::image_type img(bottom_right.first - upper_left.first, bottom_right.second - upper_left.second, 1, 3, 255);
    
    // Draw
    for (typename Policy::unsigned_type y = upper_left.second; y < bottom_right.second; ++y)
    {
        for (typename Policy::unsigned_type x = upper_left.first; x < bottom_right.second; ++x)
        {
            typename Policy::unsigned_type res = in_mandel(transform_coord(zoom_level, x, y));
            typename Policy::unsigned_type color[] = {0, 0, 0};
            
            if (Policy::max_iterations != res)
                color[2] = 256 * res / Policy::max_iterations;
            
            img.draw_point(x, y, color);
        }
    }
    
    img.display("Hello, World!");
    
    std::stringstream filename;
    filename << dir << "/" << zoom_level << "_" << 0 << "_" << 0 << ".bmp";
    if (Policy::debug_level >= 2)
        Policy::log(std::string("saving image ") + filename.str());
    img.save(filename.str().c_str());
    
    if (zoom_level < Policy::max_zoom) {
        // Call recursive
    }
}

#endif /* defined(__mandel__Mandelbrot__) */
