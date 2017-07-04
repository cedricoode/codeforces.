#include <map>
#include <list>
#include <iostream>
#include <vector>

using namespace std;

list<string>::iterator find_candidate(list<string> &li, string const &name) {
    for (list<string>::iterator i = li.begin(); i != li.end(); i++) {
        if (name.compare(*i) == 0) {
            return i;
        }
    }
    return li.end();
}

void recollect_candidates(int last_idx, map<string, int> const &game, list<string> &candidates, int &max_score) {
    // Find max score
    max_score = -1000001;
    candidates.clear();
    for (map<string, int>::const_iterator i = game.begin(); i != game.end(); i++) {
        if (i->second > max_score) {
            max_score = i->second;
            candidates.clear();
            candidates.push_back(i->first);
        } else if (i->second == max_score) {
            candidates.push_back(i->first);
        }
    }

    // Reorder candidates
//    list<string>::iterator previous = candidates.begin();
//    for (list<string>::iterator i = candidates.begin(); i != candidates.end(); i++) {
//        for (int j = last_idx; j >= 0; j--) {
//            if ((*i).compare(seq[j]) == 0) {
//                previous = candidates.insert(previous, *i);
//                candidates.erase(i);
//                i = previous;
//                break;
//            }
//        }
//    }
}

void print_candidate(list<string> & candidates, map<string, int> &score) {
    cout << "printing candidates:" << endl;
    for (list<string>::iterator i = candidates.begin(); i != candidates.end(); i++) {
        cout << *i << " score is: " << score[*i] <<endl;
    }
}

struct Round {
    int score;
    int idx;
    Round(int s, int i) {
        this->score = s;
        this->idx = i;
    }
};

void print_winner(list<string> &, map<string, vector<Round> > &, int);


int main(void) {
    map<string, int> game;
    int n;
    cin >> n;
    string name;
    int score;
//    char sequence[1000][32];
    map<string, vector<Round> > p_seq;
    int max_score = -2000;
    list<string> candidates;

    for (int i = 0; i < n; i++) {
        cin >> name;
        cin >> score;

        if (p_seq.find(name) == p_seq.end()) {
            vector<Round> l;
            Round round(score, i);

            l.push_back(round);
            p_seq[name] = l;
        } else {
            vector<Round> *l = &p_seq[name];
            Round round((l->back()).score + score, i);
            l->push_back(round);
        }

        if (game.find(name) == game.end()) {
            game[name] = score;
        } else {
            game[name] += score;
        }

        if (game[name] > max_score) {
            max_score = game[name];
            candidates.clear();
            candidates.push_back(name);
        } else if (game[name] == max_score) {
            candidates.push_back(name);
        } else {
            if (score < 0 && game[name] - score == max_score) {
                // Possibly change the max score and need to reconstruct
                list<string>::iterator idx = find_candidate(candidates, name);
                if (idx != candidates.end()) {
                    idx = candidates.erase(idx);
                }
                // check candidates size
                if (candidates.size() == 0) {
                    recollect_candidates(i, game, candidates, max_score);
                }
            }
        }
//        print_candidate(candidates, game);
    }

//    cout << "===========" << endl;
//    for(map<string, int>::iterator i = game.begin(); i != game.end(); i++) {
//        cout << i->first << " final score is: " << i-> second << endl;
//    }
//    cout << *candidates.begin() << endl;
    print_winner(candidates, p_seq, max_score);
}

void print_winner(list<string> &candidates, map<string, vector<Round> > &sequence, int max_score) {
    if (candidates.size() == 1) {
        cout << *candidates.begin() << endl;
    } else {
        string winner = *candidates.begin();
        int winner_index = 10000;
        for (list<string>::iterator i = candidates.begin(); i != candidates.end(); i++) {
            vector<Round> l = sequence[*i];
            for (vector<Round>::iterator j = l.begin(); j != l.end(); j++) {
                if ((*j).score >= max_score && (*j).idx < winner_index) {
                    winner_index = (*j).idx;
                    winner = *i;
                    break;
                }
            }
        }
        cout << winner << endl;
    }
}
