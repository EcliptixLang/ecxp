#ifdef STD_CONSOLE
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

using Values::FunctionCallback;
#include <atomic>

namespace Console {
    namespace Async {
        std::mutex queue_mutex;
        std::condition_variable queue_cv;
        std::queue<std::string> log_queue;
        std::atomic<bool> running{true};
        std::thread worker_thread;

        void worker() {
            while(true) {
                std::unique_lock lock(queue_mutex);
                queue_cv.wait(lock, []{ return !log_queue.empty() || !running; });
                
                if(!running && log_queue.empty()) break;

                while(!log_queue.empty()) {
                    std::cout << log_queue.front();
                    log_queue.pop();
                }
            }
        }

        void log(const std::string& message) {
            std::lock_guard guard(queue_mutex);
            log_queue.push(message);
            queue_cv.notify_one();
        }

        void start() {
            worker_thread = std::thread(worker);
        }

        void stop() {
            running = false;
            queue_cv.notify_all();
            if(worker_thread.joinable()) {
                worker_thread.join();
            }
        }
    };

    std::unique_ptr<Values::Runtime> out(FunctionCallback* callback) {
        std::ostringstream buffer;
        for(auto& arg : callback->parsedArgs) {
            buffer << arg->stringValue();
        }
        buffer << '\n';
        
        Async::log(buffer.str());
        return createNull();
    }

    void cleanup() {
        Async::stop();
    }
};
#endif