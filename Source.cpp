#include"Header.h"
#include<fstream>
unordered_map<string, Seller>the_Sellers;
unordered_map<string, Customer>the_Customers;
unordered_map<int, Product>the_Products;
unordered_map<string, set<int>>the_Categories;
Seller* theSeller = NULL;
Customer* theCustomer = NULL;
int sellerID = 0, customerID = 0, productID = 0;

void Read();
void Write();

int main()
{
	Read();
	//cout << "================================== WELCOME ================================\n";
	string ans;
	while (true)
	{
		Menu("MAIN MENU");
		cout << "\n1-Buy\n2-Sell\n3-Regist\n4-Exit\n-> ";
		getline(cin, ans);
		if (ans == "1") {
			Customer newCustomer;
			if(newCustomer.log_in())
				theCustomer->menu();
		}
		else if (ans == "2") {
			Seller newSeller;
			if (newSeller.log_in())
				theSeller->menu();
		}
		else if (ans == "3") {
			while (true)
			{
				Menu("REGESTRATION");
				cout << "\nRegist as:\n\t1-Customer\n\t2-Seller\n\t3-Go back\n-> ";
				getline(cin, ans);
				if (ans == "1") {
					Customer newCustomer;
					if (newCustomer.regist())
						theCustomer->menu();
					break;
				}
				else if (ans == "2") {
					Seller newSeller; 
					if (newSeller.regist())
						theSeller->menu();
					break;
				}
				else if (ans == "3") {
					break;
				}
				else {
					Invalid;
				}
			}
		}
		else if (ans == "4") {
			break;
		}
		else {
			Invalid;
		}
	}

	Write();
	cout << "\n================================== GOOD BYE ================================\n";
	return 0;
}

set<int> split_id(const string& line)
{
	if (line == "#")
		return {};
	set<int>ids;
	string temp;
	for (const char& i : line)
	{
		if (i == ';') {
			ids.insert(stoi(temp));
			temp = "";
		}
		else temp += i;
	}

	return ids;
}

unordered_map<string, int> split_rate(const string& line)
{
	if (line == "#")
		return {};
	unordered_map<string, int>ratings;
	string username, temp;
	for (const char& i : line)
	{
		if (i == ',')
		{
			username = temp;
			temp = "";
		}
		else if (i == ';')
		{
			ratings.insert({ username,stoi(temp) });
			temp = "";
		}
		else temp += i;
	}

	return ratings;
}

void Read()
{
	fstream readfile("Data.txt");
	if (!readfile.is_open()) {
		Mess("The data file not found");
		exit(0);
	}

	string line, temp;
	int sz;

	readfile >> line; //<<<<<<<<<<<<<<<<PRODUCTS>>>>>>>>>>>>>>>>
	readfile >> productID >> sz;
	while (sz--)
	{
		readfile >> line; //----------------------------------------
		Product newProduct;
		readfile >> newProduct.id;
		getline(readfile >> ws, newProduct.name);
		readfile >> newProduct.price;
		getline(readfile >> ws, newProduct.category);
		readfile >> newProduct.quantity;
		getline(readfile >> ws, newProduct.seller_username);
		readfile >> line;
		newProduct.customers_ratings = split_rate(line);
		readfile >> newProduct.rate;
		the_Products.insert({ newProduct.id, newProduct });
	}
	//Mess("PRODUCTS READ");

	readfile >> line; //<<<<<<<<<<<<<<<<SELLERS>>>>>>>>>>>>>>>>>
	readfile >> sellerID >> sz;
	while (sz--)
	{
		readfile >> line; //----------------------------------------
		Seller newSeller;
		readfile >> newSeller.id;
		getline(readfile >> ws, newSeller.name);
		getline(readfile >> ws, newSeller.email.username);
		getline(readfile >> ws, newSeller.email.password);
		readfile >> line; // pro_id1;pro_id2;pro_id3;pro_id4;pro_id;
		newSeller.products_id = split_id(line);
		readfile >> line; //user1,rate1;user2,rate2;user3,rate3;
		newSeller.customers_ratings = split_rate(line);
		readfile >> newSeller.rate;
		the_Sellers.insert({ newSeller.email.username, newSeller });
	}
	//Mess("SELLER READ");

	readfile >> line;  //<<<<<<<<<<<<<<<CUSTOMERS>>>>>>>>>>>>>>>>
	readfile >> customerID >> sz;
	while(sz--)
	{
		readfile >> line; //----------------------------------------
		Customer newCustomer;
		readfile >> newCustomer.id;
		getline(readfile >> ws, newCustomer.name);
		getline(readfile >> ws, newCustomer.email.username);
		getline(readfile >> ws, newCustomer.email.password);
		getline(readfile >> ws, newCustomer.address);
		getline(readfile >> ws, newCustomer.phone_number);
		readfile >> line; //pro_id1,quan1;pro_id2,quan2;
		if (line != "#") {
			int id;
			for (const char& i : line)
			{
				if (i == ',')
				{
					id = stoi(temp);
					temp = "";
				}
				else if (i == ';')
				{
					newCustomer.customer_cart.list_of_products.push_back({ id,stoi(temp) });
					newCustomer.customer_cart.calc_total_price(the_Products[id].price, stoi(temp));
					temp = "";
				}
				else temp += i;
			}
		}
		the_Customers.insert({ newCustomer.email.username, newCustomer });
	}
	//Mess("CUSTOMER READ");

	readfile >> line; //<<<<<<<<<<<<<<<CATEGORIES>>>>>>>>>>>>>>>
	readfile >> sz;
	while (sz--)
	{
		readfile >> line; //----------------------------------------
		readfile >> temp;
		readfile >> line;
		the_Categories.insert({ temp, split_id(line) });
	}
	//Mess("CATEGORIES READ");

	readfile >> line; //<<<<<<<<<<<<<<<<<<END>>>>>>>>>>>>>>>>>>>

	readfile.close();
}

