#pragma once
#include "Standard_Library.h"

using namespace std;

class JohnsonAlgorithm {
private:

	struct Edge {
		int start, end, weight;
	};

	int V;
	vector<vector<pair<int, int>>> adjList;
	vector<Edge> edges;
	vector<long long> potential;

public:
	int show = 0;  // Lựa chọn có hiện thị kết quả ra hay không, giá trị mặc định là không

	// Constructor: Khởi tạo số đỉnh và cấu trúc dữ liệu
	JohnsonAlgorithm(int vertex);

	void reset();

	// Thêm một cạnh vào danh sách cạnh
	void addEdge(int start, int end, int weight);

	// Bước 1: Thêm đỉnh phụ V vào đồ thị, nối với tất cả các đỉnh khác bằng cạnh trọng số 0
	void addAuxiliaryVertex();

	// Bước 2: Chạy Bellman-Ford từ đỉnh phụ để tính potential (hàm h(u))
	// Nếu tồn tại chu trình âm → trả về false
	bool BellmanFord();

	// Bước 3: Reweight các cạnh theo công thức w'(u,v) = w(u,v) + h(u) - h(v)
	void reweightEdges();

	// Tạo danh sách kề từ danh sách cạnh (sau khi đã reweight)
	void AdjacencyList();

	// Dijkstra: Tìm đường đi ngắn nhất từ 1 đỉnh đến các đỉnh khác
	void Dijkstra(int src);

	// In kết quả đường đi từ src
	void print(int src, vector<int>& parent, vector<long long>& disc); 

	// Thuật toán Johnson chính: kết hợp tất cả bước
	void Johnson();

	// Hàm đo bộ nhớ sử dụng
	int memory();
};