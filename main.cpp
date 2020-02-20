#include <iostream>
#include <fstream>

using namespace std;

const string prefix = "";
const string input_file = prefix + ".in";
const string output_file = prefix + ".out";

ifstream fin("/home/iulia/Downloads/" + input_file);
ofstream fout("/home/iulia/CLionProjects/hashcode/" + output_file);

int main() {
  cout << "Hello, World!" << endl;
  return 0;
}