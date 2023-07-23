#include "Header.h"

Customer::Customer()
{
	this->address = "";
	this->phone_number = "";
}

bool Customer::log_in()
{
	Menu("CUSTOMER LOGGING IN");
	string ans;
	cout << "\nEnter:";
	while (true)
	{
		cout << "\n\tUsername : "; getline(cin, this->email.username);
		cout << "\tPasswrod : "; getline(cin, this->email.password);
		auto it = the_Customers.find(this->email.username);
		if (it != the_Customers.end() && it->second.email.password == this->email.password)
		{
			theCustomer = &it->second;
			Mess("You logged in successfully");
			return true;
		}
		else {
			Mess("Wrong username or password");
			cout << "Try again? (Y/y) -> ";
			getline(cin, ans);
			if (ans != "Y" && ans != "y")
				return false;
		}
	}
}

bool Customer::regist()
{
	Menu("CUSTOMER REGESTERATION");
	string ans;
	cout << "\nEnter:";
	cout << "\n\tFull name : "; getline(cin, this->name);
	cout << "\tAddress : "; getline(cin, this->address);
	cout << "\tPhone number : "; getline(cin, this->phone_number);
	while (true)
	{
		cout << "\tUsername : "; getline(cin, this->email.username);
		if (the_Customers.find(this->email.username) == the_Customers.end())
			break;
		else {
			Mess("This username is taken");
			cout << "Try again? (Y/y) -> ";
			getline(cin, ans);
			if (ans != "Y" && ans != "y")
				return false;
		}
	}
	cout << "\tPasswrod : "; getline(cin, this->email.password);
	cout << "\nConfirm the regestration? (Y/y) -> ";
	getline(cin, ans);
	if (ans == "Y" || ans == "y") {
		this->id = ++customerID;
		the_Customers.insert({ this->email.username, *this });
		theCustomer = &the_Customers[this->email.username];
		Mess("The Registeration completed successfully");
		return true;
	}
	else {
		Mess("The Registeration canceled");
		return false;
	}
}

bool Customer::delete_account()
{
	Menu("DELETE ACCOUNT");
	string ans;
	cout << "Are you sure you want to log out? (Y/y) -> ";
	getline(cin, ans);
	if (ans == "Y" || ans == "y") {
		the_Customers.erase(this->email.username);
		return true;
	}

	return false;
}

void Customer::browse_by_name()
{
	string ans;
	int i;
	while (true)
	{
		Menu("BROWSE BY NAME");
		i = 0;
		cout << "\nProducts: quantity (Price)\n";
		for (const auto& pro : the_Products)
			cout << "\n" << ++i << "-" << pro.second.name << " x" << pro.second.quantity << " ($" << pro.second.price << ")";

		while (true)
		{
			cout << "\n\nSelect a product to add to cart or enter \'0\' to go back -> ";
			cin >> i; cin.ignore();
			if (i == 0) return;
			else if (i < 0 || i > the_Products.size()) {
				Invalid;
				cout << "\nTry again? (Y/y) -> ";
				getline(cin, ans);
				if (ans != "Y" && ans != "y")
					return;
			}
			else break;
		}
		auto it = the_Products.begin();
		advance(it, i - 1);
		Product* pro_ptr = &the_Products[it->first];

		if (pro_ptr->quantity == 0) {
			Mess("Sorry, The quantity of the product has been sold out");
			continue;
		}

		while (true)
		{
			cout << "Enter the quantity -> ";
			cin >> i; cin.ignore();
			if (i <= 0) {
				Invalid;
				cout << "\nTry again? (Y/y) -> ";
				getline(cin, ans);
				if (ans != "Y" && ans != "y")
					return;
			}
			break;
		}
		if (i > pro_ptr->quantity) {
			cout << "There is no enough quantity, only " << pro_ptr->quantity << ".\nTake them any way? (Y/y) -> ";
			getline(cin, ans);
			if (ans == "Y" || ans == "y")
				i = pro_ptr->quantity;
			else continue;
		}

		if (this->add_product_to_cart(pro_ptr, i))
		{
			this->rate_product(it->first);
			this->rate_seller(the_Products[it->first].seller_username);
		}
	}
}

