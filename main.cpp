#include <future>

#include <gtest/gtest.h>


TEST(PackagedTask, ObjectFunctor) {
   
    struct Functor {
        int *_instance_count{nullptr};
        Functor(int* instance_count) : _instance_count(instance_count) {
            ++*_instance_count;
        }
        ~Functor() {
            if(_instance_count) {
                --*_instance_count;
            }
        }
        Functor(const Functor&) = delete;
        Functor& operator=(const Functor&) = delete;
        Functor(Functor&& o) noexcept : _instance_count(o._instance_count) {
            o._instance_count = nullptr;
        }
        Functor& operator=(Functor&& o) {
            if (this != &o) {
                
                _instance_count = o._instance_count;
                o._instance_count = nullptr;
            }
            return *this;
        }
        void operator()() const {
            // This is a simple functor that does nothing.
        }
    };
    int instance_count = 0;

    {
        std::future<void> result;
        {
            std::packaged_task<void()> task(Functor{&instance_count});
            EXPECT_EQ(instance_count, 1) << "Packaged task should own an instance of Functor";
            result = task.get_future();
            task();
            EXPECT_EQ(instance_count, 1) << "Packaged task should keep the Functor instance after its execution";

        }
        EXPECT_EQ(instance_count, 0) << "Packaged task should destroy the Functor instance after its destruction";

        result.get();
        EXPECT_EQ(instance_count, 0) << "future should not keep the Functor instance alive after its execution";
    }
    EXPECT_EQ(instance_count, 0) << "future should not keep the Functor instance alive after its destruction";
}