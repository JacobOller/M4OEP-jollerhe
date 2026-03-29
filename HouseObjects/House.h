//
// Created by jacob on 1/28/2026.
//

#ifndef M1OEP_House_H
#define M1OEP_House_H

#include <fstream>
#include <string>
#include <vector>


class House {
private:
    // Fields
    std::string brokered_by, status, street_id, city, state, zip_code, prev_sold_date;
    int price, beds, baths, house_size;
    double size_in_acres;

public:
    // Default Constructor
    House();

    // Main Constructor
    House(std::string brokered_by, std::string status, int price, int beds,
        int baths, double size_in_acres, std::string street_id, std::string city,
        std::string state, std::string zip_code, int house_size, std::string prev_sold_date);

    // Getters
    std::string get_brokered_by() const;
    std::string get_status() const;
    int get_price() const;
    int get_beds() const;
    int get_baths() const;
    double get_size_in_acres() const;
    std::string get_street_id() const;
    std::string get_city() const;
    std::string get_state() const;
    std::string get_zip_code() const;
    int get_house_size() const;
    std::string get_prev_sold_date() const;

    // Setters
    void set_brokered_by(std::string brokered_by);
    void set_status(std::string status);
    void set_price(int price);
    void set_beds(int beds);
    void set_baths(int baths);
    void set_size_in_acres(double size_in_acres);
    void set_street_id(std::string street_id);
    void set_city(std::string city);
    void set_state(std::string state);
    void set_zip_code(std::string zip_code);
    void set_house_size(int house_size);
    void set_prev_sold_date(std::string prev_sold_date);

    friend std::ostream &operator<<(std::ostream &outs, const House &s);
    friend bool operator < (const House &l_house, const House &r_house);
    friend bool operator > (const House &l_house, const House &r_house);
    friend bool operator <= (const House &l_house, const House &r_house);
    friend bool operator >= (const House &l_house, const House &r_house);
    friend bool operator == (const House &l_house, const House &r_house);
    friend bool operator != (const House &l_house, const House &r_house);
};

#endif //M1OEP_House_H