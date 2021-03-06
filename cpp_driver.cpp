// Your First C++ Program

#include <iostream>
#include <chrono>
#include <ctime>
#include "bno055.h"
//#include <rosbag/bag.h>
//#include <std_msgs/Int32.h>
//#include <std_msgs/String.h>

//It is possible that I wouldn't need these if these fns were first declared in the header file
extern "C" int init_and_calib_bno055(void);
extern "C" int close_bno055(void);
extern "C" struct marae_data_t get_bno055_data(void);

int main(void)
{

  printf("Starting...\n");
  int i, func_val;
  struct marae_data_t imu_data = {};
  auto start = std::chrono::system_clock::now();

  func_val = init_and_calib_bno055();
  printf("Init and Calib returned %d\n", func_val);
  
  for (i=0; i< 2000; i++) {
      //TODO may want to verify at some point the quality of this data - as in - is the config properly tuned for this freq?
      imu_data = get_bno055_data();
      auto end = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_time = end - start;
      printf("%d %f\n", i, elapsed_time.count());
      //printf("BNO055 func call returned %d at %f\n", func_val, seconds);
  }

  func_val = close_bno055();
  printf("BNO055 close func returned %d\n", func_val);

  return 0;
}
