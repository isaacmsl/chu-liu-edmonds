#include <bits/stdc++.h>
#define INF 1e9+7
using namespace std;

vector<int> V;
vector<pair<int,int>> E;
vector<int> W;

vector<pair<int,int>> A;

map<pair<int, int>, int> E_to_W;
map<pair<int, int>, int> E_to_I;

vector<pair<int,int>> S;

pair<int,int> get_best_edge_to_blossom(vector<pair<int,int>> & X, int pos_initial_cicle) {
    map<int, int> in_blossom;
    map<int, pair<int,int>> blossom_from;
    queue<int> to_blossom;

    to_blossom.push(pos_initial_cicle);

    while(!to_blossom.empty()){
        auto b = to_blossom.front();
        to_blossom.pop();
        
        if(in_blossom[b]) continue;
        in_blossom[b] = 1;
        
        for(auto edge : X) {
            if(edge.first == b) {
                to_blossom.push(edge.second);
                blossom_from[edge.second] = edge;
            }
        }
    }

    auto min_weight_to_blossom = INF;
    pair<int,int> best_edge_to_blossom = {-1,-1};
    for (auto edge : E) {
        auto [s, t] = edge;
        auto i = E_to_I[edge];
        if (!in_blossom[s] && in_blossom[t]) {
            auto n_w = W[E_to_I[edge]] - W[E_to_I[blossom_from[t]]];

            if (n_w < min_weight_to_blossom) {
                min_weight_to_blossom = n_w;
                best_edge_to_blossom = edge;
            }
        }
    }
    
    return best_edge_to_blossom;
}

int get_pos_initial_cicle(vector<pair<int,int>> & X) {
    map<int,int> vis;
    
    for(auto edge : X) {
        if (vis[edge.second]) return edge.second;
        vis[edge.second] = 1;
    }

    return -1;
}

void chu_liu_edmonds(){
    auto root = A[0].first;
    
    // Construct S
    for (auto node : V) {
        auto min_weight = INF;
        pair<int,int> min_w_edge;
        for(auto edge : E) {
            if (root == node) {
                if (edge.first == root)
                    S.push_back(edge);
                continue;
            }

            if (edge.second == node && edge.first != root) {
                auto edge_weight = E_to_W[edge];
                if (edge_weight < min_weight) {
                    min_weight = edge_weight;
                    min_w_edge = edge;
                }
            }
        }

        bool has_incident = min_weight != INF;
        if (has_incident) {
            S.push_back(min_w_edge);
        }
    }
    
    bool has_cicle = true;
    while (has_cicle) {
        auto pos_initial_cicle = get_pos_initial_cicle(S);
        has_cicle = pos_initial_cicle != -1;
        auto best_edge_to_blossom = get_best_edge_to_blossom(S, pos_initial_cicle);

        bool has_best_edge = best_edge_to_blossom.first != -1 && best_edge_to_blossom.second != -1;
        if (has_best_edge) {
            for(int i = 0; i < S.size(); ++i) {
                if (S[i].second == best_edge_to_blossom.second) {
                    S.erase(S.begin() + i);
                }
            }

            S.push_back(best_edge_to_blossom);
        }
    }
}

int main(void){
int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int v;cin>>v;
        V.push_back(v);
    }

    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int x,y, w; cin>>x>>y>>w;
        E.push_back({x,y});
        W.push_back(w);
    }

    vector<pair<int,int>> w_indexed; 
    for (int i = 0; i < W.size(); ++i) {
        E_to_W[E[i]] = W[i];
        w_indexed.push_back({W[i], i});
    }

    sort(w_indexed.begin(), w_indexed.end());

    // A ordered by weight
    for (auto w_index : w_indexed){
        E_to_I[E[w_index.second]] = w_index.second;
        A.push_back(E[w_index.second]);
    }

    chu_liu_edmonds();

    cout<<"MST:\n";
    for (auto s : S) {
        cout<<s.first<<' '<<s.second<<" ("<<W[E_to_I[s]]<<')'<<endl;
    }
    
    return 0;
}
