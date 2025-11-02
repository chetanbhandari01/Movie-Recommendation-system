#include <iostream>
#include <string>
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


class QueueNode {//watch later
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
            cout << "\nFirst movie added successfully!\n";
            return;
        }
        
        Movie* temp = head;
        while (temp->nextMovie != NULL) {
            temp = temp->nextMovie;
        }
        
        temp->nextMovie = newMovie;
        totalMovies = totalMovies + 1;
        cout << "\nMovie added successfully!\n";
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
            count = count + 1;
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
                count = count + 1;
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
            arraySize = arraySize + 1;
            temp = temp->nextMovie;
        }
        
        for (int i = 0; i < arraySize - 1; i = i + 1) {
            for (int j = 0; j < arraySize - i - 1; j = j + 1) {
                if (movieArray[j]->movieRating < movieArray[j + 1]->movieRating) {
                    Movie* tempMovie = movieArray[j];
                    movieArray[j] = movieArray[j + 1];
                    movieArray[j + 1] = tempMovie;
                }
            }
        }
       
        int displayCount = 5;
        if (arraySize < 5) {
            displayCount = arraySize;
        }
        
        for (int i = 0; i < displayCount; i = i + 1) {
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
            cout << "\n'" << title << "' added to Watch Later!\n";
            return;
        }
        
        rearNode->nextNode = newNode;
        rearNode = newNode;
        queueSize = queueSize + 1;
        
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
        
        if (frontNode == NULL) {
            rearNode = NULL;
        }
        
        delete temp;
        queueSize = queueSize - 1;
        
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
            position = position + 1;
        }
        
        cout << "\nTotal movies in queue: " << queueSize << "\n";
    }
    
    int isQueueEmpty() {
        if (frontNode == NULL) {
            return 1; 
        }
        return 0; 
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
        
        for (int i = 0; i < 50; i = i + 1) {
            for (int j = 0; j < 50; j = j + 1) {
                ratingsArray[i][j] = 0.0;
            }
        }
    }
    
    void addRatingToArray(int userId, int movieId, float rating) {
        if (userId < 50 && movieId < 50) {
            ratingsArray[userId][movieId] = rating;
            cout << "\nRating saved successfully!\n";
            
            if (userId >= totalUsers) {
                totalUsers = userId + 1;
            }
            if (movieId >= totalRatedMovies) {
                totalRatedMovies = movieId + 1;
            }
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
        for (int i = 0; i < 50; i = i + 1) {
            if (ratingsArray[userId][i] > 0) {
                count = count + 1;
                cout << "Movie ID " << i << ": ";
                cout << ratingsArray[userId][i] << "/5.0\n";
            }
        }
        
        if (count == 0) {
            cout << "No ratings found for this user!\n";
        }
    }
    
    float getAverageRating(int movieId) {
        if (movieId >= 50) {
            return 0.0;
        }
        
        float sum = 0.0;
        int count = 0;
        
        for (int i = 0; i < 50; i = i + 1) {
            if (ratingsArray[i][movieId] > 0) {
                sum = sum + ratingsArray[i][movieId];
                count = count + 1;
            }
        }
        
        if (count > 0) {
            return sum / count;
        }
        return 0.0;
    }
};

// MAIN SYSTEM CLASS
class MovieRecommendationSystem {
public:
    MovieLinkedList movieDatabase;
    WatchLaterQueue watchLater;
    RatingSystem ratings;
    
    
    MovieRecommendationSystem() {
        loadSampleMovies();
        loadSampleRatings();
    }
    

    void loadSampleMovies() {
        cout << "\nLoading movie database...\n";
        
        movieDatabase.addNewMovie(1, "The Shawshank Redemption", "Drama", 9.3, 1994);
        movieDatabase.addNewMovie(2, "The Dark Knight", "Action", 9.0, 2008);
        movieDatabase.addNewMovie(3, "Inception", "Sci-Fi", 8.8, 2010);
        movieDatabase.addNewMovie(4, "Forrest Gump", "Drama", 8.8, 1994);
        movieDatabase.addNewMovie(5, "The Matrix", "Sci-Fi", 8.7, 1999);
        movieDatabase.addNewMovie(6, "Interstellar", "Sci-Fi", 8.6, 2014);
        movieDatabase.addNewMovie(7, "The Godfather", "Crime", 9.2, 1972);
        movieDatabase.addNewMovie(8, "Pulp Fiction", "Crime", 8.9, 1994);
        movieDatabase.addNewMovie(9, "The Avengers", "Action", 8.0, 2012);
        movieDatabase.addNewMovie(10, "Titanic", "Romance", 7.9, 1997);
        movieDatabase.addNewMovie(11, "Avatar", "Sci-Fi", 7.8, 2009);
        movieDatabase.addNewMovie(12, "Gladiator", "Action", 8.5, 2000);
        movieDatabase.addNewMovie(13, "The Lion King", "Animation", 8.5, 1994);
        movieDatabase.addNewMovie(14, "Star Wars", "Sci-Fi", 8.6, 1977);
        movieDatabase.addNewMovie(15, "Jurassic Park", "Adventure", 8.2, 1993);
        
        cout << "\nDatabase loaded successfully!\n";
    }

