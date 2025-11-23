#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <regex>
#include <set>
#include <array>

using namespace std;

// РЕГУЛЯРКА ДЛЯ ДКА: ((a|b)*aa*b(a|b)*|bb*a(a|b)*)abab(a|b)(a|b)
string getRandomString(int n, const string& alphabet) {
    string s = "";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, alphabet.size() - 1);
    for (int i = 0; i < n; i++){
        s += alphabet[dist(gen)];
    }
    return s;
}

bool checkRegex(const string& word) {
    regex r("((a|b)*aa*b(a|b)*|bb*a(a|b)*)abab(a|b)(a|b)");
    return regex_match(word, r);
}

int getLetterNum(const char c, const string& alphabet){
    if (c == 'a') {
        return 0;
    }
    if (c == 'b') {
        return 1;
    }
    return -1;
}

//  ДКА
pair<array<array<int, 2>, 14>, array<int, 3>> initDFA(){
    array<array<int, 2>, 14> dfa;
    
    for (int i = 0; i < 14; i++) {
        dfa[i][0] = -1;
        dfa[i][1] = -1;
    }
    
    // State 1
    dfa[1][0] = 5;
    dfa[1][1] = 6;
    
    // State 2 (final)
    dfa[2][0] = 8;
    dfa[2][1] = 9;
    
    // State 3 (final)
    dfa[3][0] = 12;
    dfa[3][1] = 13;
    
    // State 4 (final)
    dfa[4][0] = 8;
    dfa[4][1] = 7;
    
    // State 5
    dfa[5][0] = 5;
    dfa[5][1] = 7;
    
    // State 6
    dfa[6][0] = 7;
    dfa[6][1] = 6;
    
    // State 7
    dfa[7][0] = 8;
    dfa[7][1] = 7;
    
    // State 8
    dfa[8][0] = 8;
    dfa[8][1] = 9;
    
    // State 9
    dfa[9][0] = 10;
    dfa[9][1] = 7;
    
    // State 10
    dfa[10][0] = 8;
    dfa[10][1] = 11;
    
    // State 11
    dfa[11][0] = 12;
    dfa[11][1] = 13;
    
    // State 12
    dfa[12][0] = 2;
    dfa[12][1] = 3;
    
    // State 13
    dfa[13][0] = 2;
    dfa[13][1] = 4;

    array<int, 3> dfaFinalStates = {2, 3, 4};
    
    return {dfa, dfaFinalStates};
}

