#include "ladder.h"
#include <algorithm> 

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " for words '" << word1 << "' and '" << word2 << "'" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs(int(str1.length()) - int(str2.length())) > d) {
        return false;
    }

    if (str1.length() == str2.length()) {
        int diff = 0;
        for (size_t i = 0; i < str1.length(); ++i) {
            if (str1[i] != str2[i]) {
                diff++;
                if (diff > d) {
                    return false;
                }
            }
        }
        return true;
    }

    if (abs(int(str1.length()) - int(str2.length())) == 1) {
        const string& shorter = (str1.length() < str2.length()) ? str1 : str2;
        const string& longer = (str1.length() < str2.length()) ? str2 : str1;
        
        for (size_t i = 0; i <= shorter.length(); ++i) {
            bool match = true;
            for (size_t j = 0; j < i; ++j) {
                if (shorter[j] != longer[j]) {
                    match = false;
                    break;
                }
            }
            
            if (match) {
                for (size_t j = i; j < shorter.length(); ++j) {
                    if (shorter[j] != longer[j+1]) {
                        match = false;
                        break;
                    }
                }
            }
            
            if (match) {
                return true;
            }
        }
    }
    
    return false;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "End word not in the word list");
        return {};
    }
    
    if (begin_word == end_word) {
        return {begin_word};
    }
    
    queue<vector<string>> ladder_queue;
    set<string> visited;
    
    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = current_ladder.back();
        
        for (const string& word : word_list) {
            if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                    return new_ladder;
                }
                
                visited.insert(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) {
        throw runtime_error("Can't open word list file: " + file_name);
    }
    
    string word;
    while (in >> word) {
        for (char& c : word) {
            c = tolower(c);
        }
        word_list.insert(word);
    }
    
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder (length " << ladder.size() << "):" << endl;
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

void verify_word_ladder(const vector<string>& ladder) {
    if (ladder.size() <= 1) {
        return;  
    }
    
    for (size_t i = 0; i < ladder.size() - 1; ++i) {
        if (!is_adjacent(ladder[i], ladder[i+1])) {
            cout << "Invalid word ladder: '" << ladder[i] << "' and '" 
                 << ladder[i+1] << "' are not adjacent." << endl;
            return;
        }
    }
    
    cout << "Word ladder is valid." << endl;
}