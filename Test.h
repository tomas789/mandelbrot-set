//
//  Test.cpp
//  mandel
//
//  Created by Tomáš Krejčí on 4/26/13.
//  Copyright (c) 2013 Tomas Krejci. All rights reserved.
//

#include "main.h"

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_1 )
{
    Mandelbrot<Mandelbrot_Policy> m;
    std::complex<double> coord = m.transform_coord(9, 256, 256);
    BOOST_CHECK_EQUAL(coord, std::complex<double>(0,0));
}

BOOST_AUTO_TEST_CASE( test_2 )
{
    Mandelbrot<Mandelbrot_Policy> m;
    std::complex<double> coord = m.transform_coord(9, 0, 0);
    BOOST_CHECK_EQUAL(coord, std::complex<double>(-Mandelbrot_Policy::radius,-Mandelbrot_Policy::radius));
}

BOOST_AUTO_TEST_CASE( test_3 )
{
    Mandelbrot<Mandelbrot_Policy> m;
    BOOST_CHECK(m.in_mandel(std::complex<double>(0.0,0.0)) == Mandelbrot_Policy::max_iterations);
}

BOOST_AUTO_TEST_CASE( test_4 )
{
    Mandelbrot<Mandelbrot_Policy> m;
    BOOST_CHECK(m.in_mandel(std::complex<double>(5.325,1000.0)) != Mandelbrot_Policy::max_iterations);
}

BOOST_AUTO_TEST_CASE( test_5 )
{
    typename Mandelbrot_Policy::image_type img(256, 256, 1, 3, 128);
    
    BOOST_CHECK(img.save_png("/tmp/test_case.png"));
}
