///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// State of one disk, either light or dark.
enum disk_color { DISK_LIGHT, DISK_DARK };

// Data structure for the state of one row of disks.
class disk_state {
private:
  std::vector<disk_color> _colors;

public:

  disk_state(size_t light_count)
  : _colors(light_count * 2, DISK_LIGHT) {

    assert(light_count > 0);

    for (size_t i = 0; i < _colors.size(); i += 2) {
      _colors[i] = DISK_DARK;
    }
  }

  // Equality operator for unit tests.
  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  bool is_alternating() const {

    bool alt = false;
    disk_color init_val = get(0);
    if(init_val == DISK_LIGHT)
    {
      return false;
    }

    int i = 1;
    while(is_index(i))
    {
      if(alt == true)
      {
        if(get(i) ==  DISK_DARK)
        {
          alt = false;
          i++;
        }
        else
        {
          return false;
        }
      }
      else if(alt == false)
      {
        if(get(i) ==  DISK_LIGHT)
        {
          alt = true;
          i++;
        }
        else
        {
          return false;
        }
      }
    }
    return true;
  }

  // Return true when this disk_state is fully sorted, with all light disks
  // on the left (low indices) and all dark disks on the right (high
  // indices).
  // TODO: Write code for this function, including rewriting the return
  // statement, and then delete these comments.
  bool is_sorted() const {


//  std::cout << total_count() << std::endl;
    //int counter = 1;
    for(unsigned int i = 0; i < light_count(); i++)
    {
      if(get(i) == DISK_DARK)
      {
        return false;
      }
    }
    return true;
  }

};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
  : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
  : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the left-to-right algorithm.
// TODO: Write code for this function, including rewriting the return
// statement, and then delete these comments.
sorted_disks sort_left_to_right(const disk_state& before) {
  /*
  Psedeucode
  for r in size - 2 do

  for c = r in size-2 do
  if get(i) == get(i+1)
  // do nothing
  else
  // swap(get(i),get(i+1))
  */


  // implementation
  int counter = 0;
  disk_state after = before;
  for(unsigned int r = 0; r < after.total_count(); r++)
  {
    for(unsigned int c = 0; c < after.total_count()-1; c++)
    {
      if(after.get(c) == DISK_DARK && after.get(c+1) == DISK_LIGHT)
      {
        after.swap(c);
        counter++;
      }
    }
  }
  return sorted_disks(after, counter);
}

// Algorithm that sorts disks using the lawnmower algorithm.
// TODO: Write code for this function, including rewriting the return
// statement, and then delete these comments.

sorted_disks sort_lawnmower(const disk_state& before) {

  /*
  Pseudocode
  while not sorted do
  for i = 0 to size-2
  if(get(i) == get(i+1))
  {
  do nothing
}
else
{
swap
}
for i= size-1 to 1 do
{
if(get(i) == get(i-1))
{
do nothing
}
else
{
swap
}
}



*/
int counter = 0;
disk_state after = before;
int size = after.total_count();
for( int c = 0; c < size; c++)
{
  for( int i = c; i < size-1;i++)
  {
    if(after.get(i) == DISK_DARK &&  after.get(i+1) == DISK_LIGHT)
    {
      after.swap(i);
      counter++;
    }

  }
  size--;
  for( int t = size-1; t > c; t--)
  {
    if(after.get(t) == DISK_LIGHT &&  after.get(t-1) == DISK_DARK)
    {
      after.swap(t-1);
      counter++;
    }
  }
}


return sorted_disks(after, counter);


}
