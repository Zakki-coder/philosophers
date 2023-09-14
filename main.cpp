#include "header.h"
#define ARG_NUMBER 5 //Program name is one of these
#define OPTIONAL_ARGS_NUMBER 1

void printer(std::vector<int> vec)
{
  for (int i = 0; i < vec.size(); i++)
    std::cout << vec[i] << std::endl;
}

//Args:
//number_of_philosophers, time_to_die, time_to_eat, time_to_sleep
//optional arg: number_of_times_each_philospher_must_eat
std::vector<int> parse_arguments(int argc, char **argv) 
{
  if (argc != ARG_NUMBER && argc != (ARG_NUMBER + OPTIONAL_ARGS_NUMBER))
    throw std::invalid_argument("Usage: ./philosophers <n_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>, optional: <n_of_times_each_must_eat>");

  //Test that every argument is a number
  for (int i_arg = 1; i_arg < argc; i_arg++)
  {
    for (int i = 0; argv[i_arg][i]; i++)
    {
      if (std::isdigit(argv[i_arg][i]) == 0)
        throw std::invalid_argument("ERROR: All arguments must be numbers");
    }
  }

  std::vector<int> arguments;

  for (int i = 0; i < argc; i++)
    arguments.push_back(std::atoi(argv[i]));

  return arguments;
}

std::vector<Philosopher> initialize_philosophers(std::vector<int> arguments)
{
  int n_of_philosophers = arguments[1];
  int time_to_die = arguments[2];
  int time_to_eat = arguments[3];
  int time_to_sleep = arguments[4];
  int must_eat_number = arguments[5];
  int fork_count = 0;
  std::vector<Philosopher> philosophers;
  philosophers.reserve(n_of_philosophers);

  //printer(arguments);
  if (!must_eat_number)
    must_eat_number = -1;

  for(int i = 0; i < n_of_philosophers; i++)
  {
    philosophers.push_back(Philosopher(time_to_die, time_to_eat, time_to_sleep, must_eat_number, fork_count, i));
  }
  return philosophers;
}

void print_philosopher(Philosopher philosopher)
{
  std::cout << "Time to die: " << philosopher.time_to_die() << std::endl \
          << "Time_to_eat: " << philosopher.time_to_eat() << std::endl \
          << "Time_to_sleep: " << philosopher.time_to_sleep() << std::endl \
          << "Must_still_eat: " << philosopher.must_still_eat() << std::endl \
          << "Index: " << philosopher.get_index() << std::endl \
          << "Fork count: " << philosopher.fork_count() << std::endl << std::endl;
}

void print_philosophers(std::vector<Philosopher> philosophers)
{
  for (int i = 0; i < philosophers.size(); i++)
  {
    std::cout << "Philosopher " << i + 1 << std::endl;
    print_philosopher(philosophers[i]);
  }
  std::cout << std::endl;
}

void get_forks(Philosopher);

void start_eating(Philosopher philosopher)
{
  //TODO Protect
  std::stringstream msg;
  msg << philosopher.get_index() << " Started EATING" << std::endl;
  std::cout << msg.str();
  std::cout.flush();
  usleep(philosopher.time_to_eat());
  msg << philosopher.get_index() << "SLEEEPING" << std::endl;
  std::cout << msg.str();
  std::cout.flush();
  philosopher.forks[0]->unlock();
  philosopher.forks[1]->unlock();
  philosopher.set_fork_count(0);
  usleep(philosopher.time_to_sleep());
  get_forks(philosopher);
}

void get_forks(Philosopher philosopher)
{
  //TODO Protect
  std::stringstream msg;
  msg << philosopher.get_index() << " Get Forks!" << std::endl;
  std::cout << msg.str();
  std::cout.flush();
  philosopher.forks[0]->lock();
  philosopher.forks[1]->lock();
  philosopher.set_fork_count(2);
//  print_philosopher(philosopher);
  start_eating(philosopher);
}

void create_setup(std::vector<Philosopher> philosophers, int n_of_philosophers)
{
  //Rename to forks
  std::vector<std::mutex> mutexes(n_of_philosophers); //Mutexes not movable, this works but dynamic resizing would not. 
  //Create thread for every philosopher,
  //Try to access mutex[phil_idx], after return try mutex[phil_idx + 1]
  //Once you have two forks start eating
  //we are creating threads inside a loop, so should we have a function that takes a philosopher and one fork?
  //Should I store reference of mutex inside philosopher?
  for(int i = 0; i < mutexes.size(); i++)
  {
    philosophers[i].forks[0] = &mutexes[i];
    if (i < mutexes.size() - 1)
      philosophers[i].forks[1] = &mutexes[i + 1];
    else
      philosophers[i].forks[1] = &mutexes[0];
    //mutexes[i].lock();
    //std::cout << "Mutex nb. " << i << " locked.";
    //philosophers[i].forks[0]->unlock();
    //std::cout << "Mutex nb. " << i << " unlocked.";
  }
  int i;
  std::vector<std::thread> threads(n_of_philosophers);
    i = 0;
    for(i; i < philosophers.size(); i++)
    {
//      if (i % 2 == 0)
//      {
        std::thread(get_forks, philosophers[i]).detach();
//      }
    }
//    i = 1;
//    for(i; i < philosophers.size(); i += 2)
//    {
//      if (i % 2 != 0)
//      {
//        std::thread(get_forks, philosophers[i]).detach();
//      }
//    }
    while (1);
}

int main(int argc, char **argv)
{
  std::vector<Philosopher> arguments;

  try {
    arguments = initialize_philosophers(parse_arguments(argc, argv));
  } catch (std::invalid_argument &error) {
    std::cerr << error.what() << std::endl;
    return -1;
  }
  //print_philosophers(arguments);
  create_setup(arguments, atoi(argv[1]));
  return 0;
}
