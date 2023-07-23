#include "Header.h"

Seller::Seller()
{
	this->num_of_products = 0;
	this->rate = 0.0;
}

bool Seller::log_in()
{
	Menu("SELLER LOGGING IN");
	string ans;
	cout << "\nEnter:";
	while (true)
	{
		cout << "\n\tUsername : "; getline(cin, this->email.username);
		cout << "\tPasswrod : "; getline(cin, this->email.password);
		auto it = the_Sellers.find(this->email.username);
		if (it != the_Sellers.end() && it->second.email.password == this->email.password)
		{
			theSeller = &it->second;
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

bool Seller::regist()
{
	Menu("SELLER REGESTERATION");
	string ans;
	cout << "\nEnter:";
	cout << "\n\tFull name : "; getline(cin, this->name);
	while (true)
	{
		cout << "\tUsername : "; getline(cin, this->email.username);
		if (the_Sellers.find(this->email.username) == the_Sellers.end())
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
		this->id = ++sellerID;
		the_Sellers.insert({ this->email.username, *this });
		theSeller = &the_Sellers[this->email.username];
		Mess("The Registeration completed successfully");
		return true;
	}
	else {
		Mess("The Registeration canceled");
		return false;
	}
}

bool Seller::delete_account()
{
	Menu("DELETE ACCOUNT");
	string ans;
	cout << "Are you sure you want to log out? (Y/y) -> ";
	getline(cin, ans);
	if (ans == "Y" || ans == "y") {
		the_Sellers.erase(this->email.username);
		return true;
	}

	return false;
}

void Seller::add_product()
{
	Menu("ADD PRODUCT");
	string ans;
	Product newProduct(this->email.username);
	cout << "\nEnter the Product:";
	cout << "\n\tName: "; getline(cin, newProduct.name);
	cout << "\tCategory: "; getline(cin, newProduct.category);
	cout << "\tPrice: "; cin >> newProduct.price;
	cout << "\tQuantity: "; cin >> newProduct.quantity;
	cin.ignore();

	cout << "\nConfirm adding Product? (Y/y) -> "; getline(cin, ans);
	if (ans == "Y" || ans == "y") {
		the_Products.insert({ newProduct.id, newProduct });
		the_Categories[newProduct.category].insert(newProduct.id);
		this->products_id.insert(newProduct.id);
		this->num_of_products = this->products_id.size();
		Mess("Your Product is added successfully");
	}
	else {
		--productID;
		Mess("Adding process is canceled");
	}

}

void Seller::remove_product()
{
	Menu("REMOVE PRODUCT");
	string ans;
	int i = 0;
	cout << "\nChoose Product to remove:";
	for (const int& id : this->products_id)
		cout << "\n\t" << ++i << "-" << the_Products[id].name;
	while (true)
	{
		cout << "\n\nSelect a product to remove or enter \'0\' to go back -> ";
		cin >> i; cin.ignore();
		if (i == 0) return;
		else if (i < 0 || i > this->num_of_products) {
			Invalid;
			cout << "\nTry again? (Y/y) -> ";
			getline(cin, ans);
			if (ans != "Y" && ans != "y")
				return;
		}
		else break;
	}
	auto it = this->products_id.begin();
	auto it2 = the_Products.find(*it);
	advance(it, i - 1);
	cout << "Confirm removing \"" << it2->second.name << "\"? (Y/y) -> ";
	getline(cin, ans);
	if (ans == "Y" || ans == "y") {
		auto it3 = the_Categories.find(it2->second.category);
		it3->second.erase(*it);
		if (it3->second.size() == 0)
			the_Categories.erase(it3);
		the_Products.erase(it2);
		this->products_id.erase(it);

		Mess("The Porduct has been removed successfully");
	}
	else
		Mess("Removing process is canceled");
}

void Seller::display_products()
{
	Menu("DISPALY PRODUCTS");
	int i = 0;
	for (const int& id : this->products_id)
		cout << "\n\t" << ++i << "-" << the_Products[id].name;

	cout << "\n\nEnter any thing to go back -> ";
	string s;
	getline(cin, s);
}

void Seller::setRate(string cutomer_username, int newRate)
{
	this->customers_ratings[cutomer_username] = newRate;
	double avgRate = 0;
	for (auto& rat : this->customers_ratings)
		avgRate += rat.second;
	this->rate = avgRate / this->customers_ratings.size();
}

void Seller::menu()
{
	string ans;
	while (true)
	{
		Menu("SELLER MENU");
		cout << "\n1-Add Product\n2-Remove Product\n3-Display Products\n4-Log Out\n5-Delete Account\n-> ";
		getline(cin, ans);
		if (ans == "1") {
			this->add_product();
		}
		else if (ans == "2") {
			this->remove_product();
		}
		else if (ans == "3") {
			this->display_products();
		}
		else if (ans == "4") {
			if (this->log_out())
				return;
		}
		else if (ans == "5") {
			if (this->delete_account())
				return;
		}
		else {
			break;
		}
	}
}
