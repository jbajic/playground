#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

template <typename T>
class BufferWithMutex {
 public:
  BufferWithMutex(const size_t capacity) : capacity_{capacity} {}

  bool Add(const T &val) {
    const std::lock_guard<std::mutex> lock(data_mutex_);
    if (data_.size() < capacity_) {
      data_.push(val);
      return true;
    }
    return false;
  }

  std::optional<T> Pop() {
    const std::lock_guard<std::mutex> lock(data_mutex_);
    if (!data_.empty()) {
      const auto val = data_.front();
      data_.pop();
      return val;
    }
    return std::nullopt;
  }

 private:
  size_t capacity_;
  std::queue<T> data_;
  std::mutex data_mutex_;
};

template <typename T>
class BufferWithCondition {
 public:
  BufferWithCondition(const size_t capacity) : capacity_{capacity} {}

  void Add(const T &val) {
    std::unique_lock<std::mutex> lock(data_mutex_);
    not_full_.wait(lock, [this]() { return data_.size() < capacity_; });

    data_.push(val);
    not_empty_.notify_one();
  }

  T Pop() {
    std::unique_lock<std::mutex> lock(data_mutex_);
    not_empty_.wait(lock, [this]() { return !data_.empty(); });
    const auto val = data_.front();
    data_.pop();
    not_full_.notify_one();
    return val;
  }

 private:
  size_t capacity_;
  std::queue<T> data_;
  std::mutex data_mutex_;
  std::condition_variable not_full_;
  std::condition_variable not_empty_;
};
