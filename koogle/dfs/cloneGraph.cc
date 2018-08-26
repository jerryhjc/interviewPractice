133. clone graph 

Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

DS:   unordered_map<const UndirectedGraphNode*, UndirectedGraphNode*> copied;


UndirectedGraphNode *cloneGraph(const UndirectedGraphNode *node)  { 

  if(node == nullptr) return nullptr;
  // key is original node,value is copied node
  unordered_map<const UndirectedGraphNode *, UndirectedGraphNode *> copied;

  clone(node, copied);
  
  return copied[node];
}

// DFS
static UndirectedGraphNode* clone(const UndirectedGraphNode *node, unordered_map<const UndirectedGraphNode *, UndirectedGraphNode *> &copied) {
  // a copy already exists
  if (copied.find(node) != copied.end()) 
    return copied[node];
  
  UndirectedGraphNode *new_node = new UndirectedGraphNode(node->label);
  copied[node] = new_node;
  
  for (auto a : node->neighbors)
    new_node->neighbors.push_back(clone(a, copied));
  
  return new_node;   
}


