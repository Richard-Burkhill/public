#include "AddressBookEntry.hpp"

AddressBookEntry::AddressBookEntry(int entry, std::string last, std::string first, std::string telephone, std::string email)
 : entry_number{entry},
 last_name{last},
 first_name{first},
 telephone_number{telephone},
 email_address{email}
{}

bool AddressBookEntry::operator<(const AddressBookEntry& rhs) const
{
   return (entry_number < rhs.entry_number);
}

bool AddressBookEntry::operator>(const AddressBookEntry& rhs) const
{
   return (entry_number > rhs.entry_number);
}

