class Solution {
public:
    string convert(string s, int numRows) {
        if(s.size() < 2) return s;
        string res;
        int length = s.size();
        int groupSize = 2 * numRows - 2;
        int nGroup = ceil(length / (float)groupSize);
        int left = 0, right = groupSize;
        while(left <= right){
            for(int g=0; g<length; g+=groupSize){
                if(left >= 0 && right < groupSize && g+left >= 0 && g+left < length){
                    res.push_back(s[g+left]);
                }
                if(right == left){
                    continue;
                }
                if(right >= 0 && right < groupSize && g+right >= 0 && g+right < length){
                    res.push_back(s[g+right]);
                }
            }
            left++;
            right--;
        }
        return res;
    }
};