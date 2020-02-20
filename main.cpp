#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_set>

using namespace std;

const string prefix = "c_incunabula";
const string input_file = prefix + ".txt";
const string output_file = prefix + ".out";

ifstream fin("/home/iulia/Downloads/" + input_file);
ofstream fout("/home/iulia/CLionProjects/hashcode-2020/" + output_file);

vector<int> scores;
unordered_set<int> scanned_books;

struct LibraryInfo {
  int index;
  int signup_days;
  int num_shipped;
  long long score;
  priority_queue<pair<int, int>, vector<pair<int, int>>> books;
  vector<int> scanned_books;

  LibraryInfo() {
    index = signup_days = num_shipped = -1;
    score = -1;
  }

  LibraryInfo& operator=(const LibraryInfo& other) = default;

  LibraryInfo(const LibraryInfo& other) {
    index = other.index;
    signup_days = other.signup_days;
    num_shipped = other.num_shipped;
    score = other.score;
    books = other.books;
    scanned_books = other.scanned_books;
  }

  const bool operator<(const LibraryInfo& other) const {
    return score < other.score;
  }
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

  priority_queue<LibraryInfo, vector<LibraryInfo>> libraries;
  for (int lib = 0; lib < num_libraries; lib++) {
    LibraryInfo info;
    info.index = lib;

    int num_books;
    fin >> num_books >> info.signup_days >> info.num_shipped;
    for (int i = 0; i < num_books; i++) {
      int book_id;
      fin >> book_id;
      info.books.push({scores[book_id], book_id});
    }
    info.score = 1LL * (days - info.signup_days) * info.num_shipped;
    libraries.push(info);
  }

  vector<LibraryInfo> signed_up;
  vector<LibraryInfo> finished_for_sign_up(days, LibraryInfo());
  finished_for_sign_up[libraries.top().signup_days] = libraries.top();
  cout << libraries.top().index << ' ';
  cout << "AICI" << finished_for_sign_up[libraries.top().signup_days].index << endl;
  libraries.pop();

  for (int day = 0; day < days; day++) {
    // Is smth finished for sing up on this day?
    if (finished_for_sign_up[day].index >= 0) {
      signed_up.push_back(finished_for_sign_up[day]);
      cout << "FINISHED SIGN UP FOR " << finished_for_sign_up[day].index << " ON DAY " << day << endl;
      if (!libraries.empty()) {
        const auto library = libraries.top();
        libraries.pop();
        cout << "STARTED SIGN UP FOR LIBRARY " << library.index << " on day " << day << endl;
        finished_for_sign_up[day + library.signup_days - 1] = library;
      }
    }

    // Scan books;
    for (auto& library : signed_up) {
      for (int scanned = 0; scanned < library.num_shipped && !library.books.empty(); ) {
        pair<int, int> top_book = library.books.top();
        if (scanned_books.count(top_book.second)) {
          library.books.pop();
          continue;
        }
        scanned_books.insert(top_book.second);
        library.scanned_books.push_back(top_book.second);
        scanned++;
      }
    }
  }

  cout << "SOLTION: " << endl;
  fout << signed_up.size() << endl;
  for (const LibraryInfo& lib : signed_up) {
    fout << lib.index << ' ' << lib.scanned_books.size() << endl;
    for (int book_id : lib.scanned_books) {
      fout << book_id << ' ';
    }
    fout << endl;
  }
  return 0;
}