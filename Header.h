#pragma once
#include<iostream>
#include<string>
#include<list>
#include<set>
#include<vector>
#include<unordered_map>
#include <windows.h>
#define Invalid cout << "\aInvalid choice, please try again..\n"
#define Menu(word) Sleep(500); system("cls"); cout << "<<<<<<<<<<<<<<< " << word << " >>>>>>>>>>>>>>>\n"
#define Mess(word) cout << "\n========== " << word << " ==========\n"; Sleep(300)
using namespace std;

struct Email
{
	string username;
	string password;
};

class Person {
public:
	int id;
	string name;
	Email email;

public:
	Person();
	bool log_out();
};

class Seller : public Person {
public:
	set<int>products_id;
	int num_of_products;
	unordered_map<string, int>customers_ratings;
	double rate;

public:
	Seller();
	bool log_in();
	bool regist();
	bool delete_account();
	void menu();
	void add_product();
	void remove_product();
	void display_products();
	void setRate(string cutomer_username, int newRate);
};

class Product {
public:
	int id;
	string name;
	double price;
	string category;
	int quantity;
	string seller_username;
	unordered_map<string, int>customers_ratings;
	double rate;

public:
	Product();
	Product(string seller_username);
	void setRate(string cutomer_username, int newRate);
};

class Cart {
public:
	list<pair<int, int>>list_of_products; // the product id and quantity
	double total_price;

public:
	Cart();
	void add_product(Product* pro_ptr, int quantity);
	void calc_total_price(double price, int quantity);
};

class Customer : public Person {
public:
	string address;
	string phone_number;
	Cart customer_cart;

public:
	Customer();
	bool log_in();
	bool regist();
	bool delete_account();
	void menu();
	void browse_by_name();
	void browse_by_category();
	bool add_product_to_cart(Product* pro_ptr, int quantity);
	void rate_seller(string seller_username);
	void rate_product(int pro_id);
	void display_cart_content(bool flag);
	void confirm_the_buying();
};

extern unordered_map<string, Seller>the_Sellers;
extern unordered_map<string, Customer>the_Customers;
extern unordered_map<int, Product>the_Products;
extern unordered_map<string, set<int>>the_Categories;
extern Seller* theSeller;
extern Customer* theCustomer;
extern int sellerID, customerID, productID;