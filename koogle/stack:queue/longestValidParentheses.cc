32. Longest Valid Parentheses    

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Example 1:
Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"

Example 2:
Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"

考虑当验证一个括号组时（见20题Valid Parentheses），使用一个栈来检查当前输入是否可能合法。这里的不同之处在于在一个合法子串之前栈内已经有一些东西了，以及只有左括号被push进栈。每次退栈时，如果栈空，则从开始到当前位置为一个合法串，否则，从栈顶元素以后到当前位置为合法串。所以这里我们压入左括号的位置，当出现右括号但栈为空时，我们把“栈底”元素对应的位置更新为当前右括号位置。


int longestValidParentheses(string s) {
	stack<int> st; 
	int bottom = -1;   // bottom 是记录valid substring之前那个index位置, 所以i - bottom不用再加1    
	int res = 0; 

	for (int i = 0; i < s.size(); ++i) {             
		if (s[i] == '(') {                   
			st.push(i);          
		} else {             
			if (st.empty()) 
				bottom = i; 
			else {
				st.pop(); 
				if (st.empty()) {
					// res = max(res, i);   // wrong, 注意st.empty()时要减bottom  
					res = max(res, i - bottom);   
				} else {
					res = max(res, i - st.top()); 
				}
			}
		}
	}

	return res; 
}

