#include <cstring>
#include <iostream>
#include <memory>
#include <queue>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

class TinyJson {
public:
  enum ParseResult {
    OK,
    EXPECT_VALUE,
    INVALID_VALUE,
    ROOT_NOT_SINGULAR,
    NUMBER_TOO_BIG,
    INVALID_CHARACTER_ESCAPE, // 无效字符转义
    INVALID_CHARACTER,        // [0x0, 0x20) 无效字符
    QUOTATION_MISMATCH,       // 字符串中的"不匹配
    INVALID_UNICODE_HEX,
    INVALID_UNICODE_SURROGATE,
    ARRAY_MISS_COMMA_OR_SQUARE_BRACKET, // 数组缺少,或者缺少]
    OBJECT_MISS_COMMA_OR_CURLY_BRACKET, // object缺少,或者}
    OBJECT_MISS_KEY,                    // object缺少key
    OBJECT_MISS_COLON                   // 缺少:
  };
  enum JsonType {
    JSON_NULL,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
  };
  struct KVnode;
  struct JsonValue;
  /* 这里没有选择使用Node直接析构, 而是包装在JsonValue中让JsonValue进行析构,
   * 仅仅是为了避免递归析构, 不知道是否有其他方案... */
  struct Node {
    Node() : type{JsonType::JSON_NULL} {}
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;
    Node &operator=(Node &&rhs) {
      switch (rhs.type) {
      case JsonType::JSON_NULL:
        this->type = JsonType::JSON_NULL;
        break;
      case JsonType::JSON_TRUE:
        this->type = JsonType::JSON_TRUE;
        break;
      case JsonType::JSON_FALSE:
        this->type = JsonType::JSON_FALSE;
        break;
      case JsonType::JSON_NUMBER:
        this->type = JsonType::JSON_NUMBER;
        this->number = rhs.number;
        break;
      case JsonType::JSON_STRING:
        this->type = JsonType::JSON_STRING;
        this->str = rhs.str;
        this->strLen = rhs.strLen;
        rhs.type = JsonType::JSON_NULL;
        rhs.str = nullptr;
        rhs.strLen = 0;
        break;
      case JsonType::JSON_ARRAY:
        this->type = JsonType::JSON_ARRAY;
        this->arr = rhs.arr;
        this->arrLen = rhs.arrLen;
        rhs.type = JsonType::JSON_NULL;
        rhs.arr = nullptr;
        rhs.arrLen = 0;
        break;
      case JsonType::JSON_OBJECT:
        this->type = JsonType::JSON_OBJECT;
        this->object = rhs.object;
        this->objSize = rhs.objSize;
        rhs.type = JsonType::JSON_NULL;
        rhs.object = nullptr;
        rhs.objSize = 0;
        break;
      }
      return *this;
    }
    Node(Node &&rhs) {
      switch (rhs.type) {
      case JsonType::JSON_NULL:
        this->type = JsonType::JSON_NULL;
        break;
      case JsonType::JSON_TRUE:
        this->type = JsonType::JSON_TRUE;
        break;
      case JsonType::JSON_FALSE:
        this->type = JsonType::JSON_FALSE;
        break;
      case JsonType::JSON_NUMBER:
        this->type = JsonType::JSON_NUMBER;
        this->number = rhs.number;
        break;
      case JsonType::JSON_STRING:
        this->type = JsonType::JSON_STRING;
        this->str = rhs.str;
        this->strLen = rhs.strLen;
        rhs.type = JsonType::JSON_NULL;
        rhs.str = nullptr;
        rhs.strLen = 0;
        break;
      case JsonType::JSON_ARRAY:
        this->type = JsonType::JSON_ARRAY;
        this->arr = rhs.arr;
        this->arrLen = rhs.arrLen;
        rhs.type = JsonType::JSON_NULL;
        rhs.arr = nullptr;
        rhs.arrLen = 0;
        break;
      case JsonType::JSON_OBJECT:
        this->type = JsonType::JSON_OBJECT;
        this->object = rhs.object;
        this->objSize = rhs.objSize;
        rhs.type = JsonType::JSON_NULL;
        rhs.object = nullptr;
        rhs.objSize = 0;
        break;
      }
    }
    JsonType type;
    union {
      double number;
      struct {
        char *str;
        size_t strLen; // for string
      };
      struct {
        Node **arr;
        size_t arrLen; // for array
      };

      struct {
        KVnode *object;
        size_t objSize; // for object
      };
    };

