#include "ladder.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <word_list_file>" << endl;
        return 1;
    }

    string filename = argv[1];
    string start_word, end_word;
    
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;
    
    for (char& c : start_word) c = tolower(c);
    for (char& c : end_word) c = tolower(c);
    
    if (start_word == end_word) {
        cerr << "Error: Start and end words are the same" << endl;
        return 1;
    }

    set<string> word_list;
    try {
        load_words(word_list, filename);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    if (word_list.find(end_word) == word_list.end()) {
        cerr << "Error: End word '" << end_word << "' not found in the word list" << endl;
        return 1;
    }

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    
    print_word_ladder(ladder);
    
    if (!ladder.empty()) {
        bool valid = true;
        for (size_t i = 0; i < ladder.size() - 1; ++i) {
            if (!is_adjacent(ladder[i], ladder[i+1])) {
                cout << "Invalid word ladder: '" << ladder[i] << "' and '" 
                     << ladder[i+1] << "' are not adjacent." << endl;
                valid = false;
                break;
            }
        }
        if (valid) {
            cout << "Word ladder is valid." << endl;
        }
    }

    return 0;
}