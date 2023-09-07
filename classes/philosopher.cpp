#include "../header.h"

Philosopher::Philosopher(int time_to_die, int time_to_eat, int time_to_sleep, int must_still_eat = -1)
{
  this->_time_to_die = time_to_die;
  this->_time_to_eat = time_to_eat;
  this->_time_to_sleep = time_to_sleep;
  this->_must_still_eat = must_still_eat;
}

void Philosopher::decrement_time_to_die()
{
  --this->_time_to_die;
}

void Philosopher::decrement_time_to_eat()
{
  --this->_time_to_eat;
}

void Philosopher::decrement_time_to_sleep()
{
  --this->_time_to_sleep;
}

void Philosopher::decrement_must_still_eat()
{
  --this->_must_still_eat;
}

int Philosopher::time_to_die()
{
  return this->_time_to_die;
}

int Philosopher::time_to_eat()
{
  return this->_time_to_eat;
}

int Philosopher::time_to_sleep()
{
  return this->_time_to_sleep;
}

int Philosopher::must_still_eat()
{
  return this->_must_still_eat;
}
