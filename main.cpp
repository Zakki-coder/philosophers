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
  std::vector<Philosopher> philosophers;

  printer(arguments);
  if (philosophers.capacity() < n_of_philosophers)
    philosophers.reserve(n_of_philosophers);

  if (!must_eat_number)
    must_eat_number = -1;

  for(int i = 0; i < n_of_philosophers; i++)
  {
    philosophers.push_back(Philosopher(time_to_die, time_to_eat, time_to_sleep, must_eat_number));
  }

  return philosophers;
}

void print_philosopher(Philosopher philosopher)
{
  std::cout << "Time to die: " << philosopher.time_to_die() << std::endl \
          << "Time_to_eat: " << philosopher.time_to_eat() << std::endl \
          << "Time_to_sleep: " << philosopher.time_to_sleep() << std::endl \
          << "Must_still_eat: " << philosopher.must_still_eat() << std::endl;
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

int main(int argc, char **argv)
{
  std::vector<Philosopher> arguments;

  try {
    arguments = initialize_philosophers(parse_arguments(argc, argv));
  } catch (std::invalid_argument &error) {
    std::cerr << error.what() << std::endl;
    return -1;
  }
  print_philosophers(arguments);
  return 0;
}
