#include <vector>
#include <queue>
#include <iostream>

using namespace std;

typedef pair<int, int> pii; // weight, to

class graph{
public:
    vector<vector<pii>> vecList;
    bool undirected = false;

    graph(int V, bool undirected=false){
        vecList.resize(V);
        this->undirected = undirected;
    }
    void minSpanning(){
        vector<int> parent(vecList.size(), -1);
        vector<int> key(vecList.size(), 0x3f3f3f3f);
        vector<bool> inQ(vecList.size(), true);

        priority_queue<pii, vector<pii>, greater<pii>> pq;

        pq.push(make_pair(0, 0));

        while(!pq.empty()){
            pii u = pq.top(); pq.pop();
            if(inQ[u.second]==true){
                inQ[u.second]= false;
                for(auto vE: vecList[u.second]){
                    int v = vE.second;
                    int wUV = vE.first;
                    if(inQ[v] && wUV < key[v]){
                        parent[v] = u.second;
                        key[v] = wUV;
                        pq.push(make_pair(key[v], v));
                    }
                }
            }
        }
        cout << "parent: ";
        for(int i=0; i<vecList.size(); i++){
            cout << parent[i] << " ";
        } cout <<endl;
    }
    void dfs_rec(int u, vector<int> &S, vector<int> &found){
        found[u] = 1;
        for (auto vE : vecList[u]){
            int v = vE.second;
            if (found[v] == 0)
                dfs_rec(v, S, found);
        }
        S.push_back(u);
    }
    void Topological_Sort(){
        vector<int> S;
        vector<int> found(vecList.size(), 0);
        vector<int> cont;

        for(int i=0; i<vecList.size(); i++){
            if (found[i]==0)
                dfs_rec(i, S, found);
        }
        while(!S.empty()){
            int u = S.back(); S.pop_back();
            cout << u << " ";
        } cout <<endl;
    }
    
    vector<pii> DFS(int source){
        vector<int> found(vecList.size(), 0);
        vector<int> S;
        vector<int> parent(vecList.size(), -1);
        vector<pii> timestamp(vecList.size());

        int time = 0;

        found[source] = 1;
        
        S.push_back(source);
        while(!S.empty()){
            int u = S.back(); S.pop_back();
            timestamp[u].first = time++;
            for(auto vE: vecList[u]){
                int v = vE.second;
                if(found[v]==0){
                    S.push_back(v);
                    found[v] = 1;
                    parent[v] = u;
                }
            }
            timestamp[u].second = time++;
        }
        return timestamp;
    }
    vector<int> BFS(int source){
        vector<int> found(vecList.size(), 0);
        vector<int> dist(vecList.size(), 0x3f3f3f3f);
        vector<int> parent(vecList.size(), -1);

        dist[source] = 0;
        found[source] = 1;

        queue<int> Q;
        Q.push(source);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(auto vE: vecList[u]){
                int v = vE.second;
                if(found[v]==0){
                    found[v]=1;
                    dist[v] = dist[u]+1;
                    parent[v] = u;
                    Q.push(v);
                }
            }
        }
        return dist;
    }

    vector<int> dijkstra(int source, int target){
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        vector<int> dist(vecList.size(), 0x3f3f3f3f);
        
        pq.push(make_pair(0, source));
        dist[source] = 0;
        
        while(!pq.empty()){
            int u = pq.top().second; pq.pop();

            for (auto it = vecList[u].begin(); it!=vecList[u].end(); it++){
                int v = it->second;
                int weight = it->first;

                if(dist[v] >dist[u]+weight){
                    dist[v] = dist[u]+weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        return dist;
    }
    void print_dijkstra(int source){
        vector<int> temp;

        temp = dijkstra(0, 1);

        cout << "dist: ";
        for(auto it = temp.begin(); it !=temp.end();it++){
            cout << *it << " ";
        }   cout<<endl;
    }
    void addEdge(int src, int trg, int weight){
        vecList[src].push_back(make_pair(weight, trg));
        if(undirected){
            vecList[trg].push_back(make_pair(weight, src));
        }
    }
};