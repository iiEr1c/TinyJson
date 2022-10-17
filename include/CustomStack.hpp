
#include <cassert>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

class CustomStack {
private:
  static inline size_t InitStackSize = 16; // 初始1024字节
  static inline size_t alignment = 8;
  // 默认情况下8字节对齐, 如果需要保存的对象存在更大的对齐要求则另外设置
  // todo: 修改成类似variant那样的stack? 已知要使用该栈的所有对象,
  // 然后对所有的类型求alignas
  // 这里保证了每次分配内存时, 初始的对齐位置是一样的, 那么当重新分配内存时,
  // 原来的对象所处的内存地址也是对齐的(因为offset相同)

public:
  CustomStack(size_t size = InitStackSize)
      : _base{static_cast<char *>(std::aligned_alloc(alignment, size))},
        _size{size}, _top{} {}
  ~CustomStack() { std::free(_base); }
  size_t top() const { return _top; }
  size_t size() const { return _size; }
  CustomStack(const CustomStack &) = delete;
  CustomStack &operator=(const CustomStack &) = delete;

  // 返回原来的top()和padding大小
  template <typename T> std::pair<size_t, size_t> push(T &&val) {
    size_t padding = PaddingSize<std::decay_t<T>>();
    Shrink(padding + sizeof(std::decay_t<T>));
    ::new (BasePtr() + top() + padding) T(std::forward<T>(val));
    size_t prevTop = top();
    addTop(padding + sizeof(std::decay_t<T>));
    return {prevTop, padding};
  }
  // pop不析构对象, 需要用户自己手动析构, 因为stack不保存类型
  char *pop(size_t len) {
    assert(len <= top());
    subTop(len);
    return BasePtr() + top();
  }

private:
  char *_base;  // 栈基址
  size_t _size; // 容量
  size_t _top;  // 栈顶
  template <typename T> size_t PaddingSize() {
    size_t curTop = reinterpret_cast<size_t>(BasePtr()) + top();
    constexpr size_t align = std::alignment_of_v<std::decay_t<T>>;
    size_t padding = (align - curTop % align) % align;
    return padding;
  }
  char *BasePtr() const { return _base; }
  void addTop(size_t len) { _top += len; }
  void subTop(size_t len) { _top -= len; }
  /* 非线程安全 */
  void Shrink(size_t len) {
    size_t prevSize = top(); // 原来栈中已使用的内存大小
    while (top() + len > size()) {
      _size += _size >> 1; // 每次size变成1.5倍
    }
    char *tmp = static_cast<char *>(std::aligned_alloc(alignment, size()));
    std::memcpy(tmp, _base, prevSize); // 仅支持trivial type
    std::free(_base);
    _base = tmp;
  }
};