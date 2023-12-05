#include <ostream>
#include <vector>

class Person
{
public:
  Person() = default;
  ~Person() = default;

  Person& SetName(const char* aName) { mName = aName; return *this; }
  Person& SetAge(const short aAge) { mAge = aAge; return *this; }
  Person& SetBirthMonth(const short aBirthMonth) { mBirthDate.mBirthMonth = aBirthMonth; return *this; }
  Person& SetBirthDay(const short aBirthDay) { mBirthDate.mBirthDay = aBirthDay; return *this; }
  Person& SetBirthYear(const short aBirthYear) { mBirthDate.mBirthYear = aBirthYear; return *this; }
  Person& SetOccupation(const char* aOccupation) { mOccupation = aOccupation; return *this; }
  Person& AddHobby(const char* aHobby) { mHobbies.push_back(aHobby); return *this; }

private:
  friend std::ostream &operator<<(std::ostream &, const Person &);

  const char* mName{"No Name"};
  short mAge{-1};
  struct BirthDate
  {
    short mBirthMonth{-1};
    short mBirthDay{-1};
    short mBirthYear{-1};
  } mBirthDate;
  const char* mOccupation{"No Occupation"};
  std::vector<const char*> mHobbies{};
};

inline std::ostream &operator<<(std::ostream &os, const Person &p)
{
  os << "Name: " << p.mName << "\nAge: "
     << p.mAge << "\nBirth Date: " << p.mBirthDate.mBirthMonth
     << "/" << p.mBirthDate.mBirthDay << "/" << p.mBirthDate.mBirthYear
     << "\nOccupation: " << p.mOccupation << "\nHobbies: ";

  for (int i = 0; i < p.mHobbies.size(); ++i)
  {
    const auto &hobby = p.mHobbies[i];
    os << hobby;
    if (i != p.mHobbies.size() - 1)
    {
      os << ", ";
      if (i == p.mHobbies.size() - 2) {
        os << "and ";
      }
    }
  }

  return os;
}