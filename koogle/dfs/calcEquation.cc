
399. Evaluate Division  

Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:                            
Given a / b = 2.0, b / c = 3.0.                 
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .        
return [6.0, 0.5, -1.0, 1.0, -1.0 ].            

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:                             
                                            
equations = [ ["a", "b"], ["b", "c"] ],                     
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 


DS:     unordered_map<string, unordered_map<string, double>> g;    
        unordered_set<string> visited;            

Alg:    DFS  
        A / B = (C / B) * (A / C) 


vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
    // g[A][B] = k -> A / B = k
    unordered_map<string, unordered_map<string, double>> g;        
    for (int i = 0; i < equations.size(); ++i) {    
        string A = equations[i].first;           
        string B = equations[i].second;             
        double k = values[i];                
        g[A][B] = k;
        g[B][A] = 1.0 / k;
    }
    
    vector<double> ans;

    for (auto pair : queries) {
        string X = pair.first;
        string Y = pair.second;
        if (!g.count(X) || !g.count(Y)) {
            ans.push_back(-1.0);              
            continue;
        }

        unordered_set<string> visited;            
        ans.push_back(divide(X, Y, g, visited));
    }

    return ans;
}



// get result of A / B
double divide(string& A, string& B, unordered_map<string, unordered_map<string, double>> g, unordered_set<string>& visited) {        
    if (A == B) return 1.0;
    visited.insert(A);

    for (auto pair : g[A]) {        
        string C = pair.first;      
        if (visited.count(C))       
            continue;               
        
        double d = divide(C, B, g, visited); // d = C / B
        // A / B = (C / B) * (A / C) 
        if (d > 0) return d * g[A][C];
    }        
    return -1.0;
}




