#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct strategy {
    int choice; 
    // -1 means forfeit
    // 0/1 means red/black, higher/lower, inside/outside
    double expectation;
    strategy(int c = 0, double e = 0.0) : choice(c), expectation(e) {}
};

int distinctQ(int i, int j) {return i!=j;}
int distinctQ(int i, int j, int k) {return i!=j && j!=k && k!=i;}
int get_suit(int i) {return i / 13;}
int get_value(int i) {return i % 13;}
strategy optimal_suit(int i, int j, int k) {
    int cnt[4] = {0,0,0,0};
    cnt[get_suit(i)] ++;
    cnt[get_suit(j)] ++;
    cnt[get_suit(k)] ++;
    int opt_choice = -1;
    double opt_exp = 4.0;
    for(int w=0; w<4; w++) {
        double exp = 20.0 * (13.0-cnt[w]) / 49.0;
        if(opt_exp < exp) {
            opt_choice = w;
            opt_exp = exp;
        }
    }
    if(opt_exp < 4.0) {
        return strategy(-1, 4.0);
    } else {
        return strategy(opt_choice, opt_exp);
    }
}
int id(int i, int j, int k) {return (i * 52 + j) * 52 + k;}
strategy optimal_inout(int i, int j, const vector<strategy>& suit) {
    double in_exp = 0.0;
    double out_exp = 0.0;
    for(int k=0; k<52; k++) {
        if(distinctQ(i,j,k)) {
            if((get_value(i) <= get_value(k) && get_value(k) <= get_value(j))
            || (get_value(j) <= get_value(k) && get_value(k) <= get_value(i))) {
                // inside
                in_exp += suit[id(i,j,k)].expectation / 50.0;
            } else {                
                out_exp += suit[id(i,j,k)].expectation / 50.0;
            }
        }
    }
    if(in_exp <= 3.0 && out_exp <= 3.0) {
        return strategy(-1, 3.0);
    } else if(in_exp >= out_exp) {
        return strategy(0, in_exp);
    } else {
        return strategy(1, out_exp);
    }
}
int id(int i, int j) {return i * 52 + j;}
strategy optimal_uplow(int i, const vector<strategy>& inside_outside) {    
    double up_exp = 0.0;
    double low_exp = 0.0;
    for(int j=0; j<52; j++) {
        if(distinctQ(i,j)) {
            if(get_value(j) >= get_value(i)) {
                // higher
                up_exp += inside_outside[id(i,j)].expectation / 51.0;
            } else {                
                low_exp += inside_outside[id(i,j)].expectation / 51.0;
            }
        }
    }
    if(up_exp <= 2.0 && low_exp <= 2.0) {
        return strategy(-1, 2.0);
    } else if(up_exp >= low_exp) {
        return strategy(0, up_exp);
    } else {
        return strategy(1, low_exp);
    }
} 

// game description:
/*
initial state $1
red or black: Guess the color of card#1. If correct, state $2; otherwise state $0
higher or lower: Guess higher or lower. 
    higher means card#2>=card#1, lower means card#2<card#1. 
    If correct, state $3; otherwise state $0
inside or outside: 
    inside means card#3 in [card#1,card#2], inclusively;
    If correct, state $4; otherwise state $0
suit:
    Guess the suit of card#4.
    If correct, state $20; otherwise state $0
*/

int main() {
    vector<strategy> upper_lower;
    vector<strategy> inside_outside;
    vector<strategy> suit;
    
    for(int i=0; i<52; i++) {
        for(int j=0; j<52; j++) {
            for(int k=0; k<52; k++) {
                suit.push_back(optimal_suit(i,j,k));
            }
        }
    }    
    for(int i=0; i<52; i++) {
        for(int j=0; j<52; j++) {
            inside_outside.push_back(optimal_inout(i,j,suit));
        }
    }
    for(int i=0; i<52; i++) {
        upper_lower.push_back(optimal_uplow(i,inside_outside));
    }

    double aggr = 0.0;
    for(auto str : upper_lower) {
        aggr += str.expectation / 52.0;
    }
    cout << "optimal bet: " << 500 * aggr / 2.0 << endl;

    string cardface[] = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"
    };
    {
        string options[] = {
            "forfeit", "upper", "lower"
        };
        ofstream ofs("uplow.strat");
        int id = 0;
        for(auto str : upper_lower) {
            ofs << "- " << cardface[get_value(id++)] << " : " << options[str.choice+1] << " " << str.expectation << "\n";
        }
    }
    {
        ofstream ofs("inout.strat");
        string options[] = {
            "forfeit", "inside", "outside"
        };
        string cases[] = {
            "diff", "same"
        };
        for(int i=0; i<13; i++) {
            for(int j=13+i; j<26; j++) {
                strategy str = optimal_inout(i,j,suit);
                ofs << cardface[get_value(i)] << "|" << cardface[get_value(j)] << " : " <<  options[str.choice+1] << " " << str.expectation << "\n";
            }
        }
    }
    ofstream ofs3("suit.strat");
    for(auto str : suit) {
        ofs3 << str.choice << " " << str.expectation << "\n";
    }

    return 0;
}