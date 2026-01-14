/*You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.

Find the minimum y-coordinate value of a horizontal line such that the total area of the squares above the line equals the total area of the squares below the line.

Answers within 10-5 of the actual answer will be accepted.

Note: Squares may overlap. Overlapping areas should be counted multiple times.

 

Example 1:

Input: squares = [[0,0,1],[2,2,1]]

Output: 1.00000

Explanation:



Any horizontal line between y = 1 and y = 2 will have 1 square unit above it and 1 square unit below it. The lowest option is 1.

Example 2:

Input: squares = [[0,0,2],[1,1,1]]

Output: 1.16667

Explanation:



The areas are:

Below the line: 7/6 * 2 (Red) + 1/6 (Blue) = 15/6 = 2.5.
Above the line: 5/6 * 2 (Red) + 5/6 (Blue) = 15/6 = 2.5.
Since the areas above and below the line are equal, the output is 7/6 = 1.16667.

 

Constraints:

1 <= squares.length <= 5 * 104
squares[i] = [xi, yi, li]
squares[i].length == 3
0 <= xi, yi <= 109
1 <= li <= 109
The total area of all the squares will not exceed 1012.*/

double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    typedef long long ll;

    typedef struct {
        ll y, x1, x2;
        int type;
    } Event;

    int maxN = squaresSize * 2;
    Event *events = (Event *)malloc(sizeof(Event) * maxN);
    ll *xs = (ll *)malloc(sizeof(ll) * maxN);

    int eCnt = 0, xCnt = 0;

    for (int i = 0; i < squaresSize; i++) {
        ll x = squares[i][0];
        ll y = squares[i][1];
        ll l = squares[i][2];

        events[eCnt++] = (Event){y, x, x + l, 1};
        events[eCnt++] = (Event){y + l, x, x + l, -1};

        xs[xCnt++] = x;
        xs[xCnt++] = x + l;
    }

    /* sort x-coordinates */
    int cmpLL(const void *a, const void *b) {
        ll x = *(ll *)a, y = *(ll *)b;
        return (x > y) - (x < y);
    }
    qsort(xs, xCnt, sizeof(ll), cmpLL);

    int m = 0;
    for (int i = 0; i < xCnt; i++) {
        if (i == 0 || xs[i] != xs[i - 1])
            xs[m++] = xs[i];
    }

    /* sort events */
    int cmpEvent(const void *a, const void *b) {
        Event *e1 = (Event *)a;
        Event *e2 = (Event *)b;
        if (e1->y != e2->y) return (e1->y > e2->y) - (e1->y < e2->y);
        return e1->type - e2->type;
    }
    qsort(events, eCnt, sizeof(Event), cmpEvent);

    static int cnt[800000];
    static double len[800000];
    memset(cnt, 0, sizeof(cnt));
    memset(len, 0, sizeof(len));

    int lowerBound(ll *arr, int n, ll val) {
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r) / 2;
            if (arr[mid] < val) l = mid + 1;
            else r = mid;
        }
        return l;
    }

    void pushUp(int node, int l, int r) {
        if (cnt[node] > 0)
            len[node] = (double)(xs[r + 1] - xs[l]);
        else if (l == r)
            len[node] = 0;
        else
            len[node] = len[node * 2] + len[node * 2 + 1];
    }

    void update(int node, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) {
            cnt[node] += val;
            pushUp(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        if (ql <= mid) update(node * 2, l, mid, ql, qr, val);
        if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr, val);
        pushUp(node, l, r);
    }

    double totalArea = 0, prevY = events[0].y;

    for (int i = 0; i < eCnt; i++) {
        double y = events[i].y;
        totalArea += len[1] * (y - prevY);

        int l = lowerBound(xs, m, events[i].x1);
        int r = lowerBound(xs, m, events[i].x2) - 1;
        if (l <= r)
            update(1, 0, m - 2, l, r, events[i].type);

        prevY = y;
    }

    double half = totalArea / 2;
    memset(cnt, 0, sizeof(cnt));
    memset(len, 0, sizeof(len));

    double area = 0;
    prevY = events[0].y;

    for (int i = 0; i < eCnt; i++) {
        double y = events[i].y;
        double cur = len[1] * (y - prevY);

        if (area + cur >= half) {
            double ans = prevY + (half - area) / len[1];
            free(events);
            free(xs);
            return ans;
        }

        area += cur;

        int l = lowerBound(xs, m, events[i].x1);
        int r = lowerBound(xs, m, events[i].x2) - 1;
        if (l <= r)
            update(1, 0, m - 2, l, r, events[i].type);

        prevY = y;
    }

    free(events);
    free(xs);
    return prevY;
}
