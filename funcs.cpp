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

void analyzeV(const std::vector<int> & v, int & maxDist, int & minDist){
    maxDist = 0;
    minDist = v.back() - v[0];
    for(int i=1;i<v.size();++i){
        int dist =v[i]-v[i-1];
        if(dist>maxDist)
            maxDist = dist;
        if(dist < minDist)
            minDist = dist;
    }
}

void parseFile(std::istream & input, std::ostream & output){
    int n, k;
    input>>n>>k;

    std::vector<int> numbers(n);
    std::copy_n(std::istream_iterator<int>(input),n,numbers.begin());

    std::sort(numbers.begin(), numbers.end());
    int minNumber = numbers[0], maxNumber = numbers.back();
    int minL = 0, maxL = abs(maxNumber-minNumber-1);

    //int minDist, maxDist;
    //analyzeV(numbers,maxDist,minDist);

    auto func=[&k, &numbers]
            (int l){
        return checkPointsCover(l,k,numbers);
    };

    int ans = indexOfFirst(func,minL,maxL);

    output<<ans<<'\n';
}
