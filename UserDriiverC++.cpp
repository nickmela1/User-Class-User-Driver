#include <iostream>
#include <fstream>
#include <vector>
#include "User.h" //Custom type "User", to hold information about a user

User realUser; //holds information about a User object from the convertToUser() method
std::vector<std::string> fileToUser; //Will hold file contents & update based on user input 
int size; //Will hold the size of the fileToUser vector
bool flag = false; //Will be used many times throughout the program
std::fstream file; //File object

/**
Void method fillStringArray() - Will constantly update the fileToUser vector with the file contents
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
   int i = 0; //Used for input validation several times 
   do
   {
      std::cout << "\nEnter first name: ";
      std::cin >> user._firstName;
      if(!isdigit(user._firstName[i]))
      {
         i++;
      }
      if(isdigit(user._firstName[i]))
      {
         i = 0;
         std::cout << "\nInvalid first name\n";
      }      
   } while(i == 0);
   i = 0;
   do
   {
      std::cout << "Enter last name: ";
      std::cin >> user._lastName;
      if(!isdigit(user._lastName[i]))
      { 
         i++;
      }
      if(isdigit(user._lastName[i]))
      {
         i = 0;
         std::cout << "\nInvalid first name\n\n";
      }
   } while(i == 0);
   i = 0;
   do
   {
      std::cout << "Enter age: ";
      std::cin >> user._age;
      if(isdigit(user._age[i]))
      {
         i++;
      }
      if(!isdigit(user._age[i]))
      {
         i = 0;
         std::cout <<"\nDigits only\n\n";
      }
   } while(i == 0);
   do
   {
      flag = false;
      std::cout << "Enter gender: ";
      std::cin >> user._gender;
      if(user._gender != "m" && user._gender != "M" && user._gender != "f" && user._gender != "F")
      {
         flag = true;
         std::cout <<"\nMust enter M or F\n\n";   
      }
   } while(flag);
   i = 0;
   do
   {
      std::cout << "Enter height: ";
      std::cin >> user._height;
      if(isdigit(user._height[i]))
      {
         i++;
      }
      if(!isdigit(user._height[i]))
      {
         i = 0;
         std::cout <<"\nDigits only\n\n";
      }
   } while(i == 0);
   i = 0;
   do
   {
      std::cout << "Enter weight: ";
      std::cin >> user._weight;
      if(isdigit(user._weight[i]))
      {
         i++;
      }
      if(!isdigit(user._weight[i]))
      {
         i = 0;
         std::cout <<"\nDigits only\n\n";
      }
   } while(i == 0);
   fileToUser.push_back(user.easyPrintFull());
   file.open("Database.txt", std::ios::out | std::ios::app); 
   file << user.easyPrintFull() << "\n";
   file.close();
   fillStringArray();
   std::cout << "\n" << user.easyPrintName() << " saved successfully!\n";
}

/**
Void method overwrite() - Allows the user to freely edit User objects that are stored in the file
**/

