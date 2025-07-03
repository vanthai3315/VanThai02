#include "generateRandomGraph.h"

// Hàm sinh đồ thị ngẫu nhiên có hướng, không có cạnh tự nối
// isDense: true nếu muốn đồ thị dày, false nếu đồ thị thưa
vector<tuple<int, int, int>> generateRandomGraph(int V, bool isDense)
{
    vector<tuple<int, int, int>> edges;         // Danh sách cạnh kết quả
    set<pair<int, int>> existingEdges;          // Để kiểm tra cạnh trùng lặp

    int maxEdges = V * (V - 1);                 // Số cạnh tối đa của đồ thị có hướng (không có cạnh tự nối)
    int edgeCount = isDense ? maxEdges * 0.8 : maxEdges * 0.2; // Số lượng cạnh cần sinh, phụ thuộc vào độ dày

    // Thiết lập bộ sinh số ngẫu nhiên
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distV(0, V - 1);  // Sinh đỉnh từ 0 đến V-1
    uniform_int_distribution<> distW(1, 10);     // Sinh trọng số từ 1 đến 10

    // Sinh ngẫu nhiên các cạnh cho đến khi đủ số lượng yêu cầu
    while ((int)edges.size() < edgeCount)
    {
        int u = distV(gen); // đỉnh bắt đầu
        int v = distV(gen); // đỉnh kết thúc

        // Bỏ qua nếu cạnh là tự nối hoặc đã tồn tại
        if (u == v || existingEdges.count({ u, v }))
            continue;

        int w = distW(gen); // trọng số của cạnh
        edges.emplace_back(u, v, w);            // Thêm cạnh vào danh sách
        existingEdges.insert({ u, v });         // Đánh dấu cạnh đã dùng
    }

    return edges; // Trả về danh sách các cạnh
}

