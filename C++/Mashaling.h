#include <vcclr.h>
#include <iostream>

class UnManaged;

public ref class Managed
{
   Managed()
   {
      p_unmanaged = new UnManaged();
   }

   call_UnManaged_function ()
   {
      p_unmanaged->UnManaged_function();
   }

   Managed_function()
   {
      System::Consol::WriteLine("Called Managed function");
   }

   UnManaged* p_unmanaged;
};


class UnManaged
{
public:
   UnManaged()
   {
      p_Managed = gcnew Managed();
   }

   UnManaged_function()
   {
      std::cout << "Called UnManaged function" << std::endl;
   }

   call_Managed_function ()
   {
      p_Managed->UnManaged_function();
   }

   gcroot <Managed^> p_Managed;
};

