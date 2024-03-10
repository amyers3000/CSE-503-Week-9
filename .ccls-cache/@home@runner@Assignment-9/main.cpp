#include <iostream>
#include <fstream>
#include <unistd.h>
#include<sys/wait.h>

#define ARRAY_SIZE 1500
#define RANGE 121

void initalArray(int *arr, int size, int range)
{
    for(int i = 0; i < size; i++)
    {
      arr[i] = rand() % range;
    }
  return;
}

void queryOccurences(int *arr, int size, int query)
{
  int count = 0;
  for(int i = 0; i < size; i++)
  {
    if(arr[i] == query)
    {
      count++;
    }
  }
  std::cout << "query: " << query << " count: " << count <<" pid:" << getpid() << std::endl;
}

int main() {
  
  
  std::ifstream myfile("input.txt");
  myfile.is_open();

  int query;
  int pid;
  int *arr = new int[ARRAY_SIZE];

  initalArray(arr, ARRAY_SIZE, RANGE);

  while(myfile >> query)
  {
    // create child process; shares same memory space as parent; runs all code after fork
    pid = fork();

    if(pid < 0){
      //less than 0 indicates fork failed
      std::cout << "Fork failed" << std::endl;
      exit(-1);
    }
    else if (pid == 0)
    {
      //child process
      queryOccurences(arr, ARRAY_SIZE, query); 
    }
    else
    {
      // parent process
      wait(NULL);
      exit(0);
    }
    
  }

  myfile.close();
  delete [] arr;

  return 0;
}