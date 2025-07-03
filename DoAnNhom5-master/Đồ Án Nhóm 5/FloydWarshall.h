#pragma once
#include "Standard_Library.h"

using namespace std;

class floydWarshall {
private:
	int V;
	vector<vector<long long>> adjMatrix;

public:
	int show = 0; // Lựa chọn có hiện thị kết quả ra hay không, giá trị mặc định là không

	// Constructor: Khởi tạo ma trận kề với trọng số vô hạn, trừ đường chéo là 0
	floydWarshall(int vertex);

	// Thêm cạnh có hướng từ start → end với trọng số weight
	void addEdge(int start, int end, int weight);

	// Thuật toán Floyd-Warshall: tìm đường đi ngắn nhất giữa mọi cặp đỉnh
	void FloydWarshall();

	// Hàm hỗ trợ: In ma trận khoảng cách ra màn hình
	void printMatrix(const vector<vector<long long>>& dist);

	// Hàm đo bộ nhớ sử dụng
	int memory();
};