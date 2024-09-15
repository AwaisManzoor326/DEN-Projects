#include <iostream>
#include <fstream>

#ifdef _WIN32
#define CLEAR "cls" // Command for clearing screen in Windows
#else
#define CLEAR "clear" // Command for clearing screen in Linux/macOS
#endif

using namespace std;

// Menu_page_class with declarations only
class MenuPage
{
private:
    static int choice; // Static choice

public:
    static int Title();
    static int Details();
    static int Menu();
};
int MenuPage::choice = 0; // Define static choice
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Contacts_managing_class with declarations
class ContactsManaging
{
private:
    string Name, PhoneNumber, Email;

public:
    ContactsManaging() {} // Default Constructor
    void setContact();
    void DeleteContact();
    void SearchContact();
    void DisplayContacts();
    void EditContact();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function that allows repeated selection of choices
inline void ChoiceLoop()
{
    ContactsManaging CM;
    int choice = 0;
    while (true)
    {
        choice = MenuPage::Title();
        switch (choice)
        {
        case 1:
            system(CLEAR); // Use the correct clear command based on the OS
            cout << "\n\t\t\t...ADD CONTACT..." << endl;
            CM.setContact();
            break;
        case 2:
            system(CLEAR); // Use the correct clear command based on the OS
            cout << "\n\t\t\t...DELETE CONTACT..." << endl;
            CM.DeleteContact();
            break;
        case 3:
            system(CLEAR); // Use the correct clear command based on the OS
            cout << "\n\t\t\t...SEARCH CONTACT..." << endl;
            CM.SearchContact();
            break;
        case 4:
            system(CLEAR);
            cout << "\n\t\t\t...DISPLAYING CONTACTS..." << endl;
            CM.DisplayContacts();
            break;
        case 5:
            system(CLEAR);
            cout << "\n\t\t\t...EDIT CONTACT..." << endl;
            CM.EditContact();
            break;
        case 6:
            cout << "\n\t\t\tExiting Contact Management System...\n";
            exit(0); // Exit if choice is 6
            break;
        default:
            cout << "\t\t!!!! INVALID INPUT !!!!" << endl;
            break;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    ChoiceLoop(); // Start choice loop
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu_page_class function definitions
inline int MenuPage::Title()
{
    cout << "\n\n\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t*                                                                     *" << endl;
    cout << "\t\t\t*         C O N T A C T__M A N A G E M E N T__S Y S T E M             *" << endl;
    cout << "\t\t\t*                                                                     *" << endl;
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\n\t\t****************************************************************************************" << endl;
    int ch = Details();
    return ch;
}
inline int MenuPage::Details()
{
    cout << "\n\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t*   Name    : Awais Manzoor                                           *" << endl;
    cout << "\t\t\t*   Project : Contact Management System                               *" << endl;
    cout << "\t\t\t*             Digital Empowerment Network                             *" << endl;
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\n\t\t****************************************************************************************\n";
    int c = Menu();
    return c;
}
inline int MenuPage::Menu()
{
    cout << "\n\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t*                                                                      *" << endl;
    cout << "\t\t\t*   1. Add Contact                                                     *" << endl;
    cout << "\t\t\t*   2. Delete Contact                                                  *" << endl;
    cout << "\t\t\t*   3. Search Contact                                                  *" << endl;
    cout << "\t\t\t*   4. Display Contact                                                 *" << endl;
    cout << "\t\t\t*   5. Edit Contact                                                    *" << endl;
    cout << "\t\t\t*   6. Exit Contact Management System                                  *" << endl;
    cout << "\t\t\t*                                                                      *" << endl;
    cout << "\t\t\t************************************************************************" << endl;
    cout << "\t\t****************************************************************************************\n";
    cout << "\t\t\tEnter your choice (1-6): ";
    cin >> choice;
    return choice;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Contacts_Managing_Class definitions
inline void ContactsManaging::setContact()
{
    cout << "\n\t\t\t***********************************************************************" << endl;
    cout << "\n\t\t\tEnter Contact Name: ";
    cin.ignore(); // Ignore any previous newline in the input buffer
    getline(cin, Name);
    cout << "\t\t\tEnter Contact Number: ";
    getline(cin, PhoneNumber);
    cout << "\t\t\tEnter Contact Email: ";
    getline(cin, Email);
    fstream ContactsFile;
    ContactsFile.open("Contacts.txt", ios::out | ios::app);
    ContactsFile << Name << "\t" << PhoneNumber << "\t" << Email << endl;
    ContactsFile.close();
    cout << "\n\t\t\t***********************************************************************";
    cout << "\n\n\t\t\t------Contact Added Successfully------" << endl;
}
///////////////////
// Delete Contact Function
inline void ContactsManaging::DeleteContact()
{
    cout << "\n\t\t\t***********************************************************************" << endl;
    cout << "\n\t\t\tEnter Contact Name: ";
    cin.ignore(); // Ignore any previous newline in the input buffer
    getline(cin, Name);

    fstream ContactsFile, TempFile;
    ContactsFile.open("Contacts.txt", ios::in);
    TempFile.open("Temp.txt", ios::out); // Temporary file to store contacts

    bool contactDeleted = false;
    string line;
    if (ContactsFile.is_open() && TempFile.is_open())
    {
        while (getline(ContactsFile, line))
        {
            if (line.find(Name) == string::npos)
            {
                TempFile << line << endl; // Write lines that don't match the contact
            }
            else
            {
                contactDeleted = true; // Mark contact as found and deleted
            }
        }
        ContactsFile.close();
        TempFile.close();

        if (contactDeleted)
        {
            remove("Contacts.txt");             // Delete original file
            rename("Temp.txt", "Contacts.txt"); // Rename temp file to original
            cout << "\n\t\t\tContact Deleted Successfully!" << endl;
        }
        else
        {
            cout << "\n\t\t\tContact Not Found!" << endl;
            remove("Temp.txt"); // Delete temp file if no contact was found
        }
    }
}
///////////////////////////
inline void ContactsManaging::SearchContact()
{
    cout << "\n\t\t\t***********************************************************************" << endl;
    cout << "\n\t\t\tEnter Contact Name: ";
    cin.ignore(); // Ignore any previous newline in the input buffer
    getline(cin, Name);

    fstream ContactsFile;
    ContactsFile.open("Contacts.txt", ios::in);

    if (ContactsFile.is_open())
    {
        string line;
        bool contactFound = false;

        while (getline(ContactsFile, line))
        {
            // Split the line based on tabs
            size_t pos1 = line.find("\t");
            size_t pos2 = line.find("\t", pos1 + 1);

            if (pos1 != string::npos && pos2 != string::npos)
            {
                string contactName = line.substr(0, pos1);
                string contactNumber = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string contactEmail = line.substr(pos2 + 1);

                // Check if the name matches the search term
                if (contactName == Name)
                {
                    cout << "\n\t\t\t----------------------------Contact Found--------------------------------" << endl;
                    cout << "\n\t\t\tContact Name   : " << contactName << endl;
                    cout << "\n\t\t\tContact Number : " << contactNumber << endl;
                    cout << "\n\t\t\tContact Email  : " << contactEmail << endl;
                    contactFound = true;
                    break; // Contact found, exit the loop
                }
            }
        }
        ContactsFile.close();

        if (!contactFound)
        {
            cout << "\n\t\t\tContact Not Found!" << endl;
        }
    }
    else
    {
        cout << "\n\t\t\tUnable to open the Contacts file." << endl;
    }
    cout << "\n\t\t\t***********************************************************************" << endl;
}
///////////////////////////
inline void ContactsManaging::DisplayContacts()
{
    cout << "\t\t\t***********************************************************************\n"
         << endl;
    fstream ContactsFile;
    ContactsFile.open("Contacts.txt", ios::in);
    if (ContactsFile.is_open())
    {
        string line;
        while (getline(ContactsFile, line))
        {
            cout << "\t\t\t *" << line << endl;
        }
        ContactsFile.close();
    }
    else
    {
        cout << "\n\t\t\tUnable to open the Contacts file." << endl;
    }
}
inline void ContactsManaging::EditContact()
{
    cout << "\n\t\t\t***********************************************************************" << endl;
    cout << "\n\t\t\tEnter Contact Name to Edit: ";
    cin.ignore(); // Ignore any previous newline in the input buffer
    getline(cin, Name);

    fstream ContactsFile, TempFile;
    ContactsFile.open("Contacts.txt", ios::in);
    TempFile.open("Temp.txt", ios::out); // Temporary file to store updated contacts

    bool contactFound = false;
    string line;

    if (ContactsFile.is_open() && TempFile.is_open())
    {
        while (getline(ContactsFile, line))
        {
            // Split the line based on tabs
            size_t pos1 = line.find("\t");
            size_t pos2 = line.find("\t", pos1 + 1);

            if (pos1 != string::npos && pos2 != string::npos)
            {
                string contactName = line.substr(0, pos1);
                string contactNumber = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string contactEmail = line.substr(pos2 + 1);

                // Check if the name matches the search term
                if (contactName == Name)
                {
                    contactFound = true;
                    cout << "\n\t\t\t--------------------Contact Found--------------------" << endl;
                    cout << "\n\t\t\tContact Name   : " << contactName;
                    cout << "\n\t\t\tContact Number : " << contactNumber;
                    cout << "\n\t\t\tContact Email  : " << contactEmail << endl;

                    // Ask the user to edit the contact details
                    string newName, newPhoneNumber, newEmail;

                    cout << "\n\t\t\tEnter New Name (or press Enter to keep unchanged): ";
                    getline(cin, newName);
                    cout << "\t\t\tEnter New Phone Number (or press Enter to keep unchanged): ";
                    getline(cin, newPhoneNumber);
                    cout << "\t\t\tEnter New Email (or press Enter to keep unchanged): ";
                    getline(cin, newEmail);

                    // If the user doesn't enter a new value, keep the old one
                    if (newName.empty())
                        newName = contactName;
                    if (newPhoneNumber.empty())
                        newPhoneNumber = contactNumber;
                    if (newEmail.empty())
                        newEmail = contactEmail;

                    // Write the updated contact to the temp file
                    TempFile << newName << "\t" << newPhoneNumber << "\t" << newEmail << endl;
                    cout << "\n\t\t\t------Contact Updated Successfully------" << endl;
                }
                else
                {
                    // Write the unchanged contact to the temp file
                    TempFile << line << endl;
                }
            }
        }
        ContactsFile.close();
        TempFile.close();

        // If the contact was found and edited, update the original file
        if (contactFound)
        {
            remove("Contacts.txt");             // Delete the original file
            rename("Temp.txt", "Contacts.txt"); // Rename temp file to original file
        }
        else
        {
            cout << "\n\t\t\tContact Not Found!" << endl;
            remove("Temp.txt"); // Delete temp file if no contact was found
        }
    }
    else
    {
        cout << "\n\t\t\tUnable to open the Contacts file." << endl;
    }
    cout << "\n\t\t\t***********************************************************************" << endl;
}