#include <string>

class AddressBookEntry {
   public:
      AddressBookEntry() = delete;
      AddressBookEntry(const AddressBookEntry&) = default;
      AddressBookEntry(AddressBookEntry&&) = default;
      AddressBookEntry& operator=(const AddressBookEntry&) = default;
      AddressBookEntry& operator=(AddressBookEntry&&) = default;

      AddressBookEntry(int entry, std::string last, std::string first, std::string telephone, std::string email);
      bool operator<(const AddressBookEntry& rhs) const;
      bool operator>(const AddressBookEntry& rhs) const;

   protected:
      int entry_number;
      std::string last_name;
      std::string first_name;
      std::string telephone_number;
      std::string email_address;
};
