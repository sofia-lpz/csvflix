#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

class videos {
protected:
  string id;
  string name;
  string genre;
  int length;
  float rating;
  string comments;

public:
  virtual void design() = 0;
  void set_new_rating(float r) { rating = (rating + r) / 2.0; }
  void set_data(string i, string n, string g, int len, float rate, string com) {
    id = i;
    name = n;
    genre = g;
    length = len;
    rating = rate;
    comments = com;
  }
  void print() {
    cout << " " << id << " " << setw(31) << left << name << setw(9) << left
         << genre << setw(6) << left << length << setw(4) << left << rating
         << comments << endl;
  }
  bool search(string a, string c) {
    if (c == name && a == "name") {
      return true;
    }
    if (c == genre && a == "genre") {
      return true;
    }
    return false;
  }
};

class movies : public videos {
public:
void design() {
    cout << "MOVIES" << endl
         << "-ID--Movie Name---------------------Genre-lenght-rating-comments"
         << endl;
  }
void save_file(movies x[],int size) {
  ofstream mfile;
  mfile.open("movies.csv");
  for (int i = 0; i < size; i++) {
    mfile<<x[i].id<<","<<x[i].name<<","<<x[i].genre<<","<<x[i].length<<","<<x[i].rating<<","<<x[i].comments<<endl; 
  }
  mfile.close();
  cout << "Changes saved successfully to movies file";
}

};
class series : public videos {
public:
  void design() {
    cout << "SERIES" << endl
         << "-ID--Series Name--------------------Genre-lenght-rating-comments"
         << endl;
  }
void save_file(series x[], int size) {
  ofstream sfile;
  sfile.open("series.csv");
  for (int i = 0; i < size; i++) {
    sfile <<x[i].id<<","<<x[i].name<<","<<x[i].genre<<","<<x[i].length<<","<<x[i].rating<<","<<x[i].comments<<endl;
  }
  sfile.close();
  cout << "Changes saved successfully to series file";
}
};

string display_user_menu() {
  string choice;
  cout << "-----Welcome to Tecflix-----" << endl << endl;
  cout << "1. Display all videos" << endl << endl;
  cout << "2. Display all movies" << endl;
  cout << "3. Display movies by genre" << endl;
  cout << "4. Display movies by name" << endl;
  cout << "5. Rate movie between 0-5" << endl;
  cout << "6. Save the changes in movie file" << endl << endl;
  cout << "7. Display all series" << endl;
  cout << "8. Display series by genre" << endl;
  cout << "9. Display series by name" << endl;
  cout << "10. Rate series bewteen 0-5" << endl;
  cout << "11. Save the changes in series file" << endl << endl;
  cout << "12. Exit" << endl << endl;
  while (1) {
    cout << "Enter an option: ";
    cin >> choice;
    if (choice == "1" || choice == "2" || choice == "3" || choice == "4" ||
        choice == "5" || choice == "6" || choice == "7" || choice == "8" ||
        choice == "9" || choice == "10" || choice == "11" || choice == "12") {
      return choice;
    } else {
      cout << "> invalid input" << endl;
    }
  }
}

// start function overloading
void display(series x[], int size) {
  x[0].design();
  for (int i = 0; i < size; i++)
    x[i].print();
}
void display(movies x[], int size) {
  x[0].design();
  for (int i = 0; i < size; i++)
    x[i].print();
}

int searchName(movies x[], int size) {
  string name;
  cout << "Enter movie name: ";
  getline(cin, name);
  cout << endl;
  int i;
  for (i = 0; i < size; i++) {
    if (x[i].search("name", name)) {
      x[0].design();
      x[i].print();
      return i;
      break;
    }
  }
  if (i == size) {
    cout << endl << "> movie not found" << endl;
  }
  return size + 1;
}
int searchName(series x[], int size) {
  string name;
  cout << "Enter series name: ";
  getline(cin, name);
  cout << endl;
  int i;
  for (i = 0; i < size; i++) {
    if (x[i].search("name", name)) {
      x[0].design();
      x[i].print();
      return i;
      break;
    }
  }
  if (i == size) {
    cout << endl << "> series not found" << endl;
  }
  return size + 1;
}
// returns index, when not found returns size+1

