//
//  rmq.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/06/10.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment37 rmq - final home work

#include <fstream>
using namespace std;

const int MAX = 1000001;
ifstream inp("rmq.inp");
ofstream out("rmq.out");

int arr[MAX], tree[MAX * 4];

int init(int idx, int s, int e) {
    if(s == e) return tree[idx] = s;

    int mid = (s + e) / 2;
    int left = init(idx * 2 + 1, s, mid);
    int right = init(idx * 2 + 2, mid + 1, e);

    return tree[idx] = arr[left] > arr[right] ? right : left;;
}

int update(int idx, int start, int end, int node) {
    if(node < start || node > end) return tree[idx];
    if(start != end) {
        int mid = (start + end) / 2;
        int left = update(idx * 2 + 1, start, mid, node);
        int right = update(idx * 2 + 2, mid + 1, end, node);
        tree[idx] = arr[left] > arr[right] ? right : left;
    }
    return tree[idx];
}

int query(int idx, int s, int e, int l, int r) {
    if(r < s || e < l) return -1;
    if(l <= s && r >= e) return tree[idx];
    
    int mid = (s + e) / 2;
    int left = query(idx * 2 + 1, s, mid, l, r);
    int right = query(idx * 2 + 2, mid + 1, e, l, r);

    if(left == -1) return right;
    if(right == -1) return left;

    return arr[left] > arr[right] ? right : left;
    
}

int main() {
    ios_base::sync_with_stdio(false); inp.tie(NULL); out.tie(NULL);
    int n, ans = 0;
    inp >> n;
    for(int i = 0; i < n; i++) inp >> arr[i];
    init(0, 0, n - 1);

    while(true) {
        char q;
        int a, b;
        inp >> q >> a >> b;
        if(q == 's') break;
        else if(q == 'q') {
            ans += query(0, 0, n - 1, a, b);
            ans %= 100000;
        }
        else {
            arr[a] = b;
            update(0, 0, n - 1, a);
        }
    }
    out << ans % 100000 << "\n";
    inp.close(); out.close();
    return 0;
}
