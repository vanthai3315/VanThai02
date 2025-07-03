#include "JohnsonAlgorithm.h"

// Constructor: Khởi tạo số đỉnh và cấu trúc dữ liệu
JohnsonAlgorithm::JohnsonAlgorithm(int vertex) : V(vertex) {
    adjList.resize(V + 1);                    // Danh sách kề (dùng cho Dijkstra)
    potential.resize(V + 1, LLONG_MAX);         // Mảng potential để lưu kết quả từ Bellman-Ford
}


void JohnsonAlgorithm::reset() {
    edges.clear();                                  // Xoá danh sách cạnh
    adjList.assign(V + 1, {});                      // Xoá danh sách kề
    fill(potential.begin(), potential.end(), LLONG_MAX); // Reset mảng tiềm năng
}
// Thêm một cạnh vào danh sách cạnh
void JohnsonAlgorithm::addEdge(int start, int end, int weight) {
    edges.push_back(Edge{ start, end, weight });
}

// Bước 1: Thêm đỉnh phụ V vào đồ thị, nối với tất cả các đỉnh khác bằng cạnh trọng số 0
void JohnsonAlgorithm::addAuxiliaryVertex() {
    for (int i = 0; i < V; i++) {
        edges.push_back(Edge{ V, i, 0 });
    }
}

// Bước 2: Chạy Bellman-Ford từ đỉnh phụ để tính potential (hàm h(u))
// Nếu tồn tại chu trình âm → trả về false
bool JohnsonAlgorithm::BellmanFord() {
    potential[V] = 0;  // Đỉnh phụ có trọng số 0
    for (int i = 0; i < V; i++) {
        bool finish = true;
        for (Edge x : edges) {
            int start = x.start, end = x.end, weight = x.weight;
            if (potential[start] < LLONG_MAX && potential[end] > potential[start] + weight) {
                potential[end] = potential[start] + weight;
                finish = false;
            }
        }
        if (finish) break;
    }

    // Kiểm tra chu trình âm
    for (Edge x : edges) {
        int start = x.start, end = x.end, weight = x.weight;
        if (potential[start] < LLONG_MAX && potential[end] > potential[start] + weight) {
            return false;
        }
    }
    return true;
}

// Bước 3: Reweight các cạnh theo công thức w'(u,v) = w(u,v) + h(u) - h(v)
void JohnsonAlgorithm::reweightEdges() {
    for (Edge& x : edges) {
        x.weight = x.weight + potential[x.start] - potential[x.end];
    }
}

// Tạo danh sách kề từ danh sách cạnh (sau khi đã reweight)
void JohnsonAlgorithm::AdjacencyList() {
    for (Edge e : edges) {
        adjList[e.start].push_back({ e.end, e.weight });
    }
}

// Dijkstra: Tìm đường đi ngắn nhất từ 1 đỉnh đến các đỉnh khác
void JohnsonAlgorithm::Dijkstra(int src) {
    priority_queue < pair<long long, int>, vector < pair<long long, int>>, greater<pair<long long, int>>> pq;
    vector<long long> disc(V, LLONG_MAX);  // Distance từ src đến các đỉnh
    vector<int> parent(V, -1);     // Mảng truy vết đường đi
    vector<bool> check(V, false);  // Kiểm tra đỉnh đã duyệt
    disc[src] = 0;
    pq.push({ 0, src });

    while (!pq.empty()) {
        pair<int, int> top = pq.top(); pq.pop();
        int weight = top.first, start = top.second;
        if (check[start]) continue;
        check[start] = true;

        for (pair<int, int> x : adjList[start]) {
            int end = x.first, Weight = x.second;
            if (!check[end] && disc[end] > disc[start] + Weight) {
                disc[end] = disc[start] + Weight;
                parent[end] = start;
                pq.push({ disc[end], end });
            }
        }
    }
    if (show) print(src, parent, disc);
}


// In kết quả đường đi từ src
void JohnsonAlgorithm::print(int src, vector<int>& parent, vector<long long>& disc) {
    cout << "\nShortest paths from vertex " << src << ":\n";
    cout << " Dest | Path                      | Cost\n";
    cout << "-----------------------------------------------\n";

    for (int dest = 0; dest < V; ++dest) {
        if (src == dest) continue;
        cout << setw(5) << dest << " | ";

        if (disc[dest] == LLONG_MAX) {
            cout << setw(25) << "No path" << " | INF\n";
        }
        else {
            // Truy vết đường đi
            vector<int> path;
            for (int v = dest; v != -1; v = parent[v])
                path.push_back(v);
            reverse(path.begin(), path.end());

            ostringstream oss;
            for (size_t i = 0; i < path.size(); ++i) {
                oss << path[i];
                if (i + 1 < path.size()) oss << " -> ";
            }
            cout << setw(25) << oss.str() << " | ";

            // Chuyển lại trọng số ban đầu: disc - h(s) + h(v)
            cout << disc[dest] - potential[src] + potential[dest] << endl;
        }
    }
}

// Thuật toán Johnson chính: kết hợp tất cả bước
void JohnsonAlgorithm::Johnson() {
    addAuxiliaryVertex();      // Thêm đỉnh phụ V
    if (!BellmanFord()) {
        cout << "The graph contains a negative-weight cycle" << endl;
        return;
    }
    reweightEdges();           // Reweight các cạnh
    AdjacencyList();           // Tạo danh sách kề từ cạnh mới
    for (int i = 0; i < V; ++i) {
        Dijkstra(i);     // Chạy Dijkstra từ từng đỉnh
    }
}

// Hàm đo bộ nhớ sử dụng (đơn vị: byte)
int JohnsonAlgorithm::memory()
{
    // Nếu chưa có cạnh nào thì coi như chưa có dữ liệu → trả về 0
    if (edges.empty())
        return 0;

    // Bộ nhớ dùng cho adjList (danh sách kề)
    // Chi phí phần "vỏ" vector (mỗi vector trong danh sách)
    int memory_adjList = adjList.size() * sizeof(vector<pair<int, int>>);

    // Cộng thêm chi phí các phần tử trong từng vector (các cặp <đỉnh, trọng số>)
    for (const auto& neighbors : adjList)
    {
        memory_adjList += neighbors.size() * sizeof(pair<int, int>);
    }

    // Bộ nhớ dùng cho danh sách cạnh
    int memory_edges = edges.size() * sizeof(Edge);

    // Bộ nhớ dùng cho mảng trọng số phụ (potential)
    int memory_potential = potential.size() * sizeof(int);

    // Tổng bộ nhớ
    return memory_adjList + memory_edges + memory_potential;
}
