#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <iostream>

using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector< priority_queue< pair<Len, int> , vector< pair<Len,int> >, greater< pair<Len,int> > > > Queue;

const Len INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra {
    // Number of nodes
    int n_;
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    Adj adj_;
    Adj cost_;
    // distance_[0] stores distances for the forward search,
    // and distance_[1] stores distances for the backward search.
    vector<vector<Len>> distance_;
    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset_;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward(visited_[0]) or backward(visited_[1]) search.
    vector<vector<bool>> visited_;


    Len shortest_path(int start, int target)
    {
        Len final_dist = INFINITY;
        for (const int node : workset_)
        {
            if (distance_[0][node] + distance_[1][node] < final_dist)
                final_dist = distance_[0][node] + distance_[1][node];
        }
        return final_dist;
    }

public:
    Bidijkstra(int n, Adj adj, Adj cost)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(2, vector<bool>(n))
    { workset_.reserve(n); }

    // Initialize the data structures before new query,
    // clear the changes made by the previous query.
    void clear() {
        // for (int i = 0; i < n_; ++i) {
        //     distance_[0][i] = distance_[1][i] = INFINITY;
        //     visited_[0][i] = false;
        //     visited_[1][i] = false;
        // }
        distance_[0].assign(distance_[0].size(), INFINITY);
        distance_[1].assign(distance_[1].size(), INFINITY);
        visited_[0].assign(visited_[0].size(), false);
        visited_[1].assign(visited_[1].size(), false);
        workset_.clear();
    }

    // Processes visit of either forward or backward search 
    // (determined by value of side), to node v trying to
    // relax the current distance by dist.
    void visit(Queue& q, int side, int v, Len dist) {
        // For each edge connected to the current vertex v
        for(size_t i = 0; i < adj_[side][v].size(); ++i)
        {
            int next_v = adj_[side][v][i];
            Len new_dist = dist + cost_[side][v][i];
            if (new_dist < distance_[side][next_v])
            {
                q[side].push(std::make_pair(new_dist, next_v));
                distance_[side][next_v] = new_dist;
            }
        }
        visited_[side][v] = true;
        workset_.push_back(v);
    }

    // Returns the distance from s to t in the graph.
    Len query(int s, int t) {
        clear();
        //vector of priority_queues
        //q[0] forward
        //q[1] backward
        Queue q(2);
        distance_[0][s] = 0;
        distance_[1][t] = 0;
        q[0].push(std::make_pair(0, s));
        q[1].push(std::make_pair(0, t));
        
        // Implement the rest of the algorithm yourself
        while (!q[0].empty() && !q[1].empty())
        {
            std::pair<Len, int> v;
            //Forward dijkstra
            do {
            v = q[0].top(); q[0].pop();
            } while (visited_[0][v.second]);
            visit(q, 0, v.second, v.first);
            //shortest path has been explored
            //now need to extract;
            if (visited_[1][v.second])
                return shortest_path(s, t);

            //backward dijkstra
            do {
                v = q[1].top(); q[1].pop();
            } while (visited_[1][v.second]);
            visit(q, 1, v.second, v.first);

            //shortest path has been explored
            //now need to extract;
            if (visited_[0][v.second])
                return shortest_path(s, t);
        }

        return -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
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

    Bidijkstra bidij(n, adj, cost);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", bidij.query(u-1, v-1));
        bidij.clear();
    }
}