void overwrite()
{
   std::string choice, menuToString = ""; //The choice variable to hold the User last name/user number to edit, menuToString for the switch statement
   int menu, edit, i = 0; //The menu variable is for the switch statement, edit is the User number the user chose to edit
   bool find, equals = false; //The find bool will return true if what the user searched for exists within the fileToUser vector, equals checks if that happens or not
   std::cout << "\nEnter the last name of the user to edit: ";
   std::cin >> choice;
   std::cout << "\n-----------------------------------------------------------\n";
   for(int i = 0; i < size - 1; i++)
   {
      find = fileToUser[i].find(choice) != std::string::npos;
      if(find)
      {
         equals = true;
         std::cout << "User #" << (i + 1) << ": " << fileToUser[i].substr(0, fileToUser[i].length()) + "\n";
      }
   }
   if(!equals)
   {
      std::cout << "No results\n-----------------------------------------------------------\n";
      return;
   }
   std::cout << "-----------------------------------------------------------\n";
   i = 0;
   do
   {
      i++;
      std::cout << "\nEnter the user number you'd like to overwrite: ";
      std::cin >> choice;
      if(!isdigit(choice[i - 1]))
      {
         i = 0;
         std::cout << "\nDigits only\n";
      }
   } while(i == 0);
   edit = stoi(choice);
   if(edit > size - 1 | edit < 1)
   {
      std::cout << "\nUser number does not exist\n";
      return;   
   }
   std::cout << "\n-----------------------------------------------------------\n" << "User #" << edit << ": " << fileToUser[edit - 1].substr(0, fileToUser[edit - 1].length()) << "\n-----------------------------------------------------------\n";
   convertToUser(fileToUser[edit - 1]);
   do
   {
      do
      {
         i = 0;
         do
         {
            i++;
            std::cout << "\n----------Overwrite Menu----------\n\nOverwrite first name = 1\nOverwrite last name = 2\nOverwrite age = 3\nOverwrite gender = 4\nOverwrite height = 5\nOverwrite weight = 6\nBack to main menu = 7\n\nMake selection here: ";
            std::cin >> menuToString;
            if(!isdigit(menuToString[i - 1]))
            {
               i = 0;
               std::cout << "\nDigits only\n";
            }
         } while(i == 0);
         menu = stoi(menuToString);
         if(menu > 7 | menu < 1)
         {
            std::cout << "\n" << menu << " is not a valid option\n";            
         }
      } while(menu > 7 | menu < 1);
      switch(menu)
      {
         case 1:
            i = 0;
            do
            {
               std::cout << "\nEnter new first name: ";
               std::cin >> realUser._firstName;
               if(!isdigit(realUser._firstName[i]))
               {
                  i++;
               }
               if(isdigit(realUser._firstName[i]))
               {
                  i = 0;
                  std::cout <<"\nInvalid first name\n";
               }
            } while(i == 0);
            fileToUser[edit - 1] = realUser.easyPrintFull();
            std::cout << "\n-----------------------------------------------------------\n" << realUser.easyPrintFull() << "\n-----------------------------------------------------------\n";
            flag = true;
            break;
         case 2:
            i = 0;
            do
            {
               std::cout << "\nEnter new last name: ";
               std::cin >> realUser._lastName;
               if(!isdigit(realUser._lastName[i]))
               {
                  i++;
               }
               if(isdigit(realUser._lastName[i]))
               {
                  i = 0;
                  std::cout <<"\nInvalid last name\n";
               }
            } while(i == 0);
            fileToUser[edit - 1] = realUser.easyPrintFull();
            std::cout << "\n-----------------------------------------------------------\n" << realUser.easyPrintFull() << "\n-----------------------------------------------------------\n";
            flag = true;
            break;
         case 3:
            i = 0;
            do
            {
               std::cout << "\nEnter new age: ";
               std::cin >> realUser._age;
               if(isdigit(realUser._age[i]))
               {
                  i++;
               }
               if(!isdigit(realUser._age[i]))
               {
                  i = 0;
                  std::cout <<"\nDigits only\n";
               }
            } while(i == 0);
            fileToUser[edit - 1] = realUser.easyPrintFull();
            std::cout << "\n-----------------------------------------------------------\n" << realUser.easyPrintFull() << "\n-----------------------------------------------------------\n";
            flag = true;
            break;
         case 4:
            do
            { 
               flag = true;
               std::cout << "\nEnter new gender: ";
               std::cin >> realUser._gender;
               if(realUser._gender != "m" && realUser._gender != "M" && realUser._gender != "f" && realUser._gender != "F")
               {
                  flag = false;
                  std::cout <<"\nMust enter M or F\n\n";   
               }
            } while(!flag);
            fileToUser[edit - 1] = realUser.easyPrintFull();
            std::cout << "\n-----------------------------------------------------------\n" << realUser.easyPrintFull() << "\n-----------------------------------------------------------\n";
            flag = true;
            break;
         case 5:
            i = 0;
            do
            {
               std::cout << "\nEnter new height: ";
               std::cin >> realUser._height;
               if(isdigit(realUser._height[i]))
               {
                  i++;
               }
               if(!isdigit(realUser._height[i]))
               {
                  i = 0;
                  std::cout <<"\nDigits only\n";
               }
            } while(i == 0);
            fileToUser[edit - 1] = realUser.easyPrintFull();
            std::cout << "\n-----------------------------------------------------------\n" << realUser.easyPrintFull() << "\n-----------------------------------------------------------\n";
            flag = true;
            break;
         case 6: 
            i = 0;
            do
            {
               std::cout << "\nEnter new weight: ";
               std::cin >> realUser._weight;
               if(isdigit(realUser._weight[i]))
               {
                  i++;
               }
               if(!isdigit(realUser._weight[i]))
               {
                  i = 0;
                  std::cout <<"\nDigits only\n";
               }
            } while(i == 0);
            fileToUser[edit - 1] = realUser.easyPrintFull();
            std::cout << "\n-----------------------------------------------------------\n" << realUser.easyPrintFull() << "\n-----------------------------------------------------------\n";
            flag = true;
            break;
         case 7:
            return;                 
      }
      fillStringArray();
      file.open("Database.txt", std::ios::out);
      for(int i = 0; i < size - 1; i++)
      {
         file << fileToUser[i] << "\n";
      }
      file.close();
   } while(flag);
}

/**
Void method mainMenu() - A main menu to bring the user back to something familiar & efficient
**/

void mainMenu() 
{
   std::string menuToString = ""; //Used for the switch statement & easier input validation
   int menu, i = 0; //The menu variable is used for the switch statement, the i variable is used for input validation for all main menu options
   do
   {
      i++;
      std::cout << "\n----------Main Menu----------\n\nCreate user = 1\nOverwrite user information = 2\nExit program = 3\n\nMake selection here: ";
      std::cin >> menuToString;
      if(!isdigit(menuToString[i - 1]))
      {
         i = 0;
         std::cout << "\n" << menuToString << " is not a valid option\n";
      }
   } while(i == 0); 
   menu = stoi(menuToString);
   if(menu > 3 | menu < 1)
   {
      std::cout << "\n" << menu << " is not a valid option\n";
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