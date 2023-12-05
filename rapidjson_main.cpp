#include "Person.hpp"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "rapidjson/include/rapidjson/writer.h"

#include <iostream>

static constexpr auto SampleJson = R"({
  "name": "John Doe",
  "age": 26,
  "birthDate": {
    "month": 7,
    "day": 10,
    "year": 1989
  },
  "occupation": "Dog Walker",
  "hobbies": [
    "Gaming",
    "Hiking",
    "Running",
    "Book Reading"
  ]
})";

int main()
{
  rapidjson::Document jsonObject;
  jsonObject.Parse(SampleJson);

  Person p;

  if (jsonObject.IsObject())
  {
    if (const auto name = jsonObject.FindMember("name"); name != jsonObject.MemberEnd() && name->value.IsString())
    {
      p.SetName(name->value.GetString());
    }
    if (jsonObject.HasMember("age"))
    {
      p.SetAge(static_cast<short>(jsonObject["age"].GetInt()));
    }
    if (const auto birthDate = jsonObject.FindMember("birthDate"); birthDate != jsonObject.MemberEnd() && birthDate->value.IsObject())
    {
      const auto &birthDateObj = birthDate->value;
      if (const auto birthMonth = birthDateObj.FindMember("month"); birthMonth != birthDateObj.MemberEnd() && birthMonth->value.IsInt())
      {
        p.SetBirthMonth(static_cast<short>(birthMonth->value.GetInt()));
      }
      if (const auto birthDay = birthDateObj.FindMember("day"); birthDay != birthDateObj.MemberEnd() && birthDay->value.IsInt())
      {
        p.SetBirthDay(static_cast<short>(birthDay->value.GetInt()));
      }
      if (const auto birthYear = birthDateObj.FindMember("year"); birthYear != birthDateObj.MemberEnd() && birthYear->value.IsInt())
      {
        p.SetBirthYear(static_cast<short>(birthYear->value.GetInt()));
      }
    }
    if (const auto occupation = jsonObject.FindMember("occupation"); occupation != jsonObject.MemberEnd() && occupation->value.IsString())
    {
      p.SetOccupation(occupation->value.GetString());
    }
    if (const auto hobbies = jsonObject.FindMember("hobbies"); hobbies != jsonObject.MemberEnd() && hobbies->value.IsArray())
    {
      for (const auto &hobby : hobbies->value.GetArray())
      {
        if (hobby.IsString())
        {
          p.AddHobby(hobby.GetString());
        }
      }
    }
  }

  std::cout << p << "\n";

  rapidjson::StringBuffer buffer;
  rapidjson::Writer writer{buffer};
  jsonObject.Accept(writer);

  std::cout << "\n" << buffer.GetString() << "\n";
}