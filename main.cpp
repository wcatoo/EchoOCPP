#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// 定义自定义 C++ 类型
struct Person {
  std::string name;
  std::string address;
  int age;

  // 序列化成 JSON
  friend void to_json(json& j, const Person& p) {
    j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
  }

  // 从 JSON 反序列化
  friend void from_json(const json& j, Person& p) {
    j.at("name").get_to(p.name);
    j.at("address").get_to(p.address);
    j.at("age").get_to(p.age);
  }
};

int main() {
  // 创建一个 Person 对象
  Person john{"John Doe", "123 Main St", 30};

  // 将 Person 对象序列化成 JSON
  json jsonPerson = john;

  // 打印生成的 JSON
  std::cout << "Serialized Person:\n" << jsonPerson.dump(4) << std::endl;

  // 从 JSON 反序列化回 Person 对象
  Person newPerson = jsonPerson;

  // 打印反序列化后的 Person 对象
  std::cout << "\nDeserialized Person:\n"
            << "Name: " << newPerson.name << "\n"
            << "Address: " << newPerson.address << "\n"
            << "Age: " << newPerson.age << std::endl;

  return 0;
}