//  НКА (46 состояний: 0-45)
pair<vector<vector<set<int>>>, array<int, 1>> initNFA(){
    vector<vector<set<int>>> nfa(46);

    for (int i = 0; i < 46; i++) {
        nfa[i].resize(2);
    }
  
    nfa[0][0] = {1, 2, 4, 5, 6};
    nfa[0][1] = {};

    nfa[1][0] = {2, 3, 5, 6};
    nfa[1][1] = {7, 17, 18, 20, 22, 24, 25, 26};

    nfa[2][0] = {2, 3, 5, 6};
    nfa[2][1] = {};

    nfa[3][0] = {2, 3, 5, 6};
    nfa[3][1] = {7, 17, 18, 20, 22, 24, 25, 26};

    nfa[4][0] = {2, 3, 5, 6};
    nfa[4][1] = {7, 17, 18, 20, 22, 24, 25, 26};

    nfa[5][0] = {};
    nfa[5][1] = {7, 17, 18, 20, 22, 24, 25, 26};

    nfa[6][0] = {};
    nfa[6][1] = {7, 17, 18, 20, 22, 24, 25, 26};

    nfa[7][0] = {18, 19, 20, 22, 23, 25, 26, 27, 28};
    nfa[7][1] = {18, 20, 21, 22, 23, 25, 26};

    nfa[8][0] = {};
    nfa[8][1] = {9, 10, 12, 13, 14};

    nfa[9][0] = {15, 17, 18, 20, 22, 24, 25, 26};
    nfa[9][1] = {10, 11, 13, 14};

    nfa[10][0] = {};
    nfa[10][1] = {10, 11, 13, 14};

    nfa[11][0] = {15, 17, 18, 20, 22, 24, 25, 26};
    nfa[11][1] = {10, 11, 13, 14};

    nfa[12][0] = {15, 17, 18, 20, 22, 24, 25, 26};
    nfa[12][1] = {10, 11, 13, 14};

    nfa[13][0] = {15, 17, 18, 20, 22, 24, 25, 26};
    nfa[13][1] = {};

    nfa[14][0] = {15, 17, 18, 20, 22, 24, 25, 26};
    nfa[14][1] = {};

    nfa[15][0] = {18, 19, 20, 22, 23, 25, 26, 27, 28};
    nfa[15][1] = {18, 20, 21, 22, 23, 25, 26};

    // State 16 (initial)
    nfa[16][0] = {1, 2, 4, 5, 6};
    nfa[16][1] = {9, 10, 12, 13, 14};

    nfa[17][0] = {18, 19, 20, 22, 23, 25, 26, 27, 28};
    nfa[17][1] = {18, 20, 21, 22, 23, 25, 26};

    nfa[18][0] = {18, 19, 20, 22, 23, 25, 26};
    nfa[18][1] = {};

    nfa[19][0] = {18, 19, 20, 22, 23, 25, 26, 27, 28};
    nfa[19][1] = {18, 20, 21, 22, 23, 25, 26};

    nfa[20][0] = {};
    nfa[20][1] = {18, 20, 21, 22, 23, 25, 26};

    nfa[21][0] = {18, 19, 20, 22, 23, 25, 26, 27, 28};
    nfa[21][1] = {18, 20, 21, 22, 23, 25, 26};

    nfa[22][0] = {18, 19, 20, 22, 23, 25, 26};
    nfa[22][1] = {18, 20, 21, 22, 23, 25, 26};

    nfa[23][0] = {18, 19, 20, 22, 23, 25, 26, 27, 28};
    nfa[23][1] = {18, 20, 21, 22, 23, 25, 26};

    nfa[24][0] = {18, 19, 20, 22, 23, 25, 26, 27, 28};
    nfa[24][1] = {18, 20, 21, 22, 23, 25, 26};

    nfa[25][0] = {27, 28};
    nfa[25][1] = {};

    nfa[26][0] = {27, 28};
    nfa[26][1] = {};

    nfa[27][0] = {};
    nfa[27][1] = {29, 30};

    nfa[28][0] = {};
    nfa[28][1] = {29, 30};

    nfa[29][0] = {31, 32};
    nfa[29][1] = {};

    nfa[30][0] = {31, 32};
    nfa[30][1] = {};

    nfa[31][0] = {};
    nfa[31][1] = {33, 34, 36, 38};

    nfa[32][0] = {};
    nfa[32][1] = {33, 34, 36, 38};

    nfa[33][0] = {35, 39, 40, 42, 44};
    nfa[33][1] = {37, 39, 40, 42, 44};

    nfa[34][0] = {35, 39, 40, 42, 44};
    nfa[34][1] = {};

    nfa[35][0] = {41, 45};
    nfa[35][1] = {43, 45};

    nfa[36][0] = {};
    nfa[36][1] = {37, 39, 40, 42, 44};

    nfa[37][0] = {41, 45};
    nfa[37][1] = {43, 45};

    nfa[38][0] = {35, 39, 40, 42, 44};
    nfa[38][1] = {37, 39, 40, 42, 44};

    nfa[39][0] = {41, 45};
    nfa[39][1] = {43, 45};

    nfa[40][0] = {41, 45};
    nfa[40][1] = {};

    nfa[42][0] = {};
    nfa[42][1] = {43, 45};

    nfa[44][0] = {41, 45};
    nfa[44][1] = {43, 45};

    // Остальные состояния
    nfa[41][0] = {};
    nfa[41][1] = {};
    nfa[43][0] = {};
    nfa[43][1] = {};
    nfa[45][0] = {};
    nfa[45][1] = {};

    array<int, 1> nfaFinalStates = {45};
    
    return {nfa, nfaFinalStates};
}

