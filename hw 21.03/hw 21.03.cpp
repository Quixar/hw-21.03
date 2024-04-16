#include <iostream>
using namespace std;

class Base {
public:
	static int people_on_base;
	static int vehicles_on_base;
	static double petrol_on_base;
	static double goods_on_base;
};

int Base::people_on_base = 200;
int Base::vehicles_on_base = 40;
double Base::petrol_on_base = 1000;
double Base::goods_on_base = 1500;

class Vehicle {
protected:
	double petrol_amount;
	double tank_amount;
public:
	Vehicle(double petrol_amount, double tank_amount) {
		this->petrol_amount = petrol_amount;
		this->tank_amount = tank_amount;
	}
	double getTankAmount() const {
		return tank_amount;
	}
	double getPetrolAmount() const {
		return petrol_amount;
	}
	virtual void arrive() {};
	virtual bool leave() { return false; };
};

class Bus : public Vehicle {
private:
	int people_count;
	int max_people;
public:
	Bus(int people_count, int max_people, double petrol_amount, double tank_amount) : Vehicle(petrol_amount, tank_amount) {
		this->people_count = people_count;
		this->max_people = max_people;
	}
	int getPeopleCount() const {
		return people_count;
	}
	int getMaxPeople() const {
		return max_people;
	}
	void arrive() {
		Base::vehicles_on_base++;
		Base::people_on_base += (people_count + 1);
	}
	bool leave() {
		if (Base::petrol_on_base > tank_amount && Base::people_on_base > 0) {
			Base::vehicles_on_base--;
			Base::petrol_on_base -= (tank_amount - petrol_amount);
			if (Base::people_on_base < max_people) {
				Base::people_on_base -= people_count;
			}
			else {
				Base::people_on_base -= (max_people + 1);
			}
			petrol_amount = tank_amount;
			return true;
		}
		return false;
	}
};

class Truck : public Vehicle {
private:
	double load;
	double max_load;
public:
	Truck(double load, double max_load, double petrol_amount, double tank_amount) : Vehicle(petrol_amount, tank_amount) {
		this->load = load;
		this->max_load = max_load;
	}
	double getLoad() const {
		return load;
	}
	double getMaxLoad() const {
		return max_load;
	}
	void arrive() {
		Base::vehicles_on_base++;
		Base::people_on_base++;
		Base::goods_on_base += max_load;
	}
	bool leave() {
		if (Base::petrol_on_base > tank_amount && Base::people_on_base > 0) {
			Base::people_on_base--; 
			Base::vehicles_on_base--;
			Base::petrol_on_base -= (tank_amount - petrol_amount);
			if (Base::goods_on_base < max_load) {
				Base::goods_on_base -= load;
			}
			else {
				Base::goods_on_base -= max_load;
			}
			petrol_amount = tank_amount;
			return true;
		}
		return false;
	}
};

int main() {
	Bus bus(20, 50, 50.0, 100.0);
	Truck truck(10.0, 20.0, 80.0, 150.0);

	bus.arrive();
	truck.arrive();

	cout << "People on base: " << Base::people_on_base << "\n";
	cout << "Vehicles on base: " << Base::vehicles_on_base << "\n";
	cout << "Petrol on base: " << Base::petrol_on_base << "\n";
	cout << "Goods on base: " << Base::goods_on_base << "\n";

	bool bus_left = bus.leave();
	bool truck_left = truck.leave();

	if (bus_left) {
		cout << "Bus successfully left the base.\n";
	}
	else {
		cout << "Bus couldn't leave the base.\n";
	}

	if (truck_left) {
		cout << "Truck successfully left the base.\n";
	}
	else {
		cout << "Truck couldn't leave the base.\n";
	}

	cout << "People on base: " << Base::people_on_base << "\n";
	cout << "Vehicles on base: " << Base::vehicles_on_base << "\n";
	cout << "Petrol on base: " << Base::petrol_on_base << "\n";
	cout << "Goods on base: " << Base::goods_on_base << "\n";

}