#include <bits/stdc++.h>
#define ALL(s) (s).begin(), (s).end()
#define rALL(s) (s).rbegin(), (s).rend()
//#define sz(s) (int)(s).size()
#define x real
#define y imag

using namespace std;

typedef complex<int> point;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const int MAX_INT = 2147483647;
mt19937 rnd(time(0));
struct Node {
	int x;
	int y;
	int min;
	int add;
	int sz;
	Node *l, *r;

	Node(int _x) : x(_x), y(rnd()), min(x), sz(1), add(0) { }
};

int size(Node *t) {
	if (!t) return 0;
	return t->sz;
}
void push(Node *t) {
	if (t->l) {
		t->l->x += t->add;
		t->l->min += t->add;
		t->l->add += t->add;
	}
	if (t->r) {
		t->r->x += t->add;
		t->r->min += t->add;
		t->r->add += t->add;
	}
	t->add = 0;
}
void print(Node *t) {
	if (!t) return;
	push(t);
	print(t->l);
	cout << t->x << " ";
	print(t->r);
}
void update(Node *t) {
	if (!t) return;
	t->min = min({t->x, (t->l ? t->l->min : MAX_INT), (t->r ? t->r->min : MAX_INT)});
	t->sz = 1 + (t->l ? t->l->sz : 0) + (t->r ? t->r->sz : 0);
}
Node* merge(Node *a, Node *b) {
	if (!a) return b;
	if (!b) return a;
	if (a->y > b->y) {
		push(a);
		a->r = merge(a->r, b);
		update(a);
		return a; 
	} else {
		push(b);
		b->l = merge(a, b->l);
		update(b);
		return b;
	}
}
pair<Node*, Node*> split(Node *t, int k) {
	if (!t) return {nullptr, nullptr};
	push(t);
	if (size(t->l) < k) {
		auto p = split(t->r, k - size(t->l) - 1);
		t->r = p.first;
		update(t);
		return {t, p.second};
	} else {
		auto p = split(t->l, k);
		t->l = p.second;
		update(t);
		return {p.first, t};
	}
}
Node* get(Node *t, int k) {
	if (!t) return nullptr;
	push(t);
	if (size(t->l) == k)
		return t;
	else if (size(t->l) < k)
		return get(t->r, k - size(t->l) - 1);
	else
		return get(t->l, k);
}
Node* insert(Node *t, int k, int val) {
	auto p = split(t, k);
	t = merge(p.first, new Node(val));
	t = merge(t, p.second);
	return t;
}
Node* remove(Node *t, int k) {
	auto p = split(t, k + 1);
	auto q = split(p.first, k);
	t = merge(q.first, p.second);
	return t;
}
void add_seg(Node *t, int l, int r, int x) { ///[l; r)
	if (l >= r) return;
	auto p = split(t, r);
	auto q = split(p.first, l);
	q.second->min += x;
	q.second->add += x;
	q.second->x += x;
	t = merge(q.first, q.second);
	t = merge(t, p.second);
}
int get_min(Node *t, int l, int r) { ///[l; r)
	if (l >= r) return 0LL;
	auto p = split(t, r);
	auto q = split(p.first, l);
	int min = q.second->min;
	t = merge(q.first, q.second);
	t = merge(t, p.second);
	return min;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	Node *root = nullptr;
	int n;
	cin >> n;
	const int MAX_X = 10;
	for (int i = 0; i < n; i++) {
		root = insert(root, abs(int(rnd())) % (i + 1), abs(int(rnd())) % (MAX_X + 1));
	}
	while (true) {
		char c;
		cin >> c;
		if (c == 'p')
			print(root), cout << endl;
		else if (c == '?') {
			int l, r;
			cin >> l >> r;
			cout << get_min(root, l, r) << endl;
		} else  if (c == '+') {
			int l, r, x;
			cin >> l >> r >> x;
			add_seg(root, l, r, x);
		}
	}
}