bool checkDFA(const array<array<int, 2>, 14>& dfa, const string& word, const string& alphabet, const array<int, 3>& finalStates){
    int currentState = 1;
    
    for (int i = 0; i < word.size(); i++){
        int letterIndex = getLetterNum(word[i], alphabet);
        if (letterIndex == -1) {
            return false;
        }
        
        currentState = dfa[currentState][letterIndex];
        if (currentState == -1){
            return false;
        }
    }
    
    for (int i = 0; i < 3; i++){
        if (currentState == finalStates[i]){
            return true;
        }
    } 
    return false;
}

bool checkNFA(const vector<vector<set<int>>>& nfa, const string& word, const string& alphabet, const array<int, 1> nfaFinalStates){
    set<int> currentStates;
    currentStates.insert(16); // начальное состояние 16

    for (char c : word) {
        int letterIndex = getLetterNum(c, alphabet);
        if (letterIndex == -1) {
            return false;
        }

        set<int> nextStates;
        for (int state : currentStates) {
            const set<int>& transitions = nfa[state][letterIndex];
            nextStates.insert(transitions.begin(), transitions.end());
        }
        
        // Удаляем -1 если есть
        nextStates.erase(-1);
        
        currentStates = nextStates;
        if (currentStates.empty()) {
            return false;
        }
    }

    // Проверяем, есть ли среди текущих состояний финальное
    for (int state : currentStates) {
        if (state == nfaFinalStates[0]) {
            return true;
        }
    }
    return false;
}

void traceDFA(const array<array<int, 2>, 14>& dfa, const string& word, const string& alphabet) {
    int currentState = 1;
    cout << "Трассировка ДКА: " << currentState;
    
    for (int i = 0; i < word.size(); i++){
        int letterIndex = getLetterNum(word[i], alphabet);
        if (letterIndex == -1) {
            cout << " --" << word[i] << "--> [INVALID]" << endl;
            return;
        }
        
        int nextState = dfa[currentState][letterIndex];
        if (nextState == -1){
            cout << " --" << word[i] << "--> [NO TRANSITION]" << endl;
            return;
        }
        
        cout << " --" << word[i] << "--> " << nextState;
        currentState = nextState;
    }
    
    cout << " [FINAL: " << currentState << "]" << endl;
}

void traceNFA(const vector<vector<set<int>>>& nfa, const string& word, const string& alphabet) {
    set<int> currentStates = {16};
    cout << "Трассировка НКА: {16}";
    
    for (int i = 0; i < word.size(); i++) {
        char c = word[i];
        int letterIndex = getLetterNum(c, alphabet);
        
        set<int> nextStates;
        for (int state : currentStates) {
            const set<int>& transitions = nfa[state][letterIndex];
            nextStates.insert(transitions.begin(), transitions.end());
        }
        
        nextStates.erase(-1);
        
        cout << " --" << c << "--> {";
        for (auto it = nextStates.begin(); it != nextStates.end(); ++it) {
            if (it != nextStates.begin()) cout << ",";
            cout << *it;
        }
        cout << "}";
        
        currentStates = nextStates;
        if (currentStates.empty()) {
            cout << " [DEAD END]" << endl;
            return;
        }
    }
    
    bool isFinal = false;
    for (int state : currentStates) {
        if (state == 45) isFinal = true;
    }
    cout << " [FINAL: " << (isFinal ? "YES" : "NO") << "]" << endl;
}

