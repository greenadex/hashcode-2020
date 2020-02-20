#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

const string prefix = "a_example";
const string input_file = prefix + ".txt";
const string output_file = prefix + ".out";

ifstream fin("/home/iulia/Downloads/" + input_file);
ofstream fout("/home/iulia/CLionProjects/hashcode-2020/" + output_file);

vector<int> scores;

struct LibraryInfo {
  int signup_days;
  int num_shipped;
  set<int> book_ids;
};

int main() {
  int books, num_libraries, days;
  fin >> books >> num_libraries >> days;
  scores.reserve(books);
  for (int i = 0; i < books; i++) {
    int val;
    fin >> val;
    scores.push_back(val);
  }

  for (int score : scores) {
     cout << score << ' ';
  }
  cout << endl;

  vector<LibraryInfo> libraries;
  libraries.reserve(num_libraries);
  for (int lib = 0; lib < num_libraries; lib++) {
    LibraryInfo info;
    int num_books;
    fin >> num_books >> info.signup_days >> info.num_shipped;
    for (int i = 0; i < num_books; i++) {
      int book_id;
      fin >> book_id;
      info.book_ids.insert(book_id);
    }
    libraries.push_back(info);
  }

  for (const auto& l : libraries) {
    cout << l.num_shipped << ' ' << l.signup_days << endl;
    for (const int id : l.book_ids) {
      cout << id << ' ';
    }
    cout << endl;
  }
  return 0;
}