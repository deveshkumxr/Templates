#include <bits/stdc++.h>
using namespace std;

__int128 gcd(__int128 a, __int128 b, __int128 &x, __int128 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    __int128 x1, y1;
    __int128 d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(__int128 a, __int128 b, __int128 c, __int128 &x0, __int128 &y0, __int128 &g) {
    g = gcd(a > 0 ? a : -a, b > 0 ? b : -b, x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution(__int128 &x, __int128 &y, __int128 a, __int128 b, __int128 cnt) {
    x += cnt * b;
    y -= cnt * a;
}

__int128 find_all_solutions(__int128 a, __int128 b, __int128 c, __int128 minx, __int128 maxx, __int128 miny, __int128 maxy) {
    __int128 x, y, g;
    if (!find_any_solution(a, b, c, x, y, g)) return 0;
    a /= g;
    b /= g;

    __int128 sign_a = a > 0 ? +1 : -1;
    __int128 sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx) shift_solution(x, y, a, b, sign_b);
    if (x > maxx) return 0;
    __int128 lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx) shift_solution(x, y, a, b, -sign_b);
    __int128 rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny) shift_solution(x, y, a, b, -sign_a);
    if (y > maxy) return 0;
    __int128 lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy) shift_solution(x, y, a, b, sign_a);
    __int128 rx2 = x;

    if (lx2 > rx2) swap(lx2, rx2);
    __int128 lx = max(lx1, lx2);
    __int128 rx = min(rx1, rx2);

    if (lx > rx) return 0;
    return (rx - lx) / (b > 0 ? b : -b) + 1;
}