#include <iostream>

class User
{
   public:
   std::string _firstName;
   std::string _lastName;
   int _age;
   int _height;
   int _weight;
   std::string _gender;   
      
   User(std::string firstName, std::string lastName, int age, std::string gender, int height, int weight)
   {
      this->firstName = firstName;
      this->lastName = lastName;
      this->age = age;
      this->height = height;
      this->weight = weight;
      this->gender = gender;
   }
   
   User()
   {
      firstName = "null";
      lastName = "null";
      age = 0;
      height = 0;
      weight = 0;
      gender = "null";
   }
   
   std::string firstName()
   {
      return firstName;         
   }
   
   std::string lastName()
   {
      return lastName;
   }
   int age()
   {
      return age;
   }
   
   std::string gender()
   {
      if (gender == "m" || gender == "M")
      {
         gender = "Male";
      }
      else if (gender == "f" || gender == "F")
      {
         gender = "Female";
      }
      else
      {
      
      }    
      return gender;  
   }
   
   int height()
   {
      return height;
   }
   
   int weight()
   {
      return weight;
   }
   
   std::string easyPrintName()
   {
      return firstName + " " + lastName;
   }
   
   std::string easyPrintFull()
   {
      return firstName + " - " + lastName + " - " + age + " - " + gender + " - " + height + " - " + weight;
   }
};

main()
{
   User user("nick", "mela", 24, "m", 69, 200);
   std::cout << user.firstName();
}