int main(){
    string alphabet = "ab";

    // Инициализация автоматов
    array<array<int, 2>, 14> dfa;
    array<int, 3> dfaFinalStates;
    tie(dfa, dfaFinalStates) = initDFA();

    vector<vector<set<int>>> nfa; 
    array<int, 1> nfaFinalStates;
    tie(nfa, nfaFinalStates) = initNFA();

    // Тестирование конкретных примеров
    cout << "ТЕСТИРОВАНИЕ КОНКРЕТНЫХ ПРИМЕРОВ:" << endl;
    cout << "==================================" << endl;
    
    vector<string> testWords = {
        "aabababab",    // должен быть принят
        "aaabababab",   // должен быть принят  
        "bbabababab",   // должен быть принят
        "bbbabababab",  // должен быть принят
        "baaabababab",  // должен быть принят
        "abaaabababab", // должен быть принят
        "abababab",     // должен быть отвергнут
        "aabababa",     // должен быть отвергнут
        "bbabab",       // должен быть отвергнут
        ""              // должен быть отвергнут
    };

    for (const string& word : testWords) {
        bool regexResult = checkRegex(word);
        bool dfaResult = checkDFA(dfa, word, alphabet, dfaFinalStates);
        bool nfaResult = checkNFA(nfa, word, alphabet, nfaFinalStates);
        
        cout << "Слово: '" << word << "'" << endl;
        cout << "  Регулярка: " << (regexResult ? "ПРИНЯТ" : "ОТВЕРГНУТ") << endl;
        cout << "  ДКА: " << (dfaResult ? "ПРИНЯТ" : "ОТВЕРГНУТ") << endl;
        cout << "  НКА: " << (nfaResult ? "ПРИНЯТ" : "ОТВЕРГНУТ") << endl;
        
        bool allMatch = (regexResult == dfaResult) && (regexResult == nfaResult);
        cout << "  Результат: " << (allMatch ? "✓ СОВПАДАЕТ" : "✗ РАСХОЖДЕНИЕ") << endl;
        
        if (!allMatch) {
            if (regexResult != dfaResult) {
                cout << "  ";
                traceDFA(dfa, word, alphabet);
            }
            if (regexResult != nfaResult) {
                cout << "  ";
                traceNFA(nfa, word, alphabet);
            }
        }
        cout << endl;
    }

    cout << "ФАЗЗ-ТЕСТИРОВАНИЕ:" << endl;
    cout << "==================" << endl;
    
    int totalTests = 0;
    int passedTests = 0;
    vector<string> discrepancies;
    
    for (int i = 0; i <= 15; i++){
        for (int j = 0; j < 100; j++){
            string word = getRandomString(i, alphabet);
            bool regexResult = checkRegex(word);
            bool dfaResult = checkDFA(dfa, word, alphabet, dfaFinalStates);
            bool nfaResult = checkNFA(nfa, word, alphabet, nfaFinalStates);
            
            totalTests++;
            if ((regexResult == dfaResult) && (regexResult == nfaResult)) {
                passedTests++;
            } else {
                discrepancies.push_back(word);
                if (discrepancies.size() <= 5) {
                    cout << "Расхождение: '" << word << "' - Рег:" << regexResult 
                         << " ДКА:" << dfaResult << " НКА:" << nfaResult << endl;
                }
            }
        }
        
        if (i % 3 == 0) {
            cout << "Длина " << i << ": " << passedTests << "/" << totalTests << " тестов пройдено" << endl;
        }
    }   
    
    cout << "ФИНАЛЬНЫЕ РЕЗУЛЬТАТЫ:" << endl;
    cout << "=====================" << endl;
    cout << "Всего тестов: " << totalTests << endl;
    cout << "Успешных: " << passedTests << endl;
    cout << "Неудачных: " << (totalTests - passedTests) << endl;
    cout << "Успешность: " << (passedTests * 100.0 / totalTests) << "%" << endl;
    
    if (passedTests == totalTests) {
        cout << " ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!" << endl;
        cout << "ДКА и НКА эквивалентны регулярному выражению" << endl;
    } else {
        cout << "Обнаружено " << discrepancies.size() << " расхождений" << endl;
    }
    
    return 0;
}
