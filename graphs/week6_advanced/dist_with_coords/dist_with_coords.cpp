#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>

using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef vector<vector<vector<int>>> Adj;
typedef long long Len;
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INFINITE = numeric_limits<Len>::max() / 4;

class AStar {
    // See the descriptions of these fields in the starter for friend_suggestion
    int n_;
    Adj adj_;
    Adj cost_;
    vector<vector<Len>> distance_;
    vector<int> workset_;
    vector<vector<bool>> visited_;
    // Coordinates of the nodes
    std::vector<std::pair<Len,Len>> xy_;

    Len euc_dist(std::pair<Len, Len> u, std::pair<Len, Len> v)
    {
        Len x = pow((long double)u.first - (long double)v.first, 2);
        Len y = pow((long double)u.second - (long double)v.second, 2);
        return sqrt(x + y);
    }
    
public:
    AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len,Len>> xy)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n_, INFINITE)), visited_(2, vector<bool>(n)), xy_(xy)
    { workset_.reserve(n); }

    // See the description of this method in the starter for friend_suggestion
    void clear() {
        // for (int i = 0; i < workset_.size(); ++i) {
        //     int v = workset_[i];
        //     distance_[0][v] = distance_[1][v] = INFINITE;
        //     visited_[v] = false;
        // }
        distance_[0].assign(n_, INFINITE);
        distance_[1].assign(n_, INFINITE);
        visited_[0].assign(n_, false);
        visited_[1].assign(n_, false);
        workset_.clear();
    }

    // See the description of this method in the starter for friend_suggestion
    void visit(Queue& q, int side, int v, Len dist, int t) {
        // Implement this method yourself
        for (int i = 0; i < adj_[side][v].size(); ++i)
        {
            int next_v = adj_[side][v][i];
            Len edge = cost_[side][v][i];
            Len cur_dist = dist + edge;
            if (cur_dist < distance_[side][next_v])
            {
                distance_[side][next_v] = cur_dist;
                Len est_dist = cur_dist + euc_dist(xy_[next_v], xy_[t]);
                q[side].push(std::make_pair(est_dist, next_v));
            }
        }
        visited_[side][v] = true;
        workset_.push_back(v);
    }

    // Returns the distance from s to t in the graph
    Len query(int s, int t) {
        clear();
        Queue q(2);
        // visit(q, 0, s, 0);
        // visit(q, 1, t, 0);
        q[0].push(std::make_pair(0,s));
        distance_[0][s] = 0;
        // q[1].push(std::make_pair(0,t));
        // Implement the rest of the algorithm yourself

        while (!q[0].empty())
        {
            std::pair<Len, int> v = q[0].top(); q[0].pop();
            if (v.second == t)
                return distance_[0][t]; 

            if (!visited_[0][v.second])
                visit(q, 0, v.second, distance_[0][v.second], t);
        }

        return -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<Len,Len>> xy(n);
    for (int i=0;i<n;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a,b);
    }
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }

    AStar astar(n, adj, cost, xy);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", astar.query(u-1, v-1));
    }
}
