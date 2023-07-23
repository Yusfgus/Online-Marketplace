#include "Header.h"

Cart::Cart()
{
	this->total_price = 0.0;
}

void Cart::add_product(Product* pro_ptr, int quantity)
{
	this->list_of_products.push_back({ pro_ptr->id, quantity });
	this->calc_total_price(pro_ptr->price, quantity);
	cout << "This will cost you $" << pro_ptr->price*quantity << '\n';
}

void Cart::calc_total_price(double price, int quantity)
{
	this->total_price += price * quantity;
}
