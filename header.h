#ifndef __header_H__
#define __header_H__
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <sstream>
#include <unistd.h>

class Philosopher {
  public:
    Philosopher(int, int, int, int, int, int);
    std::array<std::mutex *, 2> forks;
    void decrement_time_to_die();
    void decrement_time_to_eat();
    void decrement_time_to_sleep();
    void decrement_must_still_eat();
    int time_to_die();
    int time_to_eat();
    int time_to_sleep();
    int must_still_eat();
    int fork_count();
    int set_fork_count(int);
    int set_index(int);
    int get_index();

  private:
    int _index_in_vector;
    int _time_to_die;
    int _time_to_eat;
    int _time_to_sleep;
    int _must_still_eat; //Optional arg
    int _fork_count;
};
#endif
