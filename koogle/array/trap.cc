42. Trapping rain water
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

// two pointer
假设数组两边有两道高为lmax, rmax的墙，那么只有当找到一对大于min(lmax, rmax)的墙时，水位才会上升。假设lmax < rmax，则我们从左边scan墙高，直到找到大于lmax的墙。此时水位上升到新的lmax, rmax. （在这个两边向中间夹逼的过程中，水位是不会下降的。）

int trap(vector<int>& height) {
    int amount = 0;
    for (int l = 0, r = height.size()-1, lmax = 0, rmax = 0; l <= r) {
        if (height[l] < height[r]) {
            lmax = max(lmax, height[l]);
            amount += lmax - height[l++];
        }
        else {
            rmax = max(rmax, height[r]);
            amount += rmax- height[r--];
        }
    }
    return amount;
}


