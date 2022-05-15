#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#include <atomic>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template<class T>
class thread_safe_queue 
{
private:
    std::queue<std::shared_ptr<T>> m_data;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::atomic<bool>& m_stop;

public:
    thread_safe_queue(std::atomic<bool>& stop) : m_stop(stop)
    {}

    thread_safe_queue(const thread_safe_queue&) = delete;
    thread_safe_queue& operator=(const thread_safe_queue&) = delete;

    size_t size() {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_data.size();
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_data.empty();
    }

    void push(T value) {
        std::shared_ptr<T> data_ptr(std::make_shared<T>(std::move(value)));
        std::lock_guard<std::mutex> lock(m_mutex);
        m_data.push(data_ptr);
        
        m_condition.notify_one();
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m_mutex);

        if(m_data.empty()) {
            throw std::runtime_error("queue is empty");
        }

        std::shared_ptr<T> data_ptr = m_data.front();
        m_data.pop();

        return data_ptr;
    }

    std::shared_ptr<T> wait_and_pop() {

        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this]() {
            return !m_data.empty() || m_stop.load();
        });

        if (m_stop.load()) {
            return nullptr;
        }

        std::shared_ptr<T> data_ptr = m_data.front();
        m_data.pop();

        return data_ptr;
    }
};

#endif