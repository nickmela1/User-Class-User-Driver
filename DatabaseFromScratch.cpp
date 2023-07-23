#include <iostream>
#include <fstream>
#include <vector>
#include "User.h" //Custom type "User", to hold information about a user

User realUser; //Holds information about a User object from the convertToUser() method
std::vector<std::string> fileToUser; //Will hold file contents & update based on user input
std::string inputReference; //Will reference the "input" variable in the stringLetterValidation & stringDigitValidation methods 
int size; //Will hold the size of the fileToUser vector
bool flag; //Will be used many times throughout the program
std::fstream file; //File object

/**
Void method stringLetterValidation() - A method for input validation/making sure no digits make it through
**/

void stringLetterValidation(std::string prompt, int i)
{
   std::string input = ""; //The user input
   flag = false; 
   std::cout << prompt << ": ";
   std::getline(std::cin, input);
   while(!flag && i < input.length() | input.length() == 0)
   {
      flag = false;      
      if(isdigit(input[i]))
      {
         flag = true;
      }
      i++;
   }
   if(flag)
   {
      std::cout <<"\nInvalid entry\n\n";
      stringLetterValidation(prompt, 0);
   }
   else
   {
      inputReference = input;
   }
}

/**
Void method stringDigitValidation() - A method for input validation/making sure no letters make it through
**/

void stringDigitValidation(std::string prompt, int i)
{
   std::string input = ""; //The user input
   flag = false; 
   std::cout << prompt << ": ";
   std::getline(std::cin, input);
   while(!flag && i < input.length() | input.length() == 0)
   {
      flag = false;      
      if(!isdigit(input[i]))
      {
         flag = true;
      }
      i++;
   }
   if(flag)
   {
      std::cout <<"\nInvalid entry\n\n";
      stringDigitValidation(prompt, 0);
   }
   else
   {
      inputReference = input;
   }
}

/**
Void method fillStringArray() - Will constantly update the fileToUser vector with the file contents after each procedure is complete
**/

void fillStringArray()
{
   std::string push = ""; //The push variable will take in the file contents which are then stored in the fileToUser vector
   fileToUser.clear(); //The fileToUser vector is cleared every time this method is called
   file.open("Database.txt", std::ios::in);
   while(file)
   {
      std::getline(file, push);  
      fileToUser.push_back(push);
   }
   size = fileToUser.size();
   file.close();  
}

/**
Void method convertToUser() - Will convert a string from the fileToUser vector into a User object 
@param str - The string to be passed in
**/

void convertToUser(std::string str)
{
   int findDelimiter, i = 0; //The findDelimiter variable holds the position(s) of the chosen delimiter, i is for input validation
   std::string token[6]; //Holds the split string contents from the string 
   std::string delimiter = "-"; //The delimiter
   while(findDelimiter != std::string::npos)
   {
      findDelimiter = str.find(delimiter);      
      token[i] = str.substr(0, findDelimiter);
      str.erase(0, findDelimiter + delimiter.length());
      i++;
   }
   User user(token[0], token[1], token[2], token[3], token[4], token[5]);
   realUser = user;
}

/**
Void method createUser() - Will take user input to create a new User object and store the info in the fileToUser vector & the file
**/

void createUser()
{
   User user; //A User object
   stringLetterValidation("Enter first name", 0);
   user._firstName = inputReference;
   stringLetterValidation("Enter last name", 0);
   user._lastName = inputReference;
   stringDigitValidation("Enter age", 0);
   user._age = inputReference;
   do
   {
      flag = false;
      std::cout << "Enter gender: ";
      std::getline(std::cin, user._gender);
      if(user._gender != "m" && user._gender != "M" && user._gender != "f" && user._gender != "F")
      {
         flag = true;
         std::cout <<"\nMust enter M or F\n\n";   
      }
   } while(flag);
   stringDigitValidation("Enter height", 0);
   user._height = inputReference;
   stringDigitValidation("Enter weight", 0);
   user._weight = inputReference;
   fileToUser.push_back(user.easyPrintFull());
   file.open("Database.txt", std::ios::out | std::ios::app); 
   file << user.easyPrintFull() << "\n";
   file.close();
   std::cout << "\n" << user.easyPrintName() << " saved successfully!\n\n";
}

/**
Void method overwriteMenu() - Organized the overwrite menu into its own method
@param edit - The User number the user chose to edit
**/

