#include <conditional>
#include <mutex>
#include <optional>
#include <queue>

template <typename T>
class BufferWithMutex {
 public:
  Buffer(size_t capacity) : capacity_{capacity} {}

  bool Add(const T &val) {
    const std::lock_guard<std::mutex> lock(data_mutex_);
    if (data_.size() < capacity_) {
      data_.push(val);
      return true;
    }
    return false;
  }

  std::optional<T> Pop() {
    std::lock_guard<std::mutex> lock(data_mutex_);
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
class BufferWithConditional {
 public:
  Buffer(size_t capacity) : capacity_{capacity} {}

  bool Add(const T &val) {
    const std::lock_guard<std::mutex> lock(data_mutex_);
    if (data_.size() < capacity_) {
      data_.push(val);
      return true;
    }
    return false;
  }

  std::optional<T> Pop() {
    std::lock_guard<std::mutex> lock(data_mutex_);
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