    // setStr仅限于修改root且root.type == string的情况
    void setStr(const char *s, size_t sLen) {
      // 存在空字符串的情况(即sLen = 0), 比如json的字符串为"", 这也是合法的,
      // 即使长度为0, 也不需要显示if
      // https://stackoverflow.com/questions/3751797/can-i-call-memcpy-and-memmove-with-number-of-bytes-set-to-zero
      // 这个JsonValue是否允许重复使用呢?
      if (sLen == 0) [[unlikely]] {
        type = JsonType::JSON_STRING;
        str = nullptr;
        strLen = 0;
      } else {
        char *ret = static_cast<char *>(::malloc(sLen));
        if (ret == nullptr) [[unlikely]] {
          std::abort(); // 未处理malloc返回nullptr的情况...
        }
        type = JsonType::JSON_STRING;
        str = ret;
        strLen = sLen;
        ::memcpy(str, s, sLen);
      }
    }
    // 如果是string_view的getStr接口, 那么我们无法修改key
    std::string_view getStr() { return std::string_view(str, strLen); }
  };
  struct KVnode {
    char *str;
    size_t strLen; // for key
    Node *v;
    KVnode() : str{nullptr}, strLen{0}, v{} {}
  };
  struct JsonValue {
    Node *root;
    // 是否应该此时分配内存?
    JsonValue() : root{static_cast<Node *>(::malloc(sizeof(Node)))} {
      ::new (root) Node();
    }
    JsonValue(Node *v) : root{v} {}
    JsonValue(const JsonValue &) = delete;
    JsonValue(JsonValue &&) = delete;
    JsonValue &operator=(const JsonValue &) = delete;
    JsonValue &operator=(JsonValue &&) = delete;
    ~JsonValue() {
      if (root == nullptr)
        return;
      std::queue<Node *> que;
      que.push(root);
      root = nullptr; // 将根节点设置为nullptr
      while (!que.empty()) {
        Node *tmp = que.front();
        que.pop();
        switch (tmp->type) {
        case JsonType::JSON_STRING:
          ::free(tmp->str);
          ::free(tmp);
          break;
        case JsonType::JSON_ARRAY:
          for (size_t i = 0; i < tmp->arrLen; ++i) {
            que.push(tmp->arr[i]);
          }
          ::free(tmp->arr);
          ::free(tmp);
          break;
        case JsonType::JSON_OBJECT:
          for (size_t i = 0; i < tmp->objSize; ++i) {
            ::free(tmp->object[i].str);
            que.push(tmp->object[i].v);
          }
          ::free(tmp->object);
          ::free(tmp);
          break;
        default:
          ::free(tmp);
          break;
        }
      }
    }
    // double getNumber() { return number; }
  };
  ParseResult parse(JsonValue *);
  TinyJson(std::string_view sv) : visitedPos(sv) {
    inStack = std::make_unique<InternalStack>();
  }
  TinyJson(const TinyJson &) = delete;
  TinyJson &operator=(const TinyJson &) = delete;
  TinyJson &operator=(TinyJson &&rhs) {
    visitedPos = rhs.visitedPos;
    inStack = std::move(rhs.inStack);
    return *this;
  }
  std::span<char> stringify(JsonValue *); // 使用者负责释放内存
  std::string stringify2(JsonValue *);

private:
  // 记录状态
  std::string_view visitedPos;
  // todo use cpp template
  // todo: 封装一下变量
  struct InternalStack {
    // https://stackoverflow.com/questions/11781724/do-i-really-have-to-worry-about-alignment-when-using-placement-new-operator
    char *ptr;        // 内部栈开始的地方
    size_t size, top; // top第一个可用字节

    inline static std::size_t STACK_INIT_SIZE = 256; // 默认栈大小256字节
    void *push(size_t);
    void *pop(size_t);
    void reset() { top = 0; }
    // 栈初始化时为256字节
    InternalStack()
        : ptr{(char *)malloc(STACK_INIT_SIZE)}, size{STACK_INIT_SIZE}, top{} {}
    ~InternalStack() {
      if (ptr != nullptr) {
        free(ptr);
      }
    }
  };
  std::unique_ptr<InternalStack> inStack;
  void parse_whitespace();         // 解析空格
  ParseResult parse_value(Node *); // 根据首字符判断将要解析成的对象
  ParseResult
  parse_literal(Node *, std::string_view,
                JsonType); // 解析null/true/false, 结果保存至JsonValue
  ParseResult parse_number(Node *); // 解析数字
  ParseResult parse_string(Node *); // 解析string
  ParseResult parse_string_raw(char *&,
                               std::size_t &); // string's的开始指针+长度
  bool parse_hex4(unsigned *);     // 解析Unicode的辅助函数: 解析\uxxxx
  void encode_utf8(unsigned);      // 对utf8编码
  ParseResult parse_array(Node *); // 解析数组
  ParseResult parse_object(Node *); // 解析object

  // stringify
  void stringify_value(InternalStack &, Node *);
  void stringify_string(InternalStack &, std::string_view);

  void stringify_value(std::string &, Node *);
  void stringify_string(std::string &, std::string_view);
};
