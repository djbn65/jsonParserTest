#include "Person.hpp"
#include "cJSON/cJSON.h"

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
  cJSON* jsonObject = cJSON_Parse(SampleJson);

  Person p;

  if (cJSON_IsObject(jsonObject))
  {
    if (const auto name = cJSON_GetObjectItemCaseSensitive(jsonObject, "name"); cJSON_IsString(name))
    {
      p.SetName(name->valuestring);
    }
    if (const auto age = cJSON_GetObjectItemCaseSensitive(jsonObject, "age"); cJSON_IsNumber(age))
    {
      p.SetAge(static_cast<short>(age->valueint));
    }
    if (const auto birthDate = cJSON_GetObjectItemCaseSensitive(jsonObject, "birthDate"); cJSON_IsObject(birthDate))
    {
      if (const auto birthMonth = cJSON_GetObjectItemCaseSensitive(birthDate, "month"); cJSON_IsNumber(birthMonth))
      {
        p.SetBirthMonth(static_cast<short>(birthMonth->valueint));
      }
      if (const auto birthDay = cJSON_GetObjectItemCaseSensitive(birthDate, "day"); cJSON_IsNumber(birthDay))
      {
        p.SetBirthDay(static_cast<short>(birthDay->valueint));
      }
      if (const auto birthYear = cJSON_GetObjectItemCaseSensitive(birthDate, "year"); cJSON_IsNumber(birthYear))
      {
        p.SetBirthYear(static_cast<short>(birthYear->valueint));
      }
    }
    if (const auto occupation = cJSON_GetObjectItemCaseSensitive(jsonObject, "occupation"); cJSON_IsString(occupation))
    {
      p.SetOccupation(occupation->valuestring);
    }
    if (const auto hobbies = cJSON_GetObjectItemCaseSensitive(jsonObject, "hobbies"); cJSON_IsArray(hobbies))
    {
      cJSON* hobby;
      cJSON_ArrayForEach(hobby, hobbies) {
        if (cJSON_IsString(hobby))
        {
          p.AddHobby(hobby->valuestring);
        }
      }
    }
  }

  std::cout << p << "\n";

  std::cout << "\n" << cJSON_PrintUnformatted(jsonObject) << "\n";

  cJSON_free(jsonObject);
}