void Write()
{
	ofstream writefile("Data.txt");
	if (!writefile.is_open()) {
		Mess("The data file not found");
		exit(0);
	}

	writefile << "<<<<<<<<<<<<<<<<PRODUCTS>>>>>>>>>>>>>>>>\n";
	writefile << productID << '\n' << the_Products.size();
	for (const auto& product : the_Products)
	{
		writefile << "\n----------------------------------------\n";
		writefile << product.second.id << '\n' << product.second.name << '\n' << product.second.price << '\n' << product.second.category << '\n' << product.second.quantity << '\n' << product.second.seller_username << '\n';

		if (product.second.customers_ratings.size() == 0)
			writefile << '#';
		else {
			for (const auto& rate : product.second.customers_ratings)
				writefile << rate.first << ',' << rate.second << ';';
		}
		writefile << '\n' << product.second.rate;
	}
	
	writefile << "\n<<<<<<<<<<<<<<<<SELLERS>>>>>>>>>>>>>>>>>\n";
	writefile << sellerID << '\n' << the_Sellers.size();
	for (const auto& seller : the_Sellers)
	{
		writefile << "\n----------------------------------------\n";
		writefile << seller.second.id << '\n' << seller.second.name << '\n' << seller.second.email.username << '\n' << seller.second.email.password << '\n';
		
		if (seller.second.products_id.size() == 0)
			writefile << '#';
		else {
			for (const int& pro_id : seller.second.products_id)
				writefile << pro_id << ';';
		}
		writefile << '\n';

		if (seller.second.customers_ratings.size() == 0)
			writefile << '#';
		else {
			for (const auto& rate : seller.second.customers_ratings)
				writefile << rate.first << ',' << rate.second << ';';
		}
		writefile << '\n' << seller.second.rate;
	}

	writefile << "\n<<<<<<<<<<<<<<<CUSTOMERS>>>>>>>>>>>>>>>>\n";
	writefile << customerID << '\n' << the_Customers.size();
	for (const auto& customer : the_Customers)
	{
		writefile << "\n----------------------------------------\n";
		writefile << customer.second.id << '\n' << customer.second.name << '\n' << customer.second.email.username << '\n' << customer.second.email.password << '\n' << customer.second.address << '\n' << customer.second.phone_number << '\n';

		if (customer.second.customer_cart.list_of_products.size() == 0)
			writefile << '#';
		else {
			for (const auto& pro : customer.second.customer_cart.list_of_products)
				writefile << pro.first << ',' << pro.second << ';';
		}
	}

	writefile << "\n<<<<<<<<<<<<<<<CATEGORIES>>>>>>>>>>>>>>>\n";
	writefile << the_Categories.size();
	for (const auto& cat : the_Categories) {
		writefile << "\n----------------------------------------\n";
		writefile << cat.first << '\n';
		if (cat.second.size() == 0)
			writefile << '#';
		else {
			for (const int& pro_id : cat.second)
				writefile << pro_id << ';';
		}
	}
	
	writefile << "\n<<<<<<<<<<<<<<<<<<END>>>>>>>>>>>>>>>>>>>";

	writefile.close();
}
