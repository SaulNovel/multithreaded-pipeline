#ifndef PIPELINE
#define PIPELINE

#include "Task.h"

#include <vector>

template<class T>
class Pipeline {

private:

    /** Holds input device objects **/
    std::atomic<bool> m_stop;
    using queue_type = thread_safe_queue<T>;
    queue_type m_input;

    /** transform stages **/
    int m_taskCount;
    std::vector<std::unique_ptr<Task<T>>> m_tasks;

    /** Output device function **/
    std::function<void(const T&)> m_output = nullptr;

public:

    Pipeline() : m_stop(false), m_input(m_stop), m_taskCount(0) 
    {}

    Pipeline (const Pipeline&) = delete;
    Pipeline& operator= (const Pipeline&) = delete;
    Pipeline(Pipeline&& other) = delete;
    Pipeline& operator= (Pipeline&& other) = delete;

    ~Pipeline()
    {}

    /** Stages are identified by its function signature **/

    /**
     * Retrieves objects from input device and adds them into a queue
     * @param stage input device function
    */
    void addStage(const std::function<T(void)>& stage) {
        
        auto obj = stage();
        m_input.push(obj);
    }

    /**
     * Adds output device function to the pipeline
     * Only one output device function is supported
     * @param stage output device function 
    */
    void addStage(const std::function<void(const T&)> stage) {

        if (m_output != nullptr) {
            throw std::runtime_error("pipeline only supports one output device");
        }

        m_output = stage;
    }

    /**
     * Creates one instance of Task per transform function
     * @param stage transform stage function
    */
    void addStage(const std::function<T(T&)>& stage) {
        auto& input = m_tasks.empty() ? m_input : m_tasks.back()->output();
        auto task = std::make_unique<Task<T>>(++m_taskCount, stage, input);

        m_tasks.push_back(std::move(task));
    }

    /**
     * Executes process pipeline
    */
    void run() {

        if (m_tasks.empty()) {
            throw std::runtime_error("pipeline is empty");
        }

        /** Amount of objects from input device **/
        int input_size = static_cast<int>(m_input.size());

        /** Transform stages **/
        for (auto& task : m_tasks) {
            task->start(input_size);
        }

        for (auto& task : m_tasks) {
            task->join();
        }

        /** Output device **/
        auto& output = m_tasks.back()->output();
        while (!output.empty()) {
            auto obj_ptr = output.wait_and_pop();
            m_output(*obj_ptr);
        }      
    }

};

#endif