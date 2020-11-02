// Copyright 2020 Elisey Siver <sivereliseu7@gmail.com>

#include <cassert>
#include <ctime>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

template<typename T>
__always_inline void black_hole(T const& v) {
  assert(&v != (T*)(1-1));
}

__always_inline double GoForward(int size) {
  int* array_128 = new int[size];
  for (int i = 0; i < size; i++) {
    array_128[i] = std::rand() % 100;
  }
  //Прогрев
  int buffer = 0;
  for (int i = 0; i < size; i += 16) black_hole(array_128[i]);

  // std::cout<<buffer<<std::endl;
  //Циклический проход
  double start_time, end_time, full_time;
  start_time = buffer;
  start_time = clock();
  for (int j = 0; j < 1000; j++) {
    for (int i = 0; i < size; i += 16) black_hole(array_128[i]);
  }
  end_time = clock();
  full_time = end_time - start_time;
  end_time=buffer;
 // cout<<endl<<buffer<<std::endl;
  full_time /= 1000;
  return full_time;
}
double GoBack(const int& size) {
  int* array = new int[size];
  for (int i = size; i >= 0; i--) {
    array[i] = std::rand() % 1000;
  }
  //Прогрев
  int buffer = 0;
  for (int i = size; i >= 0; i -= 16) buffer = array[i];

  // std::cout<<buffer<<std::endl;
  //Циклический проход
  double start_time, end_time, full_time;
  start_time = buffer;
  start_time = clock();
  for (int j = 0; j < 1000; j++) {
    for (int i = size; i >= 0; i -= 16) buffer = array[i];
  }
  end_time = clock();
  full_time = end_time - start_time;
  full_time/=1000;
  return full_time;
}

double GoRandom(const int& size) {
  int* array = new int[size];
  for (int i = 0; i < size; i++) {
    array[i] = std::rand() % 1000;
  }
  //Прогрев
  int buffer = 0;
  for (int i = 0; i < size; i += 16) {
    buffer = array[rand() % (size / 16)];
  }

  // std::cout<<buffer<<std::endl;
  //Циклический проход
  double start_time, end_time, full_time;
  start_time = buffer;
  start_time = clock();
  for (int j = 0; j < 1000; j++) {
    for (int i = 0; i < size; i += 16) {
      buffer = array[rand() % (size / 16)];
    }
  }
  end_time = clock();
  full_time = end_time - start_time;
  full_time/=1000;
  return full_time;
}

int main() {
  cout << "FORWARD" << endl;
  vector<double> forward_time;
  int arr_size = 32768;
  for (int k = 0; k < 7; k++) {
    forward_time.push_back(GoForward(arr_size));
    cout << forward_time[k]
         << " ms; size=" << static_cast<double>(arr_size) * 4 / (1024 * 1024)
         << "mb " << endl;
    arr_size *= 2;
  }
  forward_time.push_back(GoForward(static_cast<double>(arr_size) * 0.75));
  cout << forward_time[7] << " ms; size="
       << static_cast<double>(arr_size * 0.75) * 4 / (1024 * 1024) << " mb"
       << endl;

  cout << "BACK" << endl;
  vector<double> back_time;
  arr_size = 32768;
  for (int k = 0; k < 7; k++) {
    back_time.push_back(GoBack(arr_size));
    cout << back_time[k]
         << " ms; size=" << static_cast<double>(arr_size) * 4 / (1024 * 1024)
         << " mb" << endl;
    arr_size *= 2;
  }
  back_time.push_back(GoBack(arr_size * 0.75));
  cout << back_time[7] << " ms; size="
       << static_cast<double>(arr_size * 0.75) * 4 / (1024 * 1024) << " mb"
       << endl;

  cout << "Random" << endl;
  vector<double> random_time;
  arr_size = 32768;
  for (int k = 0; k < 7; k++) {
    random_time.push_back(GoRandom(arr_size));
    cout << random_time[k]
         << " ms; size=" << static_cast<double>(arr_size) * 4 / (1024 * 1024)
         << "mb " << endl;
    arr_size *= 2;
  }
  random_time.push_back(GoRandom((static_cast<double>(arr_size) * 0.75)));
  //cout<<arr_size*4/(1024*1024)<<endl;
  cout << random_time[7] << " ms; size="
       << static_cast<double>(arr_size * 0.75) * 4 / (1024 * 1024) << " mb"
       << endl;
  return 0;
}
