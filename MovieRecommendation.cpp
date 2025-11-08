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
            while (temp->nextMovie != NULL) {
                temp = temp->nextMovie;
            }
            temp->nextMovie = newMovie;
            totalMovies++;
        }
    }

    
    void saveToFile() {
        ofstream fout("movies.txt");
        if (!fout) {
            cout << "\nError opening file for saving!\n";
            return;
        }

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
        cout << "\nMovies saved successfully to file!\n";
    }

    void loadFromFile() {
    ifstream fin("movies.txt");
    if (!fin) {
        cout << "\nNo saved movie file found. Starting fresh!\n";
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;  // ✅ skip empty lines

        try {
            int id, year;
            float rating;
            string title, genre;
            size_t pos = 0;

            // extract movie ID
            pos = line.find('|');
            if (pos == string::npos) continue;
            id = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            // extract title
            pos = line.find('|');
            if (pos == string::npos) continue;
            title = line.substr(0, pos);
            line.erase(0, pos + 1);

            // extract genre
            pos = line.find('|');
            if (pos == string::npos) continue;
            genre = line.substr(0, pos);
            line.erase(0, pos + 1);

            // extract rating
            pos = line.find('|');
            if (pos == string::npos) continue;
            rating = stof(line.substr(0, pos));
            line.erase(0, pos + 1);

            // remaining part is year
            if (line.empty()) continue;
            year = stoi(line);

            addNewMovie(id, title, genre, rating, year);
        } 
        catch (invalid_argument&) {
            cout << "\n Skipping invalid line in file: " << line << "\n";
            continue;
        }
    }

    fin.close();
    cout << "\nMovies loaded successfully from file!\n";
}


    void displayAllMovies() {
        if (head == NULL) {
            cout << "\nNo movies in database!\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "        ALL MOVIES IN DATABASE\n";
        cout << "========================================\n";
        
        Movie* temp = head;
        int count = 1;
        
        while (temp != NULL) {
            cout << "\n[" << count << "] Movie Details:\n";
            cout << "ID: " << temp->movieId << "\n";
            cout << "Title: " << temp->movieTitle << "\n";
            cout << "Genre: " << temp->movieGenre << "\n";
            cout << "Rating: " << temp->movieRating << "/10\n";
            cout << "Year: " << temp->movieYear << "\n";
            cout << "-----------------------------------\n";
            temp = temp->nextMovie;
            count++;
        }
        
        cout << "\nTotal Movies: " << totalMovies << "\n";
    }
    
    Movie* searchMovieById(int searchId) {
        if (head == NULL) {
            cout << "\nDatabase is empty!\n";
            return NULL;
        }
        
        Movie* temp = head;
        while (temp != NULL) {
            if (temp->movieId == searchId) {
                return temp;
            }
            temp = temp->nextMovie;
        }
        return NULL;
    }
    
    void displayByGenre(string searchGenre) {
        if (head == NULL) {
            cout << "\nNo movies available!\n";
            return;
        }
        
        cout << "\n========================================\n";
        cout << "   Movies in Genre: " << searchGenre << "\n";
        cout << "========================================\n";
        
        Movie* temp = head;
        int count = 0;
        while (temp != NULL) {
            if (temp->movieGenre == searchGenre) {
                count++;
                cout << "\n[" << count << "] " << temp->movieTitle;
                cout << " (" << temp->movieYear << ")";
                cout << " - Rating: " << temp->movieRating << "/10\n";
            }
            temp = temp->nextMovie;
        }

        if (count == 0) {
            cout << "\nNo movies found in this genre!\n";
        }
    }
    
    void displayTopRated() {
        if (head == NULL) {
            cout << "\nNo movies available!\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "         TOP RATED MOVIES\n";
        cout << "========================================\n";
        
        Movie* movieArray[100];
        int arraySize = 0;

        Movie* temp = head;
        while (temp != NULL && arraySize < 100) {
            movieArray[arraySize] = temp;
            arraySize++;
            temp = temp->nextMovie;
        }

        
        for (int i = 0; i < arraySize - 1; i++) {
            for (int j = 0; j < arraySize - i - 1; j++) {
                if (movieArray[j]->movieRating < movieArray[j + 1]->movieRating) {
                    Movie* t = movieArray[j];
                    movieArray[j] = movieArray[j + 1];
                    movieArray[j + 1] = t;
                }
            }
        }

        int displayCount = (arraySize < 5) ? arraySize : 5;
        for (int i = 0; i < displayCount; i++) {
            cout << "\n[" << (i + 1) << "] " << movieArray[i]->movieTitle;
            cout << " - Rating: " << movieArray[i]->movieRating << "/10";
            cout << " (" << movieArray[i]->movieYear << ")\n";
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
    }
    
    void addToQueue(int id, string title, string genre) {
        QueueNode* newNode = new QueueNode();
        newNode->movieId = id;
        newNode->movieTitle = title;
        newNode->movieGenre = genre;
        newNode->nextNode = NULL;
        
        if (rearNode == NULL) {
            frontNode = newNode;
            rearNode = newNode;
            queueSize = 1;
        } else {
            rearNode->nextNode = newNode;
            rearNode = newNode;
            queueSize++;
        }

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
        cout << "\n'" << removedTitle << "' removed from Watch Later!\n";
    }
    
    void displayQueue() {
        if (frontNode == NULL) {
            cout << "\nWatch Later list is empty!\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "        WATCH LATER QUEUE\n";
        cout << "========================================\n";

        QueueNode* temp = frontNode;
        int position = 1;
        while (temp != NULL) {
            cout << "\n[" << position << "] " << temp->movieTitle;
            cout << " (" << temp->movieGenre << ")";
            cout << " - ID: " << temp->movieId << "\n";
            temp = temp->nextNode;
            position++;
        }

        cout << "\nTotal movies in queue: " << queueSize << "\n";
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
    }

    void addRatingToArray(int userId, int movieId, float rating) {
        if (userId < 50 && movieId < 50) {
            ratingsArray[userId][movieId] = rating;
            cout << "\nRating saved successfully!\n";
            if (userId >= totalUsers) totalUsers = userId + 1;
            if (movieId >= totalRatedMovies) totalRatedMovies = movieId + 1;
        } else {
            cout << "\nInvalid user or movie ID!\n";
        }
    }

    void displayUserRatings(int userId) {
        if (userId >= 50) {
            cout << "\nInvalid user ID!\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "   Ratings by User " << userId << "\n";
        cout << "========================================\n";

        int count = 0;
        for (int i = 0; i < 50; i++) {
            if (ratingsArray[userId][i] > 0) {
                cout << "Movie ID " << i << ": " << ratingsArray[userId][i] << "/5.0\n";
                count++;
            }
        }

        if (count == 0)
            cout << "No ratings found for this user!\n";
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
        cout << "\n\n========================================\n";
        cout << "   MOVIE RECOMMENDATION SYSTEM\n";
        cout << "========================================\n";
        cout << "1. View All Movies\n";
        cout << "2. Search Movie by ID\n";
        cout << "3. View Movies by Genre\n";
        cout << "4. View Top Rated Movies\n";
        cout << "5. Add New Movie\n";
        cout << "6. Add Movie to Watch Later\n";
        cout << "7. View Watch Later Queue\n";
        cout << "8. Remove from Watch Later\n";
        cout << "9. Add Rating for Movie\n";
        cout << "10. View User Ratings\n";
        cout << "11. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
    }

    void handleViewAllMovies() { movieDatabase.displayAllMovies(); }

    void handleSearchById() {
        int id;
        cout << "\nEnter Movie ID: ";
        cin >> id;
        Movie* m = movieDatabase.searchMovieById(id);
        if (m) m->showMovie();
        else cout << "\nMovie not found!\n";
    }

    void handleViewByGenre() {
        string genre;
        cout << "\nEnter Genre: ";
        cin >> genre;
        movieDatabase.displayByGenre(genre);
    }

    void handleTopRated() { movieDatabase.displayTopRated(); }

    void handleAddMovie() {
        int id, year;
        float rating;
        string title, genre;
        cout << "\n--- Add New Movie ---\n";
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Genre: ";
        getline(cin, genre);
        cout << "Enter Rating (0-10): ";
        cin >> rating;
        cout << "Enter Year: ";
        cin >> year;
        movieDatabase.addNewMovie(id, title, genre, rating, year);
        movieDatabase.saveToFile();  
    }

    void handleAddToWatchLater() {
        int id;
        cout << "\nEnter Movie ID to add: ";
        cin >> id;
        Movie* m = movieDatabase.searchMovieById(id);
        if (m) watchLater.addToQueue(m->movieId, m->movieTitle, m->movieGenre);
        else cout << "\nMovie not found!\n";
    }

    void handleViewWatchLater() { watchLater.displayQueue(); }

    void handleRemoveFromWatchLater() { watchLater.removeFromQueue(); }

    void handleAddRating() {
        int userId, movieId;
        float rating;
        cout << "\nEnter User ID (0-49): ";
        cin >> userId;
        cout << "Enter Movie ID: ";
        cin >> movieId;
        cout << "Enter Rating (0-5): ";
        cin >> rating;
        ratings.addRatingToArray(userId, movieId, rating);
    }

    void handleViewUserRatings() {
        int userId;
        cout << "\nEnter User ID: ";
        cin >> userId;
        ratings.displayUserRatings(userId);
    }

    void startSystem() {
        int choice;
        while (true) {
            showMainMenu();
            cin >> choice;
            switch (choice) {
                case 1: handleViewAllMovies(); break;
                case 2: handleSearchById(); break;
                case 3: handleViewByGenre(); break;
                case 4: handleTopRated(); break;
                case 5: handleAddMovie(); break;
                case 6: handleAddToWatchLater(); break;
                case 7: handleViewWatchLater(); break;
                case 8: handleRemoveFromWatchLater(); break;
                case 9: handleAddRating(); break;
                case 10: handleViewUserRatings(); break;
                case 11:
                    cout << "\nThank you for using the system!\n";
                    return;
                default:
                    cout << "\nInvalid choice!\n";
            }
        }
    }
};

int main() {
    MovieRecommendationSystem sys;
    sys.startSystem();
    return 0;
}

