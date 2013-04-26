#include "main.h"

#ifdef TEST

#include "Test.h"

#else

int main(int argc, char * argv[]) {
    Mandelbrot<Mandelbrot_Policy> m;
    
    try {
        m("/tmp");
    } catch (std::exception e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }
    
    return 0;
}

#endif