void Customer::browse_by_category()
{
	Menu("BROWSE BY CATEGORY");
	int i = 0;
	string ans;
	cout << "\nSelect Category: ";
	for (auto cat : the_Categories)
		cout << "\n\t" << ++i << "-" << cat.first;
	while (true)
	{
		cout << "\n-> "; cin >> i;
		if (i <= 0 || i > the_Categories.size()) {
			Invalid;
			cout << "\nTry again? (Y/y) -> ";
			getline(cin, ans);
			if (ans != "Y" && ans != "y")
				return;
		}
		else break;
	}

	auto it = the_Categories.begin();
	advance(it, i - 1);
	while (true)
	{
		Product* pro_ptr;
		i = 0;
		cout << endl << it->first << ": ";
		cout << "\n\tProducts: quantity (Price)\n";
		for (const int& pro_id : it->second) {
			pro_ptr = &the_Products[pro_id];
			cout << "\n\t" << ++i << "-" << pro_ptr->name << " x" << pro_ptr->quantity << " ($" << pro_ptr->price << ")";
		}
		while (true)
		{
			cout << "\n\nSelect a product to add to cart or enter \'0\' to go back -> ";
			cin >> i; cin.ignore();
			if (i == 0) return;
			else if (i < 0 || i > it->second.size()) {
				Invalid;
				cout << "\nTry again? (Y/y) -> ";
				getline(cin, ans);
				if (ans != "Y" && ans != "y")
					return;
			}
			else break;
		}
		auto it2 = it->second.begin();
		advance(it2, i - 1);
		pro_ptr = &the_Products[*it2];

		if (pro_ptr->quantity == 0) {
			Mess("Sorry, The quantity of the product has been sold out");
			continue;
		}

		while (true)
		{
			cout << "Enter the quantity -> ";
			cin >> i; cin.ignore();
			if (i <= 0) {
				Invalid;
				cout << "\nTry again? (Y/y) -> ";
				getline(cin, ans);
				if (ans != "Y" && ans != "y")
					return;
			}
			break;
		}
		if (i > pro_ptr->quantity) {
			cout << "There is no enough quantity, only " << pro_ptr->quantity << ".\nTake them any way? (Y/y) -> ";
			getline(cin, ans);
			if (ans == "Y" || ans == "y")
				i = pro_ptr->quantity;
			else continue;
		}

		if (this->add_product_to_cart(pro_ptr, i))
		{
			this->rate_product(*it2);
			this->rate_seller(pro_ptr->seller_username);
		}
	}
}

bool Customer::add_product_to_cart(Product* pro_ptr, int quantity)
{
	string ans;
	cout << "Confirm adding " << pro_ptr->name << " to your cart? (Y/y) -> ";
	getline(cin, ans);
	if (ans != "Y" && ans != "y")
		return false;

	this->customer_cart.add_product(pro_ptr, quantity);
	pro_ptr->quantity -= quantity;

	Mess(pro_ptr->name + " added to your cart");
	cout << '\n';
	return true;
}

void Customer::rate_seller(string seller_username)
{
	int rate;
	string ans;
	cout << "Would you like to rate the seller? (Y/y) -> ";
	getline(cin, ans);
	if (ans != "Y" && ans != "y")
		return;

	while (true)
	{
		cout << "Enter the rate of 5 -> ";
		cin >> rate;
		if (rate < 1 || rate > 5) {
			Invalid;
			cout << "\nTry again? (Y/y) -> ";
			cin.ignore();
			getline(cin, ans);
			if (ans != "Y" && ans != "y")
				return;
		}
		cin.ignore();
		break;
	}
	the_Sellers[seller_username].setRate(this->email.username, rate);
	Mess("Rating complented successfully");
}

void Customer::rate_product(int pro_id)
{
	int rate;
	string ans;
	cout << "Would you like to rate the product? (Y/y) -> ";
	getline(cin, ans);
	if (ans != "Y" && ans != "y")
		return;

	while (true)
	{
		cout << "Enter the rate of 5 -> ";
		cin >> rate;
		if (rate < 1 || rate > 5) {
			Invalid;
			cout << "\nTry again? (Y/y) -> ";
			cin.ignore();
			getline(cin, ans);
			if (ans != "Y" && ans != "y")
				return;
		}
		cin.ignore();
		break;
	}
	the_Products[pro_id].setRate(this->email.username, rate);
	Mess("Rating complented successfully");
}

void Customer::display_cart_content()
{
	Menu("DISPLAY CART CONTENT");
	if (this->customer_cart.list_of_products.size() == 0) {
		Mess("Your Cart is empty");
		return;
	}
	cout << "\nCart content: (";
	for (const auto& pro : this->customer_cart.list_of_products)
	{
		cout << " " << the_Products[pro.first].name << " x" << pro.second << ",";
	}
	cout << "\b )\n";
	cout << "\nEnter any thing to go back -> ";
	string s;
	getline(cin, s);
}

void Customer::confirm_the_buying()
{
	Menu("CONFIRM THE BUYING");
	if (this->customer_cart.list_of_products.size() == 0) {
		Mess("Your Cart is empty");
		return;
	}
	this->display_cart_content();
	string ans;
	cout << "Confirm the buying? (Y/y) -> ";
	getline(cin, ans);
	if (ans != "Y" && ans != "y")
	{
		string cat;
		for (const auto& pro : this->customer_cart.list_of_products)
			the_Products[pro.first].quantity += pro.second;

		Mess("The buying process canceled successfully");
	}
	else {
		cout << "\nThe total price is " << this->customer_cart.total_price << endl;
		Mess("The buying process completed successfully");
	}
	this->customer_cart.list_of_products.clear();
	this->customer_cart.total_price = 0;
}

void Customer::menu()
{
	string ans;
	while (true)
	{
		Menu("CUSTOMER MENU");
		cout << "\n1-Browse by Name\n2-Browse by Category\n3-Display Cart content\n4-Confirm the buying\n5-Log Out\n6-Delete Account\n-> ";
		getline(cin, ans);
		if (ans == "1") {
			this->browse_by_name();
		}
		else if (ans == "2") {
			this->browse_by_category();
		}
		else if (ans == "3") {
			this->display_cart_content();
		}
		else if (ans == "4") {
			this->confirm_the_buying();
		}
		else if (ans == "5") {
			if (this->log_out())
				return;
		}
		else if (ans == "6") {
			if (this->delete_account())
				return;
		}
		else {
			break;
		}
	}
}

