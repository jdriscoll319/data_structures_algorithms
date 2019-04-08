#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <forward_list>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<std::forward_list<std::string>> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

    bool find_string(const string& s, size_t hash)
    {
        for(const string& stored : elems[hash])
        {
            if (s == stored)
                return true;
        }
        return false;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") 
        {
            for (const  string& s : elems[query.ind])
                std::cout << s << ' ';
            std::cout << "\n";
        } 
        else 
        {
            size_t hash_val = hash_func(query.s);
            // std::cout << "hash_val: " << hash_val << "\n";
            if (query.type == "add")
            {
                if(!find_string(query.s, hash_val))
                    elems[hash_val].emplace_front(query.s);
            }
            else if (query.type == "find")
                writeSearchResult(find_string(query.s, hash_val));
            else //delete
                elems[hash_val].remove(query.s);
        }
    }

    void processQueries() {
        elems.resize(bucket_count);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
