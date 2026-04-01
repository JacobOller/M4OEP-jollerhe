//
// Created by jacob on 1/28/2026.
//

#include "./House.h"

#include <iomanip>
#include <iostream>
#include <fstream>

House::House()  {
    brokered_by = "";
    status = "";
    price = -1;
    beds = -1;
    baths = -1;
    size_in_acres = -1.0;
    street_id = "";
    city = "";
    state = "";
    zip_code = "";
    house_size = -1;
    prev_sold_date = "";
}
House::House(std::string brokered_by, std::string status, int price, int beds,
    int baths, double size_in_acres, std::string street_id, std::string city, std::string state,
        std::string zip_code, int house_size, std::string prev_sold_date ) {
    this->brokered_by = brokered_by;
    this->status = status;
    this->price = price;
    this->beds = beds;
    this->baths = baths;
    this->size_in_acres = size_in_acres;
    this->street_id = street_id;
    this->city = city;
    this->state = state;
    this->zip_code = zip_code;
    this->house_size = house_size;
    this->prev_sold_date = prev_sold_date;
}

std::string House::get_brokered_by() const {
    return brokered_by;
}
std::string House::get_status() const {
    return status;
}
int House::get_price() const {
    return price;
}
int House::get_beds() const {
    return beds;
}
int House::get_baths() const {
    return baths;
}
double House::get_size_in_acres() const {
    return size_in_acres;
}
std::string House::get_street_id() const {
    return street_id;
}
std::string House::get_city() const {
    return city;
}
std::string House::get_state() const{
    return state;
}
std::string House::get_zip_code() const {
    return zip_code;
}
int House::get_house_size() const {
    return house_size;
}
std::string House::get_prev_sold_date() const {
    return prev_sold_date;
}

void House::set_brokered_by(std::string brokered_by) {
    brokered_by = brokered_by;
}
void House::set_status(std::string status) {
    status = status;
}
void House::set_price(int price) {
    price = price;
}
void House::set_beds(int beds) {
    beds = beds;
}
void House::set_baths(int baths) {
    baths = baths;
}
void House::set_size_in_acres(double size_in_acres) {
    size_in_acres = size_in_acres;
}
void House::set_street_id(std::string street_id) {
    street_id = street_id;
}
void House::set_city(std::string city) {
    city = city;
}
void House::set_state(std::string state) {
    state = state;
}
void House::set_zip_code(std::string zip_code) {
    zip_code = zip_code;
}
void House::set_house_size(int house_size) {
    house_size = house_size;
}
void House::set_prev_sold_date(std::string prev_sold_date) {
    prev_sold_date = prev_sold_date;
}

// Printing out the important info:
// Broker_ID, Price, Beds and Baths, Acres, and the City
std::ostream &operator<<(std::ostream &outs, const House &h) {
    // Column 1: Broker ID
    outs << std::right << std::setw(9) << h.brokered_by;
    // Column 3: Price
    outs << " $" << std::right << std::setw(9) << h.price;
    // Column 4: Beds
    outs << std::right << std::setw(5) << h.beds;
    // Column 5: Baths
    outs << " " << std::right << std::setw(4) << h.baths;
    // Column 6: Acres
    outs << "  " << std::right << std::setw(6) << std::setprecision(2) << h.size_in_acres;
    // Column 7: State
    outs << "   " << std::left << std::setw(12) << h.state;
    // Column 8: City
    outs << std::right << std::setw(12) << h.city;
    return outs;
}

// Overloaded Operators that compare the house price values.
// Overloaded < Operator for object comparison
bool operator < (const House &l_house, const House &r_house){
    return l_house.get_price() < r_house.get_price();
}
// Overloaded > Operator for price object comparison
bool operator > (const House &l_house, const House &r_house) {
    return l_house.get_price() > r_house.get_price();
}
// Overloaded <= Operator for price object comparison
bool operator <= (const House &l_house, const House &r_house) {
    return l_house.get_price() <= r_house.get_price();
}
// Overloaded >= Operator for price object comparison
bool operator >= (const House &l_house, const House &r_house) {
    return l_house.get_price() >= r_house.get_price();
}
// Overloaded == Operator for price object comparison
bool operator == (const House &l_house, const House &r_house) {
    return l_house.get_price() == r_house.get_price();
}
// Overloaded != Operator for price object comparison
bool operator != (const House &l_house, const House &r_house) {
    return l_house.get_price() != r_house.get_price();
}
