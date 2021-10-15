//https://contest.yandex.ru/contest/29188/problems/

#include "funcs.h"
#include <bits/stdc++.h>

/*! @brief First argument, that returns true for given func
 *
 * @tparam Func function pointer, lambda, on given vector should have
 * that form: "___---"
 * @param func function pointer, lambda, that should accept int as input
 * @param left Left limit
 * @param right Right limit
 * @param tol Tolerance
 * @return value
 */
template<typename Func>
int indexOfFirst(Func func, int left, int right){
    while (left<right){
        int middle = (left+right)/2;
        if(func(middle)){
            right = middle;
        } else {
            left = middle+1;
        }
    }
    return left;
}

bool checkPointsCover(int l, int k, const std::vector<int> & v){
    int i = 0, iMax = v.size()-1;
    while (k>0){
        int endPos = v[i]+l;
        i = indexOfFirst([&endPos, &v](int j){
            return v[j]>endPos;
            },i,iMax);
        if(i>=iMax){
            if(v[iMax]<=endPos)
                return true;
        }
        --k;
    }
    return false;
}

std::vector<int> getDistances(const std::vector<int> &v){
    std::vector<int> ans(v.size()-1);
    int iMax = v.size()-1;
    for (int i = 0; i < iMax; ++i) {
        ans[i] = v[i+1]-v[i];
    }
    std::sort(ans.begin(),ans.end(),std::greater<>());
    return ans;
}

std::pair<int,int> getRange(const std::vector<int> &v, int n, int k){
    int minNumber = v[0], maxNumber = v.back();
    int minL = 0, maxL = abs(maxNumber-minNumber);

    if(k>=n){
        return {0,0};
    }

    if(k==1){
        return {maxL, maxL};
    }

    std::vector<int> distances = getDistances(v);//n-1 len, descending order

    minL = distances[distances.size()-k];

    int iMax = k-1;
    for(int i = 1; i<iMax; ++i){
        maxL-=distances[i-1];
    }

    minL = fmin(minL,maxL);
    return {minL,maxL};
}

void parseFile(std::istream & input, std::ostream & output){
    int n, k;
    input>>n>>k;

    std::vector<int> numbers(n);
    std::copy_n(std::istream_iterator<int>(input),n,numbers.begin());

    std::sort(numbers.begin(), numbers.end());

    auto func=[&k, &numbers]
            (int l){
        return checkPointsCover(l,k,numbers);
    };
    std::pair<int,int> range = getRange(numbers,n,k);
    int ans = indexOfFirst(func, range.first, range.second);

    output<<ans<<'\n';
}
