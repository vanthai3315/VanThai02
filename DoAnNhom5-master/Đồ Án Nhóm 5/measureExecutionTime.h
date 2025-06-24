#pragma once
#include "Standard_Library.h"

// Hàm đo thời gian thực thi (tính bằng mili giây)
// Func: hàm cần đo thời gian, Args: các tham số truyền vào hàm đó
template <typename Func, typename... Args>
double measureExecutionTime(Func&& func, Args&&... args)
{
    // Ghi lại thời điểm bắt đầu
    auto start = std::chrono::high_resolution_clock::now();

    // Gọi hàm với các đối số được truyền vào
    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

    // Ghi lại thời điểm kết thúc
    auto end = std::chrono::high_resolution_clock::now();

    // Tính khoảng thời gian thực thi (microseconds → milliseconds)
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return duration.count() / 1000.0; // Trả về thời gian thực thi (ms)
}

