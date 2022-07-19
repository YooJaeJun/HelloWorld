#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int ans = 0;

struct node {
	int parent;
	vector<int> childs;
};

struct tree : public node {
	int root;
	vector<node> nodes;
	vector<bool> visited; 
	
	void dfs(int start) {
		visited[start] = true;
		if (nodes[start].parent >= -1 && 
			nodes[start].childs.size() == 0) {
			ans++;
		}
		else {
			for (auto& child : nodes[start].childs) {
				if (visited[child] == false) {
					dfs(child);
				}
			}
		}
	}
};

int main() {
	int t;
	cin >> t;
	tree tr;
	tr.nodes.resize(t);
	tr.visited.resize(t);
	for (int child = 0; child != t; child++) {
		int parent;
		cin >> parent;
		if (parent == -1) {
			tr.root = child;
		}
		else {
			tr.nodes[child].parent = parent;
			tr.nodes[parent].childs.push_back(child);
		}
	}

	int delete_node;
	cin >> delete_node;

	// �ڽ� ��ũ ����
	tr.nodes[delete_node].childs.clear();
	// �θ��� �ڽ� ��ũ ����
	int parent = tr.nodes[delete_node].parent;
	vector<int> childs = tr.nodes[parent].childs;
	for (int i = 0; i < childs.size(); i++) {
		if (childs[i] == delete_node) {
			tr.nodes[parent].childs.erase(tr.nodes[parent].childs.begin() + i);
		}
	}
	// �θ� ��ũ ����
	tr.nodes[delete_node].parent = -2;	// �����Ͱ� �ƴ϶� �� ��ȿȭ

	tr.dfs(tr.root);
	cout << ans;
	return 0;
}