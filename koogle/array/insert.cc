57. Insert Interval  

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

另一个更清晰的解释是搜索区间中第一个和最后一个与新区间相交的区间。将它们之前和之后的区间直接加入结果。相交的两个区间分别更新被merge区间的开始和结束位置。  

vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
	int l, r;
    for (l = 0; l < intervals.size() && intervals[l].end < newInterval.start; ++l);
    for (r = intervals.size()-1; r >= 0 && intervals[r].start > newInterval.end; r--);
    
    if (l < intervals.size() && intervals[l].start< newInterval.end) 
        newInterval.start = min(newInterval.start, intervals[l].start);
    if (r >=0 && intervals[r].end > newInterval.start)
        newInterval.end = max(newInterval.end, intervals[r].end);
    
    vector<Interval> result;
    result.insert(result.end(), intervals.begin(), intervals.begin()+l);
    result.push_back(newInterval);
    result.insert(result.end(), intervals.begin()+r+1, intervals.end());
    return result;
}


