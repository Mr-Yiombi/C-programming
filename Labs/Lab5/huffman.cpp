#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

const int SIZE = 5000;

struct HuffNode {
    char chart;
    int freq;
    HuffNode* left;
    HuffNode* right;

    HuffNode(char c, int f) : chart(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Comp {
    bool operator()(HuffNode* left, HuffNode* right) {
        return left->freq > right->freq;
    }
};

struct HuffmanStruct {
    HuffNode* root;
    unordered_map<char, string> huffCodeMap;

    void createMap(HuffNode* node, const string& code) {
        if (!node) return;

        if (node->chart != '\0') {
            huffCodeMap[node->chart] = code;
        }

        createMap(node->left, code + "0");
        createMap(node->right, code + "1");
    }

    void createTree(const unordered_map<char, int>& frequencyMap) {
        priority_queue<HuffNode*, vector<HuffNode*>, Comp> minHeap;

        for (auto& entry : frequencyMap) {
            minHeap.push(new HuffNode(entry.first, entry.second));
        }

        while (minHeap.size() > 1) {
            HuffNode* left = minHeap.top(); minHeap.pop();
            HuffNode* right = minHeap.top(); minHeap.pop();

            HuffNode* sumNode = new HuffNode('\0', left->freq + right->freq);
            sumNode->left = left;
            sumNode->right = right;

            minHeap.push(sumNode);
        }

        root = minHeap.top();
        createMap(root, "");
    }

    unordered_map<char, string> getHuff() const {
        return huffCodeMap;
    }

    void deleteTree(HuffNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    ~HuffmanStruct() {
        deleteTree(root);
    }
};

unordered_map<char, int> createFreq(const string& text) {
    unordered_map<char, int> frequencyMap;
    for (char c : text) {
        frequencyMap[c]++;
    }
    return frequencyMap;
}

void readfile(const string& filename, char arr[], int size) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    int index = 0;
    char ch;

    while (file.get(ch) && index < size - 1) {
        if (ch != '\r') {
            arr[index++] = ch;
        }
    }

    arr[index] = '\0';
    file.close();
}

string getchar(char currentChar) {
    switch (currentChar) {
        case '\n': return "\\n";
        case '\t': return "\\t";
        case ' ': return "' '";
        case '\'': return "\\'";
        case '\"': return "\\\"";
        case '\\': return "\\\\";
        default: return string(1, currentChar);
    }
}

int main() {
    char filename[SIZE], problem[SIZE];
    cout << endl;

    cout << "> Filename: ";
    cin >> filename;
    readfile(filename, problem, SIZE);

    string text(problem);

    unordered_map<char, int> frequeMap = createFreq(text);
    HuffmanStruct huffman;
    huffman.createTree(frequeMap);
    unordered_map<char, string> huffcodemap = huffman.getHuff();

    // 모든 문자를 아스키 코드 순서로 정렬하여 출력
    vector<pair<char, string>> sortmap;
    for (auto& entry : frequeMap) {
        sortmap.emplace_back(entry.first, huffcodemap[entry.first]);
    }

    sort(sortmap.begin(), sortmap.end(), [](const pair<char, string>& a, const pair<char, string>& b) {
        return a.first < b.first;
    });

    cout << "> " << problem << endl;
    cout << "> letters: " << text.length() << ", bits: " << text.length() * 8 << endl;
    cout << "> --------------------------" << endl;
    cout << "> Huffman code table" << endl;
    cout << "> Char.  Freq.   Code" << endl;

    for (const auto& entry : sortmap) {
        string newchar = getchar(entry.first);
        cout << "> " << newchar << "    " << left << setw(3) << setfill(' ') << frequeMap[entry.first] << "    "<< left << setw(5) << setfill(' ') << entry.second << endl;

    }

    string stort;
    for (char c : text) {
        stort += huffcodemap[c] + " ";
    }
    stort = stort.substr(0, stort.size() - 1);
    cout << "> --------------------------" << endl;
    cout << "> Encoding result: " << stort.length() - count(stort.begin(), stort.end(), ' ') << " bits" << endl;
    cout << "> " << stort << endl;
    cout << endl;

    return 0;
}
