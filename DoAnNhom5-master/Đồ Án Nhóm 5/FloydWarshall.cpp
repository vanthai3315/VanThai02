#include "FloydWarshall.h"

// Constructor: Khởi tạo ma trận kề với trọng số vô hạn, trừ đường chéo là 0
floydWarshall::floydWarshall(int vertex) : V(vertex) {
    adjMatrix.assign(V, vector<long long>(V, LLONG_MAX));   // Tạo ma trận V x V toàn LLONG_MAX
    for (int i = 0; i < V; i++) {
        adjMatrix[i][i] = 0;                    // Khoảng cách từ i đến i là 0
    }
}

// Thêm cạnh có hướng từ start → end với trọng số weight
void floydWarshall::addEdge(int start, int end, int weight) {
    adjMatrix[start][end] = weight;
}

// Thuật toán Floyd-Warshall: tìm đường đi ngắn nhất giữa mọi cặp đỉnh
void floydWarshall::FloydWarshall() {
    // Ba vòng lặp: duyệt qua đỉnh trung gian k, điểm xuất phát i và điểm kết thúc j
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            if (adjMatrix[i][k] == LLONG_MAX) continue; // Không cần xét nếu không đi từ i đến k
            for (int j = 0; j < V; j++) {
                if (adjMatrix[k][j] == LLONG_MAX) continue; // Không cần xét nếu không đi từ k đến j

                // Cập nhật khoảng cách nếu đi qua k ngắn hơn
                adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
            }
        }
    }
    if (show) {
        // In ma trận khoảng cách kết quả
        cout << "\nAll pairs shortest paths (Floyd–Warshall):\n";
        printMatrix(adjMatrix);
    }
}

// Hàm hỗ trợ: In ma trận khoảng cách ra màn hình
void floydWarshall::printMatrix(const vector<vector<long long>>& dist) {
    // In hàng tiêu đề (các đỉnh đích)
    cout << setw(6) << "";
    for (int j = 0; j < V; j++)
        cout << setw(6) << j;
    cout << "\n" << string(7 + 6 * V, '-') << "\n";

    // In từng hàng (từng đỉnh xuất phát)
    for (int i = 0; i < V; i++) {
        cout << setw(6) << i << "|";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == LLONG_MAX)
                cout << setw(6) << "INF";
            else
                cout << setw(6) << dist[i][j];
        }
        cout << "\n";
    }
}

// Hàm đo bộ nhớ sử dụng (đơn vị: byte)
int floydWarshall::memory()
{
    // Nếu ma trận trống → coi như chưa có dữ liệu → trả về 0
    if (adjMatrix.empty() || adjMatrix[0].empty())
        return 0;

    // Bộ nhớ dùng cho adjMatrix (ma trận kề dạng vector 2 chiều)
    // Chi phí phần "vỏ" vector hàng (vector<int> cho từng hàng)
    int memory_matrix = adjMatrix.size() * sizeof(vector<int>);

    // Cộng thêm chi phí cho từng phần tử bên trong (các int trong từng hàng)
    for (const auto& row : adjMatrix)
    {
        memory_matrix += row.size() * sizeof(long long);
    }

    // Trả về tổng bộ nhớ đã tính
    return memory_matrix;
}
