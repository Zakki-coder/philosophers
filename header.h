#ifndef __header_H__
#define __header_H__
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Philosopher {
  public:
    Philosopher(int, int, int, int);
    void decrement_time_to_die();
    void decrement_time_to_eat();
    void decrement_time_to_sleep();
    void decrement_must_still_eat();
    int time_to_die();
    int time_to_eat();
    int time_to_sleep();
    int must_still_eat();

  private:
    int _time_to_die;
    int _time_to_eat;
    int _time_to_sleep;
    int _must_still_eat; //Optional arg
};
#endif
