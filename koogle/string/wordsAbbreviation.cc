Word Abbreviation 单词缩写  

Given an array of n distinct non-empty strings, you need to generate minimal possible abbreviations for every word following rules below.

Begin with the first character and then the number of characters abbreviated, which followed by the last character.
If there are any conflict, that is more than one words share the same abbreviation, a longer prefix is used instead of only the first character until making the map from word to abbreviation become unique. In other words, a final abbreviation cannot map to more than one original words.
If the abbreviation doesnt make the word shorter, then keep it as original.
Example:

Input: ["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"]
Output: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]

这道题让我们求单词的缩写形式，就是首尾字母加上中间字符的个数组成的新字符串，但是要求是不能有重复的缩写字符串，而且说明如果缩写字符串的长度并没有减小的话就保留原来的字符串，比如god，缩写成g1d也没啥用，所以仍是god。博主刚开始在研究题目中给的例子的时候有些疑惑，虽然知道internal和interval的缩写形式都是i6l，会冲突，博主刚开始不明白的是，为什么不能一个是i6l，一个是in5l，这样不就不冲突了么，而题目中的缩写形式居然都是原字符串。后来才搞清楚题目原来是说只要有冲突的都不能用，而internal和interval是典型的死杠上的一对，i6l，in5l，int4l，inte3l，inter2l，统统冲突，而再往后的缩写长度就和原字符串一样了，所以二者就都保留了原样。理解了题意就好办了，由于每个单词的缩写形式中数字前面的字母个数不一定相同，所以我们用一个pre数组来记录每个单词缩写形式开头字母的长度，初始化都为1，然后先求出所有单词pre为1的缩写形式，再来进行冲突处理。我们遍历每一个缩写字符串，进行while循环，新建一个集合set，然后遍历其他所有字符串，所有发现冲突字符串，就把冲突字符串的坐标存入集合中，如果没有冲突，那么集合为空，直接break掉，如果由冲突，那么还要把当前遍历的位置i加入结合中，然后遍历集合中所有的位置，对其调用缩写函数，此时pre对应的值自增1，直到没有冲突存在为止


vector<string> wordsAbbreviation(vector<string>& A) {
    int N = A.size();
    vector<string> res;
    for (string& s : A) res.push_back(abbreviate(s, 1)); // abbreviate each string
    vector<int> pre(N, 1); // current explicit prefix length

    for (int i = 0; i < N; i++) {
        // check conflicts for every string
        while (true) {
            set<int> dup;
            for (int j = i+1; j < N; j++) if (res[i] == res[j]) dup.insert(j);
            if (dup.empty()) break;
            dup.insert(i);
            for (int k: dup) res[k] = abbreviate(A[k], ++pre[k]); // increase the prefix
        }
    }
    return res;
}

// k = prefix length
// E.g. f(hello, 3) = hello; f(hello, 2) = he2o; f(hello, 1) = h3o
string abbreviate(string s, int k) {
    return (k >= s.size()-2) ? s : s.substr(0, k) + to_string(s.size()-k-1) + s.back();
}



