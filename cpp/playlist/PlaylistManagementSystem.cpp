#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For std::shuffle
#include <random>    // For std::default_random_engine
#include <chrono>    // For std::chrono::system_clock

using namespace std;

class SongNode {
public:
    string title;
    string artist;
    SongNode* next;

    SongNode(string t, string a) : title(t), artist(a), next(nullptr) {}
};

class Playlist {
private:
    SongNode* head;

public:
    Playlist() : head(nullptr) {}
    ~Playlist() {
        while (head) { SongNode* old = head; head = head->next; delete old; }
    }
    Playlist(const Playlist&) = delete;
    Playlist& operator=(const Playlist&) = delete;

    void addSong(string title, string artist) {
        SongNode* newNode = new SongNode(title, artist);
        newNode->next = head;
        head = newNode;
    }

    void addSongToEnd(string title, string artist) {
        SongNode* newNode = new SongNode(title, artist);
        if(!head)
        {
          head = newNode;
          return;
        }

        SongNode* current = head;

        while(current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;

    }

    void reversePlaylist() {

      SongNode* previous = nullptr;
      SongNode* current = head;
      SongNode* next = nullptr;

      if(!head || !head->next)
      {
        return;
      }

      while(current != nullptr)
      {
          next = current->next;
          current->next = previous;
          previous = current;
          current = next;
      }
        head = previous;

    }

    void shufflePlaylist() {
        // Convert linked list to vector for shuffling
        vector<SongNode*> nodes;
        SongNode* current = head;
        while (current != nullptr) {
            nodes.push_back(current);
            current = current->next;
        }

        // Shuffle using modern C++ random library
        auto seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
        shuffle(nodes.begin(), nodes.end(), default_random_engine(seed));

        // Rebuild the linked list from shuffled vector
        head = nullptr;
        SongNode* tail = nullptr;
        for (SongNode* node : nodes) {
            if (head == nullptr) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
        if (tail != nullptr) {
            tail->next = nullptr; // Ensure the last node points to nullptr
        }
    }

    void printPlaylist() {
        SongNode* current = head;
        cout << "Playlist:" << endl;
        while (current != nullptr) {
            cout << current->title << " by " << current->artist << endl;
            current = current->next;
        }
    }
};

int main() {
    Playlist myPlaylist;

    myPlaylist.addSong("Africa","TOTO");
    myPlaylist.addSong("Song2", "Artist2");
    myPlaylist.addSong("Song3", "Artist3");

    cout << "Initial Playlist:" << endl;
    myPlaylist.printPlaylist();

    myPlaylist.reversePlaylist();
    cout << "\nReversed Playlist:" << endl;
    myPlaylist.printPlaylist();

    myPlaylist.shufflePlaylist();
    cout << "\nShuffled Playlist:" << endl;
    myPlaylist.printPlaylist();
    return 0;
}
