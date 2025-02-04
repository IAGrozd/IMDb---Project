#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


const char MOVIES_FILE[] = "movies.txt";

struct Movie {
    char* title;
    int year;
    char* genre;
    char* director;
    char* actors;
    float rating;
    int ratingCount;
};

void showAdminMenu(Movie*& movies, int& movieCount, int& capacity);
void showUserMenu(Movie*& movies, int& movieCount);
void addMovie(Movie*& movies, int& movieCount, int& capacity);
void searchByTitle(Movie* movies, int movieCount);
void searchByGenre(Movie* movies, int movieCount);
void browseMovies(Movie* movies, int movieCount);
void changeMovie(Movie* movies, int movieCount);
void deleteMovie(Movie*& movies, int& movieCount);
void rateMovie(Movie* movies, int movieCount);
void sortMovies(Movie* movies, int movieCount);
void filterByRating(Movie* movies, int movieCount);
void loadMovies(Movie*& movies, int& movieCount, int& capacity);
void saveMovies(Movie* movies, int movieCount);
bool substrSearch(const char* str, const char* sub);
char* copyStr(const char* source);
void resizeMoviesArr(Movie*& movies, int& capacity);
char* createStr();
float setPrecision(float);

int main() {
    Movie* movies = nullptr;
    int movieCount = 0;
    int capacity = 5;
    movies = new Movie[capacity];

    loadMovies(movies, movieCount, capacity);

    while (true) {
        cout << "\nChoose your role:\n";
        cout << "1. Administrator\n";
        cout << "2. Regular User\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            showAdminMenu(movies, movieCount, capacity);
            break;
        case 2:
            showUserMenu(movies, movieCount);
            break;
        case 3:
            saveMovies(movies, movieCount);
            delete[] movies;
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

float setPrecision(float rate) {
    int num = rate * 10;
    rate = num / 10;
    return rate;
}

char* createStr() {
    int capacity = 50; 
    int size = 0;      
    char* str = new char[capacity]; 
    str[0] = '\0';     

    while (true) {
        char ch;
        ch = cin.get(); 

        
        if (ch == '\n') {
            break;
        }

        
        if (size + 1 >= capacity) {
            capacity *= 2; 
            char* newStr = new char[capacity];

            
            for (int i = 0; i < size; i++) {
                newStr[i] = str[i];
            }

            delete[] str; 
            str = newStr; 
        }

        
        str[size++] = ch;
        str[size] = '\0'; 
    }

    return str; 
}


void showAdminMenu(Movie*& movies, int& movieCount, int& capacity) {
    while (true) {
        cout << "\nAdministrator Menu:\n";
        cout << "1. Add a new movie\n";
        cout << "2. Search for a movie by title\n";
        cout << "3. Search for a movie by genre\n";
        cout << "4. Browse all movies\n";
        cout << "5. Change a movie\n";
        cout << "6. Delete a movie\n";
        cout << "7. Sort and filter movies\n";
        cout << "8. Exit to main menu\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addMovie(movies, movieCount, capacity);
            break;
        case 2:
            searchByTitle(movies, movieCount);
            break;
        case 3:
            searchByGenre(movies, movieCount);
            break;
        case 4:
            browseMovies(movies, movieCount);
            break;
        case 5:
            changeMovie(movies, movieCount);
            break;
        case 6:
            deleteMovie(movies, movieCount);
            break;
        case 7:
            sortMovies(movies, movieCount);
            break;
        case 8:
            saveMovies(movies, movieCount);
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}


void showUserMenu(Movie*& movies, int& movieCount) {
    while (true) {
        cout << "\nRegular User Menu:\n";
        cout << "1. Search for a movie by title\n";
        cout << "2. Search for a movie by genre\n";
        cout << "3. Browse all movies\n";
        cout << "4. Rate a movie\n";
        cout << "5. Filter movies by rating\n";
        cout << "6. Exit to main menu\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            searchByTitle(movies, movieCount);
            break;
        case 2:
            searchByGenre(movies, movieCount);
            break;
        case 3:
            browseMovies(movies, movieCount);
            break;
        case 4:
            rateMovie(movies, movieCount);
            break;
        case 5:
            filterByRating(movies, movieCount);
            break;
        case 6:
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}


void addMovie(Movie*& movies, int& movieCount, int& capacity) {
    if (movieCount >= capacity) {
        resizeMoviesArr(movies, capacity);
    }

    Movie newMovie;

    cout << "Enter movie title: ";
    newMovie.title = createStr();

    cout << "Enter release year: ";
    cin >> newMovie.year;
    cin.ignore();

    cout << "Enter genre: ";
    newMovie.genre = createStr();

    cout << "Enter director: ";
    newMovie.director = createStr();

    cout << "Enter actors (comma-separated): ";
    newMovie.actors = createStr();

    newMovie.rating = 5.0;
    newMovie.ratingCount = 1;

    movies[movieCount++] = newMovie;
    cout << "Movie added successfully!\n";
}


void searchByTitle(Movie* movies, int movieCount) {
    cout << "Enter title or part of the title to search: ";
    char* searchedTitle = createStr();

    bool found = false;
    for (int i = 0; i < movieCount; i++) {
        if (substrSearch(movies[i].title, searchedTitle)) {
            cout << "\nTitle: " << movies[i].title << "\n"
                << "Year: " << movies[i].year << "\n"
                << "Genre: " << movies[i].genre << "\n"
                << "Director: " << movies[i].director << "\n"
                << "Actors: " << movies[i].actors << "\n"
                << "Rating: " << movies[i].rating << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No movies found matching the title.\n";
    }
}


char* copyStr(const char* source) {
    int length = 0;
    while (source[length] != '\0') {
        length++;
    }

    char* newString = new char[length + 1];
    for (int i = 0; i < length; i++) {
        newString[i] = source[i];
    }
    newString[length] = '\0';

    return newString;
}

void searchByGenre(Movie* movies, int movieCount) {
    cout << "Enter genre to search: ";
    char* searchedGenre = createStr();

    bool found = false;
    for (int i = 0; i < movieCount; i++) {
        if (substrSearch(movies[i].genre, searchedGenre)) {
            cout << "\nTitle: " << movies[i].title << "\n"
                << "Year: " << movies[i].year << "\n"
                << "Genre: " << movies[i].genre << "\n"
                << "Director: " << movies[i].director << "\n"
                << "Actors: " << movies[i].actors << "\n"
                << "Rating: " << movies[i].rating << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No movies found matching the genre.\n";
    }
}

void browseMovies(Movie* movies, int movieCount) {
    if (movieCount == 0) {
        cout << "No movies in the database.\n";
        return;
    }

    for (int i = 0; i < movieCount; i++) {
        cout << "\nTitle: " << movies[i].title << "\n"
            << "Year: " << movies[i].year << "\n"
            << "Genre: " << movies[i].genre << "\n"
            << "Director: " << movies[i].director << "\n"
            << "Actors: " << movies[i].actors << "\n"
            << "Rating: " << movies[i].rating << "\n";
    }
}

void deleteMovie(Movie*& movies, int& movieCount) {
    cout << "Enter the title of the movie to delete: ";
    char* delMovie = createStr();

    for (int i = 0; i < movieCount; i++) {
        if (substrSearch(movies[i].title, delMovie)) {
            delete[] movies[i].title;
            delete[] movies[i].genre;
            delete[] movies[i].director;
            delete[] movies[i].actors;

            for (int j = i; j < movieCount - 1; j++) {
                movies[j] = movies[j + 1];
            }

            movieCount--;
            cout << "Movie deleted successfully.\n";
            return;
        }
    }

    cout << "Movie not found.\n";
}

void rateMovie(Movie* movies, int movieCount) {
    
    cout << "Enter the title of the movie to rate: ";
    char* titleToRate = createStr();

    for (int i = 0; i < movieCount; i++) {
        if (substrSearch(movies[i].title, titleToRate)) {
            cout << "Enter your rating (1-10): ";
            float userRating;
            cin >> userRating;
            cin.ignore();

            if (userRating < 1.0 || userRating > 10.0) {
                cout << "Invalid rating. Please enter a value between 1 and 10.\n";
                return;
            }

            movies[i].rating = ((movies[i].rating * movies[i].ratingCount) + userRating) / (movies[i].ratingCount + 1);
            movies[i].ratingCount++;

            movies[i].rating = setPrecision(movies[i].rating);

            cout << "Thank you for rating the movie.\n";
            return;
        }
    }

    cout << "Movie not found.\n";
}

void filterByRating(Movie* movies, int movieCount) {
    cout << "Enter minimum rating to filter movies: ";
    float minRating;
    cin >> minRating;
    cin.ignore();

    bool found = false;
    for (int i = 0; i < movieCount; i++) {
        if (movies[i].rating >= minRating) {
            cout << "\nTitle: " << movies[i].title << "\n"
                << "Year: " << movies[i].year << "\n"
                << "Genre: " << movies[i].genre << "\n"
                << "Director: " << movies[i].director << "\n"
                << "Actors: " << movies[i].actors << "\n"
                << "Rating: " << movies[i].rating << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No movies found with a rating above or equal to " << minRating << ".\n";
    }
}

bool substrSearch(const char* str, const char* sub) {
    for (int i = 0; str[i] != '\0'; i++) {
        bool match = true;
        for (int j = 0; sub[j] != '\0'; j++) {
            if (str[i + j] == '\0' || str[i + j] != sub[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}


void changeMovie(Movie* movies, int movieCount) {
    cout << "Enter the title of the movie to change: ";
    char* movieToChange = createStr();

    for (int i = 0; i < movieCount; i++) {
        if (substrSearch(movies[i].title, movieToChange)) {
            cout << "\nEditing Movie: " << movies[i].title << "\n";

            cout << "Enter new title (leave empty to keep current): ";
            char* newTitle = createStr();
            if (newTitle[0] != '\0') {
                delete[] movies[i].title;
                movies[i].title = copyStr(newTitle);
            }
            delete[] newTitle;

            cout << "Enter new release year (0 to keep current): ";
            int newYear;
            cin >> newYear;
            cin.ignore();
            if (newYear != 0) {
                movies[i].year = newYear;
            }

            cout << "Enter new genre (press Enter to keep current): ";
            char* newGenre = createStr();
            if (newGenre[0] != '\0') {
                delete[] movies[i].genre;
                movies[i].genre = copyStr(newGenre);
            }
            delete[] newGenre;

            cout << "Enter new director (press Enter to keep current): ";
            char* newDirector = createStr();
            if (newDirector[0] != '\0') {
                delete[] movies[i].director;
                movies[i].director = copyStr(newDirector);
            }
            delete[] newDirector;

            cout << "Enter new actors (press Enter to keep current): ";
            char* newActors = createStr();
            if (newActors[0] != '\0') {
                delete[] movies[i].actors;
                movies[i].actors = copyStr(newActors);
            }
            delete[] newActors;

            cout << "Enter new rating (1-10 or 0 to keep current): ";
            float newRating;
            cin >> newRating;
            cin.ignore();
            if (newRating != 0) {
                if (newRating >= 1.0 && newRating <= 10.0) {
                    movies[i].rating = newRating;
                }
                else {
                    cout << "Invalid rating. Keeping the current rating.\n";
                }
            }
            
            cout << "Movie details updated successfully!\n";
            return;
        }
    }

    cout << "Movie not found.\n";
}


void resizeMoviesArr(Movie*& movies, int& capacity) {
    int newCapacity = capacity * 2;
    Movie* newMovies = new Movie[newCapacity];

   
    for (int i = 0; i < capacity; i++) {
        newMovies[i] = movies[i];
    }

    
    delete[] movies;
    movies = newMovies;
    capacity = newCapacity;

    cout << "Movies array resized to capacity " << capacity << ".\n";
}


void saveMovies(Movie* movies, int movieCount) {
    ofstream file(MOVIES_FILE);
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < movieCount; i++) {
        file << movies[i].title << "\n"
            << movies[i].year << "\n"
            << movies[i].genre << "\n"
            << movies[i].director << "\n"
            << movies[i].actors << "\n"
            << movies[i].rating << "\n"
            << movies[i].ratingCount << "\n";
    }

    cout << "Movies saved successfully.\n";
}


void loadMovies(Movie*& movies, int& movieCount, int& capacity) {
    ifstream file(MOVIES_FILE);
    if (!file) {
        cout << "No previous movie data found. Starting with an empty database.\n";
        return;
    }

    char buffer[256];
    while (file.getline(buffer, 256)) {
        if (movieCount >= capacity) {
            resizeMoviesArr(movies, capacity);
        }

        movies[movieCount].title = copyStr(buffer);

        file >> movies[movieCount].year;
        file.ignore(); //to ignore '\n'

        file.getline(buffer, 256);
        movies[movieCount].genre = copyStr(buffer);

        file.getline(buffer, 256);
        movies[movieCount].director = copyStr(buffer);

        file.getline(buffer, 256);
        movies[movieCount].actors = copyStr(buffer);

        file >> movies[movieCount].rating;
        file >> movies[movieCount].ratingCount;
        file.ignore();

        movieCount++;
    }

    cout << "Movies loaded successfully.\n";
}

void sortMovies(Movie* movies, int movieCount) {
    for (int i = 0; i < movieCount - 1; i++) {
        for (int j = i + 1; j < movieCount; j++) {
            if (movies[i].rating < movies[j].rating) {
         
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;

            }
        }
    }

    cout << "Movies sorted by rating (descending).\n";
}


