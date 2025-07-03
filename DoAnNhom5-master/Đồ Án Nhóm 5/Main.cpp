#include "floydWarshall.h"
#include "JohnsonAlgorithm.h"
#include "measureExecutionTime.h"
#include "generateRandomGraph.h"

using namespace std;

// Hàm menu chính để người dùng tương tác
void menu(JohnsonAlgorithm& johnson, floydWarshall& floyd) {
	bool check1 = false, check2 = false; // kiểm tra trước khi chạy thuật toán Johnson và floyd-warshall thì đã nhập dữ liệu chưa.
	while (true) {
		system("cls");
		// In menu lựa chọn
		cout << " ----------------------------- Menu ----------------------------- " << endl;
		cout << "1. Enter data for Johnson algorithm" << endl;
		cout << "2. Enter data for Floyd-Warshall algorithm" << endl;
		cout << "3. Run Johnson algorithm" << endl;
		cout << "4. Run Floyd-Warshall algorithm" << endl;
		cout << "5. Generate and run Johnson and Floyd-Warshall on a random graph" << endl;
		cout << "6. Display memory usage of Johnson and Floyd-Warshall algorithms" << endl;
		cout << "7. Exit" << endl;
		cout << " ---------------------------------------------------------------- " << endl;
		int choice;
		cout << "Enter your choice: "; cin >> choice;

		// Nhập dữ liệu cho thuật toán Johnson
		if (choice == 1) {
			while (true) {
				system("cls");
				cout << " ----------- Menu ----------- " << endl;
				cout << "1. Input data from keyboard" << endl;
				cout << "2. Input data from file" << endl;
				cout << "3. Exit" << endl;
				cout << " ---------------------------- " << endl;
				int subChoice;
				cout << "Enter your choice: "; cin >> subChoice;

				if (subChoice == 1) {
					// Nhập tay
					int V, E;
					cout << "+ Number of vertices: "; cin >> V;
					cout << "+ Number of edges: ";    cin >> E;
					johnson = JohnsonAlgorithm(V);
					for (int i = 0; i < E; i++) {
						int u, v, w;
						cout << "-------- Edge_" << (i + 1) << " --------" << endl;
						cout << "Start vertex: "; cin >> u;
						cout << "End vertex: ";   cin >> v;
						cout << "Weight: ";       cin >> w;
						johnson.addEdge(u, v, w);
					}
					check1 = true; // đánh dấu đã nhập dữ liệu xong 
					cout << "Johnson data entry complete\n";
					system("pause");
				}
				else if (subChoice == 2) {
					// Nhập từ file
					int V, E;
					ifstream inFile("Data.txt");
					if (inFile.is_open()) {
						inFile >> V >> E;
						johnson = JohnsonAlgorithm(V);
						for (int i = 0; i < E; i++) {
							int u, v, w;
							inFile >> u >> v >> w;
							johnson.addEdge(u, v, w);
						}
						check1 = true; // đánh dấu đã nhập dữ liệu xong 
						cout << "Data successfully loaded from file!" << endl;
					}
					else {
						cout << "Failed to open file!" << endl;
					}
					inFile.close();
					system("pause");
				}
				else break;
			}
		}

		// Nhập dữ liệu cho thuật toán Floyd-Warshall
		else if (choice == 2) {
			while (true) {
				system("cls");
				cout << " ----------- Menu ----------- " << endl;
				cout << "1. Input data from keyboard" << endl;
				cout << "2. Input data from file" << endl;
				cout << "3. Exit" << endl;
				cout << " ---------------------------- " << endl;
				int subChoice;
				cout << "Enter your choice: "; cin >> subChoice;

				if (subChoice == 1) {
					int V, E;
					cout << "+ Number of vertices: "; cin >> V;
					cout << "+ Number of edges: ";    cin >> E;
					floyd = floydWarshall(V);
					for (int i = 0; i < E; i++) {
						int u, v, w;
						cout << "-------- Edge_" << (i + 1) << " --------" << endl;
						cout << "Start vertex: "; cin >> u;
						cout << "End vertex: ";   cin >> v;
						cout << "Weight: ";       cin >> w;
						floyd.addEdge(u, v, w);
					}
					check2 = true; // đánh dấu đã nhập dữ liệu xong 
					cout << "floydWarshall data entry complete\n";
					system("pause");
				}
				else if (subChoice == 2) {
					int V, E;
					ifstream inFile("Data.txt");
					if (inFile.is_open()) {
						inFile >> V >> E;
						floyd = floydWarshall(V);
						for (int i = 0; i < E; i++) {
							int u, v, w;
							inFile >> u >> v >> w;
							floyd.addEdge(u, v, w);
						}
						check2 = true; // đánh dấu đã nhập dữ liệu xong 
						cout << "Data successfully loaded from file!" << endl;
					}
					else {
						cout << "Failed to open file!" << endl;
					}
					inFile.close();
					system("pause");
				}
				else break;
			}
		}

		// Chạy Johnson
		else if (choice == 3) {
			if (!check1) {
				cout << "Please choose option 1 to enter items first." << endl;
				system("pause");
				continue;
			}
			int subChoice;
			cout << "Would you like to print all shortest paths?" << endl;
			cout << " --------------------------- " << endl;
			cout << "1. Yes, print all paths." << endl;
			cout << "0. No, skip printing." << endl;
			cout << " --------------------------- " << endl;
			cout << "Your choice: ";
			cin >> subChoice;
			johnson.show = subChoice;

			johnson.reset(); // reset dữ liệu trước khi chạy lại nếu cần
			// Đo thời gian thực thi
			double time = measureExecutionTime(&JohnsonAlgorithm::Johnson, &johnson);
			cout << "\nExecution time of Johnson's Algorithm: " << time << " ms" << endl;
			system("pause");
		}

		// Chạy Floyd-Warshall
		else if (choice == 4) {
			if (!check2) {
				cout << "Please choose option 2 to enter items first." << endl;
				system("pause");
				continue;
			}
			int subChoice;
			cout << "Would you like to print all shortest paths?" << endl;
			cout << " --------------------------- " << endl;
			cout << "1. Yes, print all paths." << endl;
			cout << "0. No, skip printing." << endl;
			cout << " --------------------------- " << endl;
			cout << "Your choice: ";
			cin >> subChoice;
			floyd.show = subChoice;

			double time = measureExecutionTime(&floydWarshall::FloydWarshall, &floyd);
			cout << "\nExecution time of Floyd-Warshall Algorithm: " << time << " ms" << endl;
			system("pause");
		}

		// Sinh đồ thị ngẫu nhiên và chạy cả 2 thuật toán
		else if (choice == 5) {
			cout << "Choose graph type:\n";
			cout << " ----------------- " << endl;
			cout << "1. Sparse graph\n";
			cout << "2. Dense graph\n";
			cout << " ----------------- " << endl;
			cout << "Enter your choice: ";
			int typeChoice; cin >> typeChoice;

			if (typeChoice != 1 && typeChoice != 2) {
				cout << "Invalid choice. Returning to previous menu.\n";
				system("pause");
				break;
			}

			int V;
			cout << "Number of vertices: "; cin >> V;

			bool isDense = (typeChoice == 2);
			auto edges = generateRandomGraph(V, isDense); // Sinh đồ thị

			// Gán lại thuật toán với đồ thị mới
			johnson = JohnsonAlgorithm(V);
			floyd = floydWarshall(V);
			for (const auto& edge : edges) {
				int u = get<0>(edge);
				int v = get<1>(edge);
				int w = get<2>(edge);
				johnson.addEdge(u, v, w);
				floyd.addEdge(u, v, w);
			}
			cout << "Johnson and Floyd - Warshall data entry complete\n";

			// Hỏi có in đường đi không
			int subChoice;
			cout << "\nWould you like to print all shortest paths?" << endl;
			cout << " --------------------------- " << endl;
			cout << "1. Yes, print all paths." << endl;
			cout << "0. No, skip printing." << endl;
			cout << " --------------------------- " << endl;
			cin >> subChoice;
			johnson.show = subChoice;
			floyd.show = subChoice;

			johnson.reset(); // reset dữ liệu trước khi chạy lại nếu cần

			double timeJohnson = measureExecutionTime(&JohnsonAlgorithm::Johnson, &johnson);
			double timeFloyd = measureExecutionTime(&floydWarshall::FloydWarshall, &floyd);
			cout << "\nExecution time of Johnson's Algorithm: " << timeJohnson << " ms" << endl;
			cout << "Execution time of Floyd-Warshall Algorithm: " << timeFloyd << " ms" << endl;
			system("pause");
		}

		// Hiển thị bộ nhớ sử dụng
		else if (choice == 6) {
			cout << "Memory usage of Johnson's Algorithm: " << johnson.memory() << " bytes" << endl;
			cout << "Memory usage of Floyd-Warshall Algorithm: " << floyd.memory() << " bytes" << endl;
			system("pause");
		}

		// Thoát chương trình
		else {
			break;
		}
	}
}

int main() {
	// Khởi tạo thuật toán rỗng ban đầu
	JohnsonAlgorithm johnson(0);
	floydWarshall floyd(0);
	menu(johnson, floyd); // Gọi menu
	return 0;
}
