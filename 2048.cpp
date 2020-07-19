#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>

bool merge_num(std::vector<int>& v, int bi, int ei);
void rotate_anti_clock(std::vector<int>& v);
bool game_over(const std::vector<int>& v);
void print_grid(const std::vector<int>& v);

void random(std::vector<int>& v);

int rowcoltoi(int x, int y, int rowlen);

int main(){

  std::vector<int> v;

  std::string filename;

  std::cout << "Please enter the name of the file." << std::endl;
  std::cin >> filename;

  std::ifstream infile;
  infile.open(filename.c_str());

  if(!infile.is_open()){
      std::cout << "error, can't open input file. using default" << std::endl;
      for(int i = 0; i < 15; i++){
        v.push_back(0);
      }
      v.push_back(2);
  }
  else{
    int tmp;
    while(infile >> tmp){
        v.push_back(tmp);
    }
  }

  print_grid(v);
  std::string move;
  while(game_over(v) != true) {
    std::cin >> move;

    int side = std::sqrt(v.size());
    int sum = 0;

    if (move == "a"){//left
      for (int i = 0; i < v.size(); i=i+side){
        sum = sum + merge_num(v, i, i+side);
      }
      if (sum != 0){
        random(v);
        print_grid(v);
      }
    }

    if (move == "w"){//up
      rotate_anti_clock(v);
      for (int i = 0; i < v.size(); i=i+side){
        sum = sum + merge_num(v, i, i+side);
      }
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      if (sum != 0){
        random(v);
        print_grid(v);
      }
    }

    if (move == "s"){//down
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      for (int i = 0; i < v.size(); i=i+side){
        sum = sum + merge_num(v, i, i+side);
      }
      rotate_anti_clock(v);
      if (sum != 0){
        random(v);
        print_grid(v);
      }
    }

    if (move == "d"){//right
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      for (int i = 0; i < v.size(); i=i+side){
        sum = sum + merge_num(v, i, i+side);
      }
      rotate_anti_clock(v);
      rotate_anti_clock(v);
      if (sum != 0){
        random(v);
        print_grid(v);
      }
    }
  }
  std::cout << "game over" << std::endl;

  return 0;

}

int rowcoltoi(int x, int y, int rowlen){
    return x*rowlen+y;
}

void random(std::vector<int>& v){//randomly generates 2s in empty spaces when board is changed
  std::vector<int> tmp;
  bool found = false;
  for(int i=0; i<v.size(); i++){
    if(v[i]==0){
      tmp.push_back(i);
    }
  }
  while(found == false){
    int r = rand() % v.size();
    for (int i=0; i<tmp.size(); i++){
      if (tmp[i] == r){
        v[tmp[i]] = 2;
        found = true;
      }
    }
  }
}

bool merge_num(std::vector<int>& v, int bi, int ei){
  //extract part of vector from input vector based on range
  std::vector<int> tmp;
  std::vector<int> old = v;
  int a = 0, b = 0; //a is first number and b is second number
  for(int i = bi; i < ei; i){ //creates a vector filled non zero values
    while(a == 0 && i < ei) {
      a = v[i];
      i++;
    }
    while(b == 0 && i < ei) {
      b = v[i];
      i++;
    }
    if(a == b) {
      tmp.push_back(2*a);
      a = 0;
      b = 0;
    }
    else {
       tmp.push_back(a);
       a = b;
       b = 0;
     }
   }
   tmp.push_back(a);
   while(tmp.size() < (ei-bi)){ //ei - bi is the range
     tmp.push_back(0);
   }
   for(int i = bi; i < ei; i++) { //stores tmp back into original vector
     v[i] = tmp[i-bi];
   }
   if(old == v){
     return false;
   }
   else{
     return true;
   }
}

void rotate_anti_clock(std::vector<int>& v){
  std::vector<int> tmp;
  int side = std::sqrt(v.size());
  int col = side - 1;
  while (col != -1){
    for (int i = 0; i < side; i++){
      tmp.push_back(v[rowcoltoi(i, col, side)]);
    }
    col--;
  }
  for (int i = 0; i <= v.size(); i++){
    v[i] = tmp[i];
  }
}

bool game_over(const std::vector<int>& v){//checks for zeros, and same number horizontally and vertically
  int side = std::sqrt(v.size());
  for (int i = 0; i < side; i++){
    for (int j = 0; j < side; j++){
      if (v[rowcoltoi(i, j, side)] == 0){
        return false;
      }
      else if (rowcoltoi(i, j, side) % side == (side - 1)){
        if (v[rowcoltoi(i, j, side)] == v[(rowcoltoi(i, j, side)) + side]){
          return false;
        }
      }
      else {
        if ((v[rowcoltoi(i, j, side)] == v[(rowcoltoi(i, j, side)) + 1]) ||
            (v[rowcoltoi(i, j, side)] == v[(rowcoltoi(i, j, side)) + side]) ){
              return false;
        }
      }
    }
  }
  return true;
}

void print_grid(const std::vector<int>& v){
  std::cout << std::endl;
  int side = std::sqrt(v.size());
  for (int i = 0; i < side; i++){
    for (int j = 0; j < side; j++){
      std::cout << v[rowcoltoi(i, j, side)] << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
