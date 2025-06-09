#include <memory>
#include <functional>
#include <vector>
#include <shared_mutex>
#include <optional>
#include <any>
#include <iostream>


template<class Value>
class LiveData : public IBaseLiveData
        {
public:
    LiveData() = delete;

    virtual ~LiveData() override = default;

    explicit LiveData(Value value) : m_value(std::move(value)) {}

    virtual Value GetValue() const {
        std::shared_lock<std::shared_mutex> lock(m_valueMutex);
        return m_value;
    }

protected:
    void SetValueInternal(const Value& value, bool force = false) {
        Value* oldValue = nullptr;
        bool updated = false;
        {
            std::unique_lock<std::shared_mutex> lock(m_valueMutex);
            oldValue = &m_value;
            if (force || m_value != value) {
                m_value = value;
                updated = true;
            }
        }

        if (updated && oldValue) {
            NotifyObservers(*oldValue, value);
        }
    }

private:
    Value m_value;
    mutable std::shared_mutex m_valueMutex;
    
    void NotifyObservers(const Value& oldValue, const Value &newValue) {
    
    }
};


class MutexTestData{};

class MutexTest {

public:
    MutexTest() = default; // 默认构造函数

    MutexTest(const std::string& name) : m_name(name) {} // 带参数的构造函数

    void SetName(const std::string& name) {
        std::lock_guard<std::mutex> lock(m_mutex); // 上锁
        m_name = name; // 修改成员变量
    }

    const std::string& GetName() const {
        std::lock_guard<std::mutex> lock(m_mutex); // 上锁
        return m_name; // 返回成员变量的值
    }

    void SetData(MutexTestData data) {
        std::lock_guard<std::mutex> lock(m_mutex); // 上锁
        m_data = std::make_shared<MutexTestData>(std::move(data)); // 修改成员变量
    }

    std::shared_ptr<MutexTestData> GetData() const {
        std::lock_guard<std::mutex> lock(m_mutex); // 上锁
        return m_data;
    }

private:
    mutable std::mutex m_mutex; // 互斥锁，用于线程安全
    std::string m_name;
    std::shared_ptr<MutexTestData> m_data; // 成员变量

};

void Test(const MutexTest& test){
    const std::string& name = test.GetName();
    printf("Name: %s\n", name.c_str()); // 打印成员变量的值
}