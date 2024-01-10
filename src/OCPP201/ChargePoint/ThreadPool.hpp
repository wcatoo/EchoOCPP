#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
  ThreadPool(size_t);
  template<class F, class... Args>
    requires std::invocable<F, Args...>
  auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;

  ~ThreadPool();

private:
  std::vector<std::thread> workers; // C++20 jthread is an RAII thread
  std::queue<std::packaged_task<void()>> tasks;
  std::mutex queue_mutex;
  std::condition_variable condition;
  bool stop = false;
};

inline ThreadPool::ThreadPool(size_t threads)
    : stop(false)
{
  for (size_t i = 0; i < threads; ++i)
    workers.emplace_back([this] {
      std::thread::id threadId = std::this_thread::get_id();
      std::cout << "Thread ID: " << threadId  << " -> " << std::endl;
      for (;;)
      {
        std::packaged_task<void()> task;

        {
          std::unique_lock<std::mutex> lock(this->queue_mutex);
          this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
          if (this->stop && this->tasks.empty())
            return;
          task = std::move(this->tasks.front());
          this->tasks.pop();
        }

        task();
      }
    });
}

template<class F, class... Args>
  requires std::invocable<F, Args...>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
{
  using return_type = std::invoke_result_t<F, Args...>;

  auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

  std::future<return_type> res = task->get_future();
  {
    std::unique_lock<std::mutex> lock(queue_mutex);

    if (stop)
      throw std::runtime_error("enqueue on stopped ThreadPool");

    tasks.emplace([task]() { (*task)(); });
  }
  condition.notify_one();
  return res;
}

inline ThreadPool::~ThreadPool()
{
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;
  }
  condition.notify_all();
  for(std::thread &worker: workers)
    worker.join();
}

#endif
