818. Race Car  

Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.) Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse). When you get an instruction "A", your car does the following: position += speed, speed *= 2.When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.) For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1. Now for some target position, say the length of the shortest sequence of instructions to get there.

Example 1:
Input: 
target = 3
Output: 2
Explanation: 
The shortest instruction sequence is "AA".
Your position goes from 0->1->3.


// BFS 剪枝 ; time complexity: 2^D    
// Running time: 221 ms  
int racecar(int target) {    

	queue<pair<int, int>> q;
	q.push({0, 1});
	unordered_set<string> v;
	v.insert("0_1");
	v.insert("0_-1"); // 剪枝, 可有可无   
	int steps = 0;

	while (!q.empty()) {                 
		  int size = q.size();      
		  while (size--) {                      
			    auto p = q.front(); q.pop();      
			    int pos = p.first;              
			    int speed = p.second;         
			    {   // 加速                
			      int pos1 = pos + speed;            
			      int speed1 = speed * 2;         
			      pair<int, int> p1{pos1, speed1};        
			      if (pos1 == target) return steps + 1;              
			      if (p1.first > 0 && p1.first < 2 * target)  // 剪枝, 可有可无 
			        q.push(p1);
			    }
			    { // 减速 
			      int speed2 = speed > 0 ? -1 : 1;
			      pair<int, int> p2{pos, speed2}; 
			      string key2 = to_string(pos) + "_" + to_string(speed2);
			      if (!v.count(key2)) {
			        q.push(p2);
			        v.insert(key2);
			      }
		    }
		  }
		  ++steps;
	}
	return -1;
}
