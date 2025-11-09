#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Movie {
public:
    int movieId;
    string movieTitle;
    string movieGenre;
    float movieRating;
    int movieYear;
    Movie* nextMovie;

    Movie() {
        movieId = 0;
        movieTitle = "";
        movieGenre = "";
        movieRating = 0.0;
        movieYear = 0;
        nextMovie = NULL;
    }

    void setMovieData(int id, string title, string genre, float rating, int year) {
        movieId = id;
        movieTitle = title;
        movieGenre = genre;
        movieRating = rating;
        movieYear = year;
    }

    void showMovie() {
        cout << "\n----------------------------------\n";
        cout << "Movie ID: " << movieId << "\n";
        cout << "Title: " << movieTitle << "\n";
        cout << "Genre: " << movieGenre << "\n";
        cout << "Rating: " << movieRating << "/10\n";
        cout << "Year: " << movieYear << "\n";
        cout << "----------------------------------\n";
    }
};

class QueueNode {
public:
    int movieId;
    string movieTitle;
    string movieGenre;
    QueueNode* nextNode;

    QueueNode() {
        movieId = 0;
        movieTitle = "";
        movieGenre = "";
        nextNode = NULL;
    }
};

class MovieLinkedList {
public:
    Movie* head;
    int totalMovies;

    MovieLinkedList() {
        head = NULL;
        totalMovies = 0;
    }

    void addNewMovie(int id, string title, string genre, float rating, int year) {
        Movie* newMovie = new Movie();
        newMovie->setMovieData(id, title, genre, rating, year);
        newMovie->nextMovie = NULL;

        if (head == NULL) {
            head = newMovie;
            totalMovies = 1;
        } else {
            Movie* temp = head;
            while (temp->nextMovie != NULL)
                temp = temp->nextMovie;
            temp->nextMovie = newMovie;
            totalMovies++;
        }
    }

    void saveToFile() {
        ofstream fout("movies.txt");
        Movie* temp = head;
        while (temp != NULL) {
            fout << temp->movieId << "|"
                 << temp->movieTitle << "|"
                 << temp->movieGenre << "|"
                 << temp->movieRating << "|"
                 << temp->movieYear << "\n";
            temp = temp->nextMovie;
        }
        fout.close();
    }

    void loadFromFile() {
        ifstream fin("movies.txt");
        if (!fin) return;
        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            int id, year;
            float rating;
            string title, genre;
            size_t pos = 0;
            pos = line.find('|'); id = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
            pos = line.find('|'); title = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find('|'); genre = line.substr(0, pos); line.erase(0, pos + 1);
            pos = line.find('|'); rating = stof(line.substr(0, pos)); line.erase(0, pos + 1);
            year = stoi(line);
            addNewMovie(id, title, genre, rating, year);
        }
        fin.close();
    }

    Movie* searchMovieById(int searchId) {
        Movie* temp = head;
        while (temp != NULL) {
            if (temp->movieId == searchId) return temp;
            temp = temp->nextMovie;
        }
        return NULL;
    }

    void displayAllMovies() {
        if (head == NULL) {
            cout << "\nNo movies found!\n";
            return;
        }
        Movie* temp = head;
        cout << "\n======= ALL MOVIES =======\n";
        while (temp != NULL) {
            temp->showMovie();
            temp = temp->nextMovie;
        }
    }
};

class WatchLaterQueue {
public:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int queueSize;

    WatchLaterQueue() {
        frontNode = NULL;
        rearNode = NULL;
        queueSize = 0;
        loadFromFile();
    }

    void addToQueue(int id, string title, string genre) {
        QueueNode* newNode = new QueueNode();
        newNode->movieId = id;
        newNode->movieTitle = title;
        newNode->movieGenre = genre;
        if (rearNode == NULL)
            frontNode = rearNode = newNode;
        else {
            rearNode->nextNode = newNode;
            rearNode = newNode;
        }
        queueSize++;
        saveToFile();
        cout << "\n'" << title << "' added to Watch Later!\n";
    }

    void removeFromQueue() {
        if (frontNode == NULL) {
            cout << "\nWatch Later list is empty!\n";
            return;
        }
        QueueNode* temp = frontNode;
        string removedTitle = temp->movieTitle;
        frontNode = frontNode->nextNode;
        if (frontNode == NULL) rearNode = NULL;
        delete temp;
        queueSize--;
        saveToFile();
        cout << "\n'" << removedTitle << "' removed from Watch Later!\n";
    }

    void displayQueue() {
        if (frontNode == NULL) {
            cout << "\nWatch Later list is empty!\n";
            return;
        }
        cout << "\n======= WATCH LATER =======\n";
        QueueNode* temp = frontNode;
        while (temp != NULL) {
            cout << temp->movieTitle << " (" << temp->movieGenre << ")\n";
            temp = temp->nextNode;
        }
    }

    void saveToFile() {
        ofstream fout("watchlater.txt");
        QueueNode* temp = frontNode;
        while (temp != NULL) {
            fout << temp->movieId << "|"
                 << temp->movieTitle << "|"
                 << temp->movieGenre << "\n";
            temp = temp->nextNode;
        }
        fout.close();
    }

