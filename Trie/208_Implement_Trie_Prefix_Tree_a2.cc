#include <string>


// Time to complete: 30 mins

// Treated as: study problem (research allowed)

// Needed to research:
// - https://en.wikipedia.org/wiki/Trie

// Notes:
// - Early attempt via implementing from Wikipedia Trie description, without any
//   optional optimizations.

//// Begin solution, results at https://leetcode.com/submissions/detail/735416338/


class Trie {
    // "1 <= word.length, prefix.length <= 2000"
public:
    Trie() : root(new TrieNode) {}
    ~Trie() { DestructorDFS(root); }

    void insert(const std::string &word) {
        // given prototype passes `string word`
        TrieNode *temp {root};
        int i;
        for (const auto &c : word) {
            i = c - 'a';  // index in TRIE_CHARSET
            if (temp->children[i] == nullptr) {
                temp->children[i] = new TrieNode;
            }
            temp = temp->children[i];
        }
        temp->is_terminal = true;
    }

    bool search(const std::string &word) {
        // given prototype passes `string word`
        TrieNode *temp {root};
        int i;
        for (const auto &c : word) {
            i = c - 'a';  // index in TRIE_CHARSET
            if (temp->children[i] == nullptr)
                return false;
            temp = temp->children[i];
        }
        return temp->is_terminal;
    }

    bool startsWith(const std::string &prefix) {
        // given prototype passes `string prefix`
        TrieNode *temp {root};
        int i;
        for (const auto &c : prefix) {
            i = c - 'a';  // index in TRIE_CHARSET
            if (temp->children[i] == nullptr)
                return false;
            temp = temp->children[i];
        }
        return true;
    }

private:
    // "word and prefix consist only of lowercase English letters"
    static constexpr int TRIE_CHARSET_SZ {26};
    // static constexpr char TRIE_CHARSET[TRIE_CHARSET_SZ + 1] {
    //                                       "abcdefghijklmnopqrstuvwxyz"};

    struct TrieNode {
        TrieNode *children[TRIE_CHARSET_SZ] {nullptr};
        bool is_terminal {false};
        // optional value, if used like a hashmap
    };

    TrieNode *root;

    void DestructorDFS(TrieNode *root) {
        // DFS traversal to match other operations
        if (root == nullptr)
            return;
        for (int i {0}; i < TRIE_CHARSET_SZ; ++i)
            DestructorDFS(root->children[i]);
        delete root;
    }
};


//// end solution


#include <iostream>
#include <vector>


std::string TestTrieBrief(std::vector<std::string> &commands,
                          std::vector<std::string> &inputs) {
    if (commands.size() != inputs.size())
        throw std::length_error("command and input counts do not match");
    std::string outputs {"[null,"};  // for call to Trie()
    Trie trie;
    int sz (commands.size());
    for (int i{0}; i < sz; ++i) {
        if (commands[i][0] == 'i') {
            trie.insert(inputs[i]);
            outputs.append("null,");
        } else if (commands[i][1] == 'e') {
            outputs.append(trie.search(inputs[i]) ? "true," : "false,");
        } else if (commands[i][1] == 't') {
            outputs.append(trie.startsWith(inputs[i]) ? "true," : "false,");
        }
    }
    outputs[outputs.size() - 1] = ']';  // replace last comma
    return outputs;
}


void TestTrie(std::vector<std::string> &commands,
              std::vector<std::string> &inputs) {
    if (commands.size() != inputs.size())
        throw std::length_error("command and input counts do not match");
    std::cout << std::boolalpha << "Trie trie;\n";
    Trie trie;
    int sz (commands.size());
    for (int i{0}; i < sz; ++i) {
        if (commands[i][0] == 'i') {
            std::cout << "trie.insert(\"" << inputs[i] << "\");\n";
            trie.insert(inputs[i]);
        } else if (commands[i][1] == 'e') {
            std::cout << "trie.search(\"" << inputs[i] << "\"): " <<
                trie.search(inputs[i]) << '\n';
        } else if (commands[i][1] == 't') {
            std::cout << "trie.startsWith(\"" << inputs[i] << "\"): " <<
                trie.startsWith(inputs[i]) << '\n';
        }
    }
}


int main() {
    std::vector<std::string> commands_1 {
        "insert", "search", "search", "startsWith", "insert", "search"
    };
    std::vector<std::string> inputs_1 {
        "apple", "apple", "app", "app", "app", "app"
    };
    std::vector<std::string> commands_2 {
        "insert","insert","insert","insert","insert","insert","search",
        "search","search","search","search","search","search","search",
        "search","startsWith","startsWith","startsWith","startsWith",
        "startsWith","startsWith","startsWith","startsWith","startsWith"
    };
    std::vector<std::string> inputs_2 {
        "app","apple","beer","add","jam","rental","apps",
        "app","ad","applepie","rest","jan","rent","beer",
        "jam","apps","app","ad","applepie",
        "rest","jan","rent","beer","jam"
    };

    std::cout << "TestTrieBrief(commands_1, inputs_1):\n       got: " <<
        TestTrieBrief(commands_1, inputs_1) << '\n';
    std::cout << "  expected: [null,null,true,false,true,null,true]\n";
    TestTrie(commands_1, inputs_1);
    std::cout << '\n';

    std::cout << "TestTrieBrief(commands_2, inputs_2):\n       got: " <<
        TestTrieBrief(commands_2, inputs_2) << '\n';
    std::cout << "  expected: [null,null,null,null,null,null,null,false," \
        "true,false,false,false,false,false,true,true,false,true,true,false," \
        "false,false,true,true,true]\n";
    std::cout << '\n';
    TestTrie(commands_2, inputs_2);
    std::cout << '\n';
}