    void loadSampleRatings() {
        ratings.addRatingToArray(0, 1, 5.0);
        ratings.addRatingToArray(0, 3, 4.5);
        ratings.addRatingToArray(0, 5, 4.0);
        ratings.addRatingToArray(1, 2, 5.0);
        ratings.addRatingToArray(1, 7, 4.8);
    }
   
    void showMainMenu() {
        cout << "\n\n";
        cout << "========================================\n";
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
    
    void handleViewAllMovies() {
        movieDatabase.displayAllMovies();
    }
    
    void handleSearchById() {
        int searchId;
        cout << "\nEnter Movie ID to search: ";
        cin >> searchId;
        
        Movie* foundMovie = movieDatabase.searchMovieById(searchId);
        
        if (foundMovie != NULL) {
            foundMovie->showMovie();
        } else {
            cout << "\nMovie with ID " << searchId << " not found!\n";
        }
    }

    void handleViewByGenre() {
        string genreChoice;
        
        cout << "\n========================================\n";
        cout << "Available Genres:\n";
        cout << "1. Action\n";
        cout << "2. Drama\n";
        cout << "3. Sci-Fi\n";
        cout << "4. Crime\n";
        cout << "5. Romance\n";
        cout << "6. Animation\n";
        cout << "7. Adventure\n";
        cout << "========================================\n";
        cout << "Enter genre name: ";
        cin >> genreChoice;
        
        movieDatabase.displayByGenre(genreChoice);
    }

    void handleTopRated() {
        movieDatabase.displayTopRated();
    }

    void handleAddMovie() {
        int newId, newYear;
        string newTitle, newGenre;
        float newRating;
        
        cout << "\n--- Add New Movie ---\n";
        cout << "Enter Movie ID: ";
        cin >> newId;
        
        cin.ignore(); 
        
        cout << "Enter Movie Title: ";
        getline(cin, newTitle);
        
        cout << "Enter Genre: ";
        getline(cin, newGenre);
        
        cout << "Enter Rating (0.0-10.0): ";
        cin >> newRating;
        
        cout << "Enter Release Year: ";
        cin >> newYear;
        
        movieDatabase.addNewMovie(newId, newTitle, newGenre, newRating, newYear);
    }

    void handleAddToWatchLater() {
        int movieId;
        cout << "\nEnter Movie ID to add to Watch Later: ";
        cin >> movieId;
        
        Movie* foundMovie = movieDatabase.searchMovieById(movieId);
        
        if (foundMovie != NULL) {
            watchLater.addToQueue(foundMovie->movieId, 
                                 foundMovie->movieTitle, 
                                 foundMovie->movieGenre);
        } else {
            cout << "\nMovie not found!\n";
        }
    }
    
    void handleViewWatchLater() {
        watchLater.displayQueue();
    }
    
    void handleRemoveFromWatchLater() {
        watchLater.removeFromQueue();
    }
    
    void handleAddRating() {
        int userId, movieId;
        float rating;
        
        cout << "\n--- Add Movie Rating ---\n";
        cout << "Enter User ID (0-49): ";
        cin >> userId;
        
        cout << "Enter Movie ID: ";
        cin >> movieId;
        
        cout << "Enter Rating (0.0-5.0): ";
        cin >> rating;
        
        if (rating < 0.0 || rating > 5.0) {
            cout << "\nInvalid rating! Must be between 0.0 and 5.0\n";
            return;
        }
        
        ratings.addRatingToArray(userId, movieId, rating);
    }
   
    void handleViewUserRatings() {
        int userId;
        cout << "\nEnter User ID to view ratings: ";
        cin >> userId;
        
        ratings.displayUserRatings(userId);
    }
    
    void startSystem() {
        int userChoice;
        int continueProgram = 1;
        
        cout << "\n========================================\n";
        cout << "   WELCOME TO MOVIE RECOMMENDATION\n";
        cout << "========================================\n";
        
        while (continueProgram == 1) {
            showMainMenu();
            cin >> userChoice;
            
            if (userChoice == 1) {
                handleViewAllMovies();
            }
            else if (userChoice == 2) {
                handleSearchById();
            }
            else if (userChoice == 3) {
                handleViewByGenre();
            }
            else if (userChoice == 4) {
                handleTopRated();
            }
            else if (userChoice == 5) {
                handleAddMovie();
            }
            else if (userChoice == 6) {
                handleAddToWatchLater();
            }
            else if (userChoice == 7) {
                handleViewWatchLater();
            }
            else if (userChoice == 8) {
                handleRemoveFromWatchLater();
            }
            else if (userChoice == 9) {
                handleAddRating();
            }
            else if (userChoice == 10) {
                handleViewUserRatings();
            }
            else if (userChoice == 11) {
                continueProgram = 0;
                cout << "\n========================================\n";
                cout << "   Thank you for using our system!\n";
                cout << "========================================\n";
            }
            else {
                cout << "\nInvalid choice! Please enter 1-11\n";
            }
        }
    }
};

int main() {
    // Create system object
    MovieRecommendationSystem mySystem;
    
    // Start the system
    mySystem.startSystem();
    
    return 0;
}
