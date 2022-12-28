#include <iostream> 
#include <string>
#include <windows.h>
#include <fstream>

using namespace std;

int sum_weight;
int incidence_matrix[50][50];

struct edge {
	int A;
	int B;
	int W;
};

struct graph {
	struct edge amount_edg[1023];
	int edge_id;
};

struct graph tree_graph;
struct graph output;

void edges_union(int tree[], int frst_node, int scnd_node, int sub_graph) {
	for (int i = 0; i < sub_graph; i = i + 1) {
		if (tree[i] == scnd_node) {
			tree[i] = frst_node;
		}
	}
}

void print_graph() {
	int tree_value = 0;
	for (int i = 0; i < output.edge_id; i = i + 1) {
		char output_from = (output.amount_edg[i].A + 65);
		char output_to = (output.amount_edg[i].B + 65);
		cout << output_to << " - " << output_from << " " << endl;
		tree_value = tree_value + output.amount_edg[i].W;
	}
	cout <<"Tree weight: "<< tree_value << endl;
}

void sorting() {
	struct edge sort_edges;
	for (int i = 1; i < tree_graph.edge_id; i = i + 1) {
		for (int j = 0; j < tree_graph.edge_id - 1; j = j + 1) {
			if (tree_graph.amount_edg[j].W > tree_graph.amount_edg[j + 1].W) {
				sort_edges = tree_graph.amount_edg[j];
				tree_graph.amount_edg[j] = tree_graph.amount_edg[j + 1];
				tree_graph.amount_edg[j + 1] = sort_edges;
			}
		}
	}
}
int tree_edge(int tree[], int tree_node) {
	return(tree[tree_node]);
}

void main_algorithm(int** graph_algorithm, int sub_graph) {
	int id_root[1023];
	int id_first;
	int id_second;
	tree_graph.edge_id = 0;
	for (int i = 1; i < sub_graph; i = i + 1) {
		for (int j = 0; j < i; j = j + 1) {
			if (!(graph_algorithm[i][j] == 0)) {
				tree_graph.amount_edg[tree_graph.edge_id].A = i;
				tree_graph.amount_edg[tree_graph.edge_id].B = j;
				tree_graph.amount_edg[tree_graph.edge_id].W = graph_algorithm[i][j];
				tree_graph.edge_id = tree_graph.edge_id + 1;
			}
		}
		sorting();
		for (int i = 0; i < sub_graph; i = i + 1) {
			id_root[i] = i;
		}
		output.edge_id = 0;
		for (int i = 0; i < tree_graph.edge_id; i = i + 1) {
			id_first = tree_edge(id_root, tree_graph.amount_edg[i].A);
			id_second = tree_edge(id_root, tree_graph.amount_edg[i].B);
			if (!(id_first == id_second)) {
				output.amount_edg[output.edge_id] = tree_graph.amount_edg[i];
				output.edge_id = output.edge_id + 1;
				edges_union(id_root, id_first, id_second, sub_graph);
			}
		}
	}
	print_graph();
}

int main() {
	string path = "input_data.txt";
	int tree_weight;
	char A_ch;
	char B_ch;
	int W_input = 0;
	int max_jk = 0;
	for (int i = 0; i < 50; i = i + 1) {
		for (int j = 0; j < 50; j = j + 1) {
			incidence_matrix[i][j] = 0;
		}
	}
	ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		cout << "Error. " << endl;
	}
	else {
		while (fin >> A_ch >> B_ch >> W_input) {
			int id_fr = int(A_ch) - 65;
			int id_to = int(B_ch) - 65;
			int id_we = W_input;
			if (max_jk < id_fr) {
				max_jk = id_fr;
			}
			if (max_jk < id_to) {
				max_jk = id_to;
			}
			incidence_matrix[id_fr][id_to] = id_we;
			incidence_matrix[id_to][id_fr] = id_we;
		}
		max_jk++;
		int** inc_matrix_new_graph = new int* [max_jk];
		for (int i = 0; i <= max_jk; i++) {
			inc_matrix_new_graph[i] = new int[max_jk];
		}
		for (int i = 0; i <= max_jk; i++) {
			for (int j = 0; j <= max_jk; j++) {
				inc_matrix_new_graph[i][j] = incidence_matrix[i][j];
			}
		}
		main_algorithm(inc_matrix_new_graph, max_jk);
	}
	fin.close();
	return 0;
}