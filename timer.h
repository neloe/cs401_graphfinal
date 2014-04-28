//
/// \file timer.h
/// \author Nathan Eloe
/// \brief a timer class
//

#include <chrono>

class timer
{
  private:
    std::chrono::high_resolution_clock::time_point _start, _end;
  
  public:
    timer() {_start = std::chrono::high_resolution_clock::now();}
    void start() {_start = std::chrono::high_resolution_clock::now();}
    void end() {_end = std::chrono::high_resolution_clock::now();}
    double read() const {return std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start).count() ; }
};