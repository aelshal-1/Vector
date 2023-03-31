#include "Vector.h"


int main() {
  
  //init vector
  Vector<int> nums{1,2,3,4,5,6,7,8,9,10};
  nums.print();
  
  //copy constructor
  Vector<int> nums2(nums);
  nums2.print();
  
  nums2.remove();
  //assignment operator
  nums = nums2;
  nums.print();
  
  nums2.remove();
  nums2.add(20);
  
  //move constructor
  Vector<int> nums3 = std::move(nums2);
  for(auto& i:nums3){
    std::cout << i << " " ;
  }
  std::cout <<std::endl;
  
  Vector<int>nums4;
  nums4 = std::move(nums3);
  nums4.print();
  
  
  // Init Vector using file
  Vector<int> v("../numbers.txt");
  v.findSync(27709884);
  v.findAsync(27709884);
  return 0;
}