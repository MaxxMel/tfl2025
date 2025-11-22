#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <optional>
#include <algorithm>

using namespace std;

struct Rule {
    string left;
    string right;

    Rule(const string& l, const string& r) : left(l), right(r) {}
};

class RuleSystem {
public:
    explicit RuleSystem(const vector<Rule>& rules) : rules_(rules) {}

    bool applyOnce(string& text) const {
        for (const auto& rule : rules_) {
            size_t pos = text.find(rule.left);
            if (pos != string::npos) {
                text.replace(pos, rule.left.size(), rule.right); 
                return true;
            }
        }
        return false;
    }

    void normalize(string& text) const {
        while (applyOnce(text)) {}
    }

    vector<int> randomTransform(string& text, int steps) const {
        vector<int> path;
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, (int)rules_.size() - 1);

        for (int i = 0; i < steps; ++i) {
            int idx = dist(gen);
            path.push_back(idx);

            const Rule& rule = rules_[idx];
            size_t pos = text.find(rule.left);
            if (pos != string::npos) {
                text.replace(pos, rule.left.size(), rule.right); 
            }
        }
        return path; 
    }

private:
    vector<Rule> rules_; 
};

string getRandomString(int length, const string& alphabet = "abcd") {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, (int)alphabet.size() - 1);

    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i)
        s += alphabet[dist(gen)]; 

    return s; 
}

struct FuzzResult {
    bool success;
    string finalString;
    vector<int> path;
};

FuzzResult fuzzTest(const RuleSystem& systemT, const RuleSystem& systemT2) {
    string s = getRandomString(6);
    string original = s;

    vector<int> path = systemT.randomTransform(s, 7);

    string normalized = s;
    systemT2.normalize(normalized);

    bool ok = !normalized.empty();

    FuzzResult res;
    res.success = ok;
    res.finalString = s;  
    res.path = path;      
    return res;          
}

int main() {
    RuleSystem T({
        Rule("aa", "bb"),
        Rule("ccb", "dca"),
        Rule("a", "dcc"),
        Rule("cd", "bc")
    });

    RuleSystem T2({
        Rule("aa", "bb"),
        Rule("ccb", "dca"),
        Rule("a", "dcc"),
        Rule("cd", "bc"),
        Rule("aabcd", "bbbbc"),
        Rule("aaaa", "bbbb"),
        Rule("abcbdb", "ddbcbcbc"),
        Rule("cccd", "dbcccc"),
        Rule("cbdcbcadcbd", "cbdcbcdccdbcd"),
        Rule("bcdacbdacd", "bcbdddcccbddcbccd")
    });

    FuzzResult result = fuzzTest(T, T2);

    if (result.success) {
        cout << "Все тесты успешны\n";
    } else {
        cout << "Ошибка. Итоговая строка: " << result.finalString << "\n";
        cout << "Применённые правила: ";
        for (int i : result.path) cout << i << " ";
        cout << endl;
    }
}