void searchGenre(movies x[], int size) {
  string genre;
  bool genreFound = false;
  cout << "Enter genre of movies: ";
  getline(cin, genre);
  cout << endl;
  int i;
  for (i = 0; i < size; i++) {
    if (x[i].search("genre", genre)) {
      genreFound = true;
      break;
    }
  }
  if (genreFound) {
    x[0].design();
  }
  for (i = 0; i < size; i++) {
    if (x[i].search("genre", genre)) {
      x[i].print();
    }
  }
  if (!genreFound) {
    cout << endl << "> genre not found" << endl;
  }
}
void searchGenre(series x[], int size) {
  string genre;
  bool genreFound = false;
  cout << "Enter genre of series: ";
  getline(cin, genre);
  cout << endl;
  int i;
  for (i = 0; i < size; i++) {
    if (x[i].search("genre", genre)) {
      genreFound = true;
      break;
    }
  }
  if (genreFound) {
    x[0].design();
  }
  for (i = 0; i < size; i++) {
    if (x[i].search("genre", genre)) {
      x[i].print();
    }
  }
  if (!genreFound) {
    cout << endl << "> genre not found" << endl;
  }
}

void rate(movies x[], int size, int i) {
  float rating;
  if (i > size) {
    return;
  } // when name is not found, searchName function returns size+1
  cout << endl;
  cout << "Enter rating: ";
  while (1) {
    cin >> rating;
    if (rating <= 5 && rating >= 0) {
      cin.ignore();
      break;
    } else {
      cout << "> Invalid rating, enter number between 0 and 5" << endl;
    }
  }
  x[i].set_new_rating(rating);
  cout << "New rating added successfully" << endl;
  cout << endl;
  x[0].design();
  x[i].print();
}
void rate(series x[], int size, int i) {
  float rating;
  if (i > size) {
    return;
  } // when name is not found, searchName function returns size+1
  cout << endl;
  cout << "Enter rating: ";
  while (1) {
    cin >> rating;
    if (rating <= 5 && rating >= 0) {
      cin.ignore();
      break;
    } else {
      cout << "> Invalid rating, enter number between 0 and 5" << endl;
    }
  }
  x[i].set_new_rating(rating);
  cout << "New rating added successfully" << endl;
  cout << endl;
  x[0].design();
  x[i].print();
}
//recieves index to rate, return; when index is size+1

// end function overloading

int main() {
  int m_array_size = 30;
  int s_array_size = 29;

  movies moviearray[m_array_size];
  series seriesarray[s_array_size];
  string line;
  string row[6];

  // read movies file
  ifstream fmovies;
  fmovies.open("movies.csv");
  int j = 0;
  while (getline(fmovies, line)) {
    stringstream ss(line);
    int i = 0;
    while (getline(ss, row[i], ','))
      i++;
    moviearray[j].set_data(row[0], row[1], row[2], stoi(row[3]), stof(row[4]), row[5]);
    j++;
  }
  // end read movies file

  // read series file
  ifstream fseries;
  fseries.open("series.csv");
  int k = 0;
  while (getline(fseries, line)) {
    stringstream ss(line);
    int l = 0;
    while (getline(ss, row[l], ','))
      l++;
    seriesarray[k].set_data(row[0], row[1], row[2], stoi(row[3]), stof(row[4]), row[5]);
    k++;
  }
  // end read series file

  while (1) {
    system("clear");
    string choice = display_user_menu();
    system("clear");
    cin.ignore();

    switch (stoi(choice)) {
    case 1: // display all videos
      display(moviearray, m_array_size);
      cout << endl;
      display(seriesarray, s_array_size);
      break;

    case 2: // display all movies
      display(moviearray, m_array_size);
      break;

    case 3: // display movies by genre
      searchGenre(moviearray, m_array_size);
      break;

    case 4: // search movie by name, valid
      searchName(moviearray, m_array_size);
      break;

    case 5: // change rating of movie, valid
      rate(moviearray, m_array_size, searchName(moviearray, m_array_size));
      break;

    case 6: // save changes in movie file
      moviearray[0].save_file(moviearray, m_array_size);
      break;

    case 7: // display all series
      display(seriesarray, s_array_size);
      break;

    case 8: // display series by genre
      searchGenre(seriesarray, s_array_size);
      break;

    case 9: // search series by name
      searchName(seriesarray, s_array_size);
      break;

    case 10: // change rating of series
      rate(seriesarray, s_array_size, searchName(seriesarray, s_array_size));
      break;

    case 11: // save changes in series file
      seriesarray[0].save_file(seriesarray, s_array_size);
      break;

    case 12: // exit
      cout << "thanks for using tecflix" << endl;
      return 0;
      break;
    }
    cout << endl << endl << "Press any key to return to menu" << endl;
    cin.ignore();
  }
}