void overwriteMenu(int edit)
{
   short menu = 0; //The menu variable is for the switch statement
   fillStringArray();
   do
   {
      do
      {
         std::cout << "\n-----------------------------------------------------------\n" << "User #" << edit << ": " << fileToUser[edit - 1] << "\n-----------------------------------------------------------\n\n";
         stringDigitValidation("----------Overwrite Menu----------\n\nOverwrite first name = 1\nOverwrite last name = 2\nOverwrite age = 3\nOverwrite gender = 4\nOverwrite height = 5\nOverwrite weight = 6\nBack to main menu = 7\n\nMake selection here", 0);            
         if(inputReference.length() > 9)
         {
            std::cout << "\nError: Numbers above 999,999,999 are invalid\n";
         }
      } while(inputReference.length() > 9);
      menu = stoi(inputReference);
      if(menu > 7 | menu < 1)
      {
         std::cout << "\n" << menu << " is not a valid option\n";            
      }
   } while(menu > 7 | menu < 1);
   switch(menu)
   {
      case 1:
         std::cout << "\n";
         stringLetterValidation("Enter new first name", 0);
         realUser._firstName = inputReference;
         fileToUser[edit - 1] = realUser.easyPrintFull();
         std::cout << "\nFirst name successfully updated!\n"; 
         flag = true;
         break;
      case 2:
         std::cout << "\n";
         stringLetterValidation("Enter new last name", 0);
         realUser._lastName = inputReference;
         fileToUser[edit - 1] = realUser.easyPrintFull();
         std::cout << "\nLast name successfully updated!\n";
         flag = true;
         break;
      case 3:
         std::cout << "\n";
         stringDigitValidation("Enter new age", 0);
         realUser._age = inputReference;
         fileToUser[edit - 1] = realUser.easyPrintFull();
         std::cout << "\nAge successfully updated!\n";
         flag = true;
         break;
      case 4:
         std::cout << "\n";
         do
         { 
            flag = true;
            std::cout << "Enter new gender: ";
            std::getline(std::cin, realUser._gender);
            if(realUser._gender != "m" && realUser._gender != "M" && realUser._gender != "f" && realUser._gender != "F")
            {
               flag = false;
               std::cout <<"\nMust enter M or F\n\n";   
            }
         } while(!flag);
         fileToUser[edit - 1] = realUser.easyPrintFull();
         std::cout << "\nGender successfully updated!\n";
         flag = true;
         break;
      case 5:
         std::cout << "\n";
         stringDigitValidation("Enter new height", 0);
         realUser._height = inputReference;
         fileToUser[edit - 1] = realUser.easyPrintFull();
         std::cout << "\nHeight successfully updated!\n";
         flag = true;
         break;
      case 6: 
         std::cout << "\n";
         stringDigitValidation("Enter new weight", 0);
         realUser._weight = inputReference;
         fileToUser[edit - 1] = realUser.easyPrintFull();
         std::cout << "\nWeight successfully updated!\n";
         flag = true;
         break;
      case 7:
         std::cout << "\n";
         return;                 
   }
   file.open("Database.txt", std::ios::out);
   for(int i = 0; i < size - 1; i++)
   {
      file << fileToUser[i] << "\n";
   }
   file.close();
}

/**
Void method overwrite() - Allows the user to freely edit User objects that are stored in the file
**/

void overwrite()
{
   std::string choice = ""; //The choice variable to hold the User last name/user number to edit
   int edit = 0; //The User number the user chose to edit
   bool find, equals = false; //The find bool will return true if what the user searched for exists within the fileToUser vector, equals checks if that happens or not
   std::cout << "Enter the last name of the user to edit: ";
   std::getline(std::cin, choice);
   std::cout << "\n-----------------------------------------------------------\n";
   for(int i = 0; i < size - 1; i++)
   {
      find = fileToUser[i].find(choice) != std::string::npos;
      if(find)
      {
         equals = true;
         std::cout << "User #" << (i + 1) << ": " << fileToUser[i] + "\n";
      }
   }
   if(!equals)
   {
      std::cout << "No results\n-----------------------------------------------------------\n\n";
      return;
   }
   std::cout << "-----------------------------------------------------------\n\n";
   do
   {
      do
      {
         stringDigitValidation("Enter the user number you'd like to overwrite", 0);
         if(inputReference.length() > 9)
         {
            std::cout << "\nError: Numbers above 999,999,999 are invalid\n\n";
         }
      } while(inputReference.length() > 9);
      edit = stoi(inputReference);
      if(edit > size - 1 | edit < 1)
      {
         std::cout << "\nUser number does not exist\n\n";   
      }
   } while(edit > size - 1 | edit < 1);
   convertToUser(fileToUser[edit - 1]);
   overwriteMenu(edit);
   if(flag)
   {
      overwriteMenu(edit);
   }
}

/**
Void method mainMenu() - A main menu to bring the user back to something familiar & efficient
**/

void mainMenu() 
{
   short menu = 0; //The menu variable is used for the switch statement
   stringDigitValidation("----------Main Menu----------\n\nCreate user = 1\nOverwrite user information = 2\nExit program = 3\n\nMake selection here", 0);
   if(inputReference.length() > 1)
   {
      std::cout << "\n" << menu << " is not a valid option\n\n";
      mainMenu();
   }
   std::cout << "\n";
   menu = stoi(inputReference);
   if(menu > 3 | menu < 1)
   {
      std::cout << menu << " is not a valid option\n\n";
      mainMenu();
   }  
   switch(menu)
   {
      case 1:
         createUser();
         mainMenu();
         break;
      case 2:
         overwrite();
         mainMenu();
         break;
      case 3:
         exit(0);
         break;
   }
}

main()
{
   fillStringArray();
   mainMenu();       
}
