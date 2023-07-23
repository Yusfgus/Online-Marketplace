#include "Header.h"

Person::Person()
{
	id = 0;
	name = "";
}

bool Person::log_out()
{
	string ans;
	cout << "Are you sure you want to log out? (Y/y) -> ";
	getline(cin, ans);
	if (ans == "Y" || ans == "y") {
		Mess("You logged out successfully");
		return true;
	}
	return false;
}
