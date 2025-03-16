#include "ladder.h"
#include <algorithm> 

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " for words '" << word1 << "' and '" << word2 << "'" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len_diff = abs(int(str1.length()) - int(str2.length()));
    if (len_diff > d) {
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
        return diff <= d;
    }

    const string& shorter = (str1.length() < str2.length()) ? str1 : str2;
    const string& longer = (str1.length() < str2.length()) ? str2 : str1;
    for (size_t i = 0, j = 0; i < shorter.length(); ++i, ++j) {
        if (shorter[i] != longer[j]) {
            return shorter.substr(i) == longer.substr(j + 1);
        }
    }
    
    return true;
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

    map<string, vector<string>> wildcard_map;
    
    for (const string& word : word_list) {
        for (size_t i = 0; i < word.length(); i++) {
            string pattern = word;
            pattern[i] = '*';  
            wildcard_map[pattern].push_back(word);
        }
        
        wildcard_map["+" + word].push_back(word);  
    }
    
    queue<vector<string>> ladder_queue;
    set<string> visited;
    
    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = current_ladder.back();
        
        for (size_t i = 0; i < last_word.length(); i++) {
            string pattern = last_word;
            pattern[i] = '*';
            
            for (const string& candidate : wildcard_map[pattern]) {
                if (visited.find(candidate) != visited.end() || candidate == last_word) {
                    continue;
                }
                
                if (is_adjacent(last_word, candidate)) {
                    vector<string> new_ladder = current_ladder;
                    new_ladder.push_back(candidate);
                    
                    if (candidate == end_word) {
                        return new_ladder;
                    }
                    
                    visited.insert(candidate);
                    ladder_queue.push(new_ladder);
                }
            }
        }
        
        for (const string& candidate : word_list) {
            if (visited.find(candidate) != visited.end() || 
                abs(int(candidate.length()) - int(last_word.length())) != 1) {
                continue;
            }
            
            if (is_adjacent(last_word, candidate)) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(candidate);
                
                if (candidate == end_word) {
                    return new_ladder;
                }
                
                visited.insert(candidate);
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
        cout << "No ladder" << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for (const string& word : ladder) {
        cout << word << " "; 
    }

    cout << endl;
}

void verify_word_ladder() {
    return;
}