#ifndef TASK
#define TASK

#include <ThreadSafeQueue.h>

#include <thread>
#include <future>
#include <iostream>
#include <sstream>

template<class T>
class Task {

private:
    int m_id;

    std::thread m_thread;
    /** Synch the process with the main thread and propagate exceptions **/
    std::future<void> m_future;
    std::promise<void> m_promise;

    /** Transform function **/
    const std::function<T(T&)> m_task;

    using queue_type = thread_safe_queue<T>;

    /** Input container of objects to be processed **/
    queue_type& m_input;

    /** Flag which allows to stop the processing **/
    std::atomic<bool> m_stop;

    /** Output container of transformed objects **/
    std::unique_ptr<queue_type> m_output;

    /** Keeps track of objects processed **/
    int m_count;

private:
    
    void logger( const std::string message, const T& obj) {
        std::ostringstream out;
        out << "Task '" << m_id << " -> " << message << " '" << obj << "'\n";
        std::cout << out.str();
    }

    /**
     * Dequeues objects from input container
     * Calls to transform function
     * Enqueues objects in output container
    */
    void run() {

        try {
            while(!m_stop.load() && m_count > 0) {

                std::shared_ptr<T> obj_ptr = m_input.wait_and_pop();
                if (obj_ptr == nullptr) {
                    continue;
                }

                auto& obj_input = *(obj_ptr.get());
                logger("input", obj_input);

                // transform obj and copy it on output
                auto obj_output = m_task(obj_input);
                logger("output", obj_output);
                m_output->push(obj_output);

                m_count--;
            }
            m_promise.set_value();
        }
        catch (...) {
            m_promise.set_exception(std::current_exception());
        }
    }

public:

    Task(const int id, const std::function<T(T&)> task, queue_type& input) : 
        m_id(id),
        m_task(task),
        m_input(input), 
        m_stop(false),
        m_count(0)
    {
        m_output = std::make_unique<queue_type>(m_stop);
    }

    Task(const Task&) = delete;
    Task& operator= (const Task&) = delete;

    Task(Task&& other) = delete;
    Task& operator= (Task&& other) = delete;

    ~Task() { 
        join(); 
    }

    /**
     * Waits until thread execution is finished
    */
    void join() {

        if (m_future.valid()) {
            m_future.get();
        }

        if (m_thread.joinable()) {
            m_thread.join();
        }
    }


    /**
     * Stops execution
    */
    void stop() {
        m_stop.store(true);
    }


    /**
     * Launches thread execution
     * @param count number of objects to be processed
    */
    void start(int count) {
        m_count = count;
        m_future = m_promise.get_future();
        m_thread = std::thread(&Task::run, this);
    }

    /**
     * Returns queue of processed objects
     * @return m_output
    */
    queue_type& output() {
        return *m_output;
    }

};

#endif