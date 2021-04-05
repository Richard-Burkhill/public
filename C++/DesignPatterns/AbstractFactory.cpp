#include <iostream>

class Button
{
public:
	virtual void paint() = 0;
};
 
class WinButton : public Button 
{
public:
	void paint (){
		std::cout << " Window Button \n";
       }
};
 
class MacButton : public Button 
{
public:
	void paint (){
		std::cout << " Mac Button \n";
       }
};

class ScrollBar 
{
public:
	virtual void paint() = 0;
};
 
class WinScrollBar : public ScrollBar 
{
public:
	void paint (){
		std::cout << " Window ScrollBar \n";
       }
};
 
class MacScrollBar : public ScrollBar {
public:

	void paint (){
		std::cout << " Mac ScrollBar \n";
       }
};