    void loadFromFile() {
        ifstream fin("watchlater.txt");
        if (!fin) return;
        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            int id;
            string title, genre;
            size_t pos = 0;
            pos = line.find('|'); id = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
            pos = line.find('|'); title = line.substr(0, pos); line.erase(0, pos + 1);
            genre = line;
            addToQueue(id, title, genre);
        }
        fin.close();
    }
};

class RatingSystem {
public:
    float ratingsArray[50][50];
    int totalUsers;
    int totalRatedMovies;

    RatingSystem() {
        totalUsers = 0;
        totalRatedMovies = 0;
        for (int i = 0; i < 50; i++)
            for (int j = 0; j < 50; j++)
                ratingsArray[i][j] = 0.0;
        loadRatings();
    }

    void addRatingToArray(int userId, int movieId, float rating) {
        if (userId < 50 && movieId < 50) {
            ratingsArray[userId][movieId] = rating;
            cout << "\nRating saved successfully!\n";
            saveRatings();
        } else {
            cout << "\nInvalid user or movie ID!\n";
        }
    }

    void displayUserRatings(int userId) {
        cout << "\nRatings by User " << userId << ":\n";
        for (int i = 0; i < 50; i++) {
            if (ratingsArray[userId][i] > 0)
                cout << "Movie ID " << i << ": " << ratingsArray[userId][i] << "/5\n";
        }
    }

    void saveRatings() {
        ofstream fout("ratings.txt");
        for (int i = 0; i < 50; i++)
            for (int j = 0; j < 50; j++)
                if (ratingsArray[i][j] > 0)
                    fout << i << "|" << j << "|" << ratingsArray[i][j] << "\n";
        fout.close();
    }

    void loadRatings() {
        ifstream fin("ratings.txt");
        if (!fin) return;
        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            int userId, movieId;
            float rating;
            size_t pos = 0;
            pos = line.find('|'); userId = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
            pos = line.find('|'); movieId = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
            rating = stof(line);
            ratingsArray[userId][movieId] = rating;
        }
        fin.close();
    }
};


class MovieRecommendationSystem {
public:
    MovieLinkedList movieDatabase;
    WatchLaterQueue watchLater;
    RatingSystem ratings;

    MovieRecommendationSystem() {
        movieDatabase.loadFromFile();
    }

    void showMainMenu() {
        cout << "\n\n======= MOVIE RECOMMENDATION SYSTEM =======\n";
        cout << "1. View All Movies\n";
        cout << "2. Search Movie by ID\n";
        cout << "3. Add New Movie\n";
        cout << "4. Add Movie to Watch Later\n";
        cout << "5. View Watch Later Queue\n";
        cout << "6. Remove from Watch Later\n";
        cout << "7. Add Rating for Movie\n";
        cout << "8. View User Ratings\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
    }

    void startSystem() {
        int choice;
        while (true) {
            showMainMenu();
            cin >> choice;
            if (choice == 1) movieDatabase.displayAllMovies();
            else if (choice == 2) handleSearchById();
            else if (choice == 3) handleAddMovie();
            else if (choice == 4) handleAddToWatchLater();
            else if (choice == 5) watchLater.displayQueue();
            else if (choice == 6) watchLater.removeFromQueue();
            else if (choice == 7) handleAddRating();
            else if (choice == 8) handleViewUserRatings();
            else if (choice == 9) { cout << "\nThank you!\n"; break; }
            else cout << "\nInvalid choice!\n";
        }
    }

    void handleSearchById() {
        int id;
        cout << "Enter Movie ID: ";
        cin >> id;
        Movie* m = movieDatabase.searchMovieById(id);
        if (m) m->showMovie();
        else cout << "Movie not found!\n";
    }

    void handleAddMovie() {
        int id, year; float rating;
        string title, genre;
        cout << "Enter Movie ID: "; cin >> id;
        cin.ignore();
        cout << "Enter Title: "; getline(cin, title);
        cout << "Enter Genre: "; getline(cin, genre);
        cout << "Enter Rating (0-10): "; cin >> rating;
        cout << "Enter Year: "; cin >> year;
        movieDatabase.addNewMovie(id, title, genre, rating, year);
        movieDatabase.saveToFile();
    }

    void handleAddToWatchLater() {
        int id;
        cout << "Enter Movie ID to add: ";
        cin >> id;
        Movie* m = movieDatabase.searchMovieById(id);
        if (m)
            watchLater.addToQueue(m->movieId, m->movieTitle, m->movieGenre);
        else
            cout << "Movie not found!\n";
    }

    void handleAddRating() {
        int userId, movieId;
        float rating;
        cout << "Enter User ID: "; cin >> userId;
        cout << "Enter Movie ID: "; cin >> movieId;
        cout << "Enter Rating (0-5): "; cin >> rating;
        ratings.addRatingToArray(userId, movieId, rating);
    }

    void handleViewUserRatings() {
        int userId;
        cout << "Enter User ID: "; cin >> userId;
        ratings.displayUserRatings(userId);
    }
};


int main() {
    MovieRecommendationSystem sys;
    sys.startSystem();
    return 0;
}
