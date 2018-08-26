865. Shortest Path to Get All Keys

We are given a 2-dimensional grid. "." is an empty cell, "#" is a wall,"@" is the starting point, ("a","b", …) are keys, and ("A", "B", …) are locks.
We start at the starting point, and one move consists of walking one space in one of the 4 cardinal directions. We cannot walk outside the grid, or walk into a wall. If we walk over a key, we pick it up. We can’t walk over a lock unless we have the corresponding key.
For some 1 <= K <= 6, there is exactly one lowercase and one uppercase letter of the first K letters of the English alphabet in the grid. This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.
Return the lowest number of moves to acquire all keys. If it’s impossible, return -1.

Example 1:
Input: ["@.a.#","###.#","b.A.B"]
Output: 8


Time complexity: O(m*n*64)
Space complexity: O(m*n*64)

  int shortestPathAllKeys(vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].size();    
    int all_keys = 0;
    queue<int> q;
    vector<vector<vector<int>>> seen(m, vector<vector<int>>(n, vector<int>(64, 0)));
        
    // Init
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j) {
        const char c = grid[i][j];
        if (c == '@') {
          q.push((j << 16) | (i << 8));
          seen[i][j][0] = 1;
        } else if (c >= 'a' && c <= 'f') {
          all_keys |= (1 << (c - 'a'));
        }
      }
    
    const vector<int> dirs{-1, 0, 1, 0, -1};
    
    int steps = 0;
    while (!q.empty()) {
      int size = q.size();
      while (size--) {
        int s = q.front(); q.pop();
        int x = s >> 16;
        int y = (s >> 8) & 0xFF;
        int keys = s & 0xFF;        
        if (keys == all_keys) return steps;
        for (int i = 0; i < 4; ++i) {
          int nkeys = keys;
          int nx = x + dirs[i];
          int ny = y + dirs[i + 1];          
          if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
          const char c = grid[ny][nx];          
          if (c == '#') continue; // Wall
          // Do not have the key.
          if (c >= 'A' && c <= 'F' && !(keys & (1 << (c - 'A')))) continue;
          // Update the keys we have.
          if (c >= 'a' && c <= 'f') nkeys |= (1 << (c - 'a'));
          if (seen[ny][nx][nkeys]) continue;
          q.push((nx << 16) | (ny << 8) | nkeys);
          seen[ny][nx][nkeys] = 1;
        }
      }
      ++steps;
    }
    return -1;
  }








