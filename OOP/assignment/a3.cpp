#include <iostream>

using namespace std;
class Publication{
	public:
		string title;
		float price;
	
		Publication(string title, float price) {
			this->title = title;
			this->price = price;
		}
};

class Book : public Publication {
	public :
		int page_count;
		
		Book(string title, float price, int page_count): Publication(title, price) {
			this->page_count = page_count;
		}
		
		void print_data() {
			cout << string(20,'-') << endl;
			cout << "title = " << title << endl;
			cout << "price = " << price << endl;
			cout << "page Count = " << page_count << endl;
			cout << string(20,'-') << endl;
		}
		
			
};

class Tape : public Publication {
	public :
		float playing_time;
		
		Tape(string title, float price, float playing_time): Publication(title, price) {
			this->playing_time = playing_time;
		}
		
		void print_data() {
			cout << string(20,'-') << endl;
			cout << "title = " << title << endl;
			cout << "price = " << price << endl;
			cout << "playing Time = " << playing_time << endl;
			cout << string(20,'-') << endl;
		}
};


int main() {
	Book b1("MY_BOOK",12,100);
	cout << "book stuff " << endl;
	
	b1.print_data();
	
	Tape t1("MY_TAPE",32,30);
	cout << "tape stuff " << endl;
	
	t1.print_data();
	
	return 0;
}