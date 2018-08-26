Text Justification 文本左右对齐
 
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.
You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly Lcharacters.
Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.
For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:

[
   "This    is    an",
   "example  of text",
   "justification.  "
]

string ops + modularization
首先定位本行的第一个单词first和最后一个单词last，总共字母数为nchar，空格数为L-nchar。前t个空格为s+1格，后last - first - t为s格。
如果last为最后一个单词，则s=1，t＝0.否则s = L-nchar/(last-first), t = L-nchar-(last-first)*s.
结束的空格数为L-nchar-(last-first)*s - t.

string transform_line(vector<string>& words, int maxWidth, 
                             int first, int last, int nchar){
    int s = (first == last || last == words.size()-1)? 1 : (maxWidth-nchar)/(last-first);
    int t = (first == last || last == words.size()-1)? 0 : maxWidth-nchar-(last-first)*s;
    int r = maxWidth - nchar - (last-first)*s - t;
    
    string str = words[first];
    for (int k = 1; first+k<= last; ++k) 
        str+= string(k <= t? s+1 : s, ' ') + words[first+k];
    return str + string(r, ' ');
}

vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> result;
    for (int first = 0; first < words.size();) {
        int nchar = 0, last = first;
        while (last < words.size() && nchar+words[last].size()+last-first<= maxWidth)
            nchar += words[last++].size();
        result.push_back(transform_line(words, maxWidth, first, last-1, nchar));
        first = last;
    }
    return result;
}




