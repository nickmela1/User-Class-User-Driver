#include <iostream>

class User
{
   public:
   std::string _firstName;
   std::string _lastName;
   std::string _age;
   std::string _gender;
   std::string _height;
   std::string _weight;
        
   User(std::string _firstName, std::string _lastName, std::string _age, std::string _gender, std::string _height, std::string _weight)
   {
      this->_firstName = _firstName;
      this->_lastName = _lastName;
      this->_age = _age;
      this->_gender = _gender;
      this->_height = _height;
      this->_weight = _weight;
   }

   User()
   {
      _firstName = "null";
      _lastName = "null";
      _age = "null";
      _gender = "null";
      _height = "null";
      _weight = "null";
   }
   
   std::string firstName()
   {
      return _firstName;         
   }
   
   std::string lastName()
   {
      return _lastName;
   }
   
   std::string age()
   {
      return _age;
   }
   
   std::string gender()
   {
      if (_gender == "m" || _gender == "M")
      {
         _gender = "Male";
      }
      if (_gender == "f" || _gender == "F")
      {
         _gender = "Female";
      } 
      return _gender;  
   }
   
   std::string height()
   {
      return _height;
   }
   
   std::string weight()
   {
      return _weight;
   }

   std::string easyPrintName()
   {
      return _firstName + " " + _lastName;
   }
   
   std::string easyPrintFull()
   {
      return _firstName + " - " + _lastName + " - " + _age + " - " + gender() + " - " + _height + " - " + _weight;
   }
};