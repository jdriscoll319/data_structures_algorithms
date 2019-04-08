#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

class HashTable {
private:
    int bucket_count;
    std::vector<unsigned long long> table;
    static const unsigned long long multiplier = 3;
    static const unsigned long long prime = 1000000007;

    unsigned long long hash_func(const string& s) const {
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash; 
    }

    void precompute(const string& p, const string &t) {

        size_t p_len = p.length();
        size_t t_len = t.length();
        table[t_len - p_len] = hash_func( t.substr(t_len - p_len, p_len) );
        unsigned long long y = 1;
        for (size_t i = 1; i <= p_len; ++i)
            y = (y * multiplier) % prime;
        std::cout << "y: " << y << "\n";

        for (int i = t_len - p_len - 1; i >= 0; --i)
        {
            unsigned long long a = multiplier * table[i+1] % prime;
            unsigned long long b = t[i] % prime;
            unsigned long long c = (y * t[i + p_len]) % prime;
            table[i] = ((a + b - c) % prime + prime) % prime;
        }
    }

public:
    HashTable(const Data &data) 
    {
        bucket_count = (data.text.length() - data.pattern.length()) * 1.3;
        table.resize(data.text.length() - data.pattern.length() + 1);
        precompute(data.pattern, data.text);
    }

    std::vector<size_t> search_text(const Data &data)
    {
        std::vector<size_t> ans;
        size_t hash = hash_func(data.pattern);
        std::cout << "Pattern hash: " << hash << "\n";
        size_t p_len = data.pattern.length();
        for (size_t i = 0; i < table.size(); ++i)
        {
            std::cout << "text at " << i << " hash: " << data.text.substr(i, p_len) << ' ' << table[i] << "\n";
            if (table[i] == hash && data.text.substr(i, p_len) == data.pattern)
                ans.push_back(i);
        }
        return ans;
    }
};


void print_occurrences(const std::vector<size_t>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<size_t> get_occurrences(const Data& input) {
    HashTable table(input);
    const string& s = input.pattern, t = input.text;
    std::vector<size_t> ans = table.search_text(input);
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}