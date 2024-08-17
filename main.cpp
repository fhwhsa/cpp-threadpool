#include <iostream>
#include <chrono>
#include <vector>
#include <future>
#include <cassert>
#include "threadpool.cpp"  

// 测试函数，模拟一个耗时任务
int testFunction(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return x * x;
}

// 测试线程池的基本功能
void testThreadPool() {
    ThreadPool& pool = ThreadPool::getInstance();

    // 添加多个任务
    std::vector<std::future<int>> results;
    for (int i = 0; i < 10; ++i) {
        results.emplace_back(pool.enqueue(testFunction, i));
    }

    // 获取任务结果并验证
    for (int i = 0; i < 10; ++i) {
        int result = results[i].get();
        std::cout << "Task " << i << " result: " << result << std::endl;
        assert(result == i * i);
    }

}

int main() {
    testThreadPool();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
