#include<iostream>
#include<cstring>


struct char_wrapper{
	char* str;
	mutable int ref_count;
	char_wrapper(const char* str_in): str(new char), ref_count(0){
		std::strcpy(str, str_in);	
	};
	char_wrapper(const char_wrapper &str_data_in): str(new char), ref_count(0){
		std::strcpy(str, str_data_in.str);
	}
};


class String{
	public:
		String(const char* str_in): str_data(new char_wrapper(str_in)){};
		String(const String& string_in): str_data(string_in.str_data){
			ref_inc();
		};
		String &operator=(const String &rhs){
			if(this == &rhs){
				return *this;
			}
			ref_dec();
			str_data = new char_wrapper(*rhs.str_data);
			return *this;	
		};
		char &operator[](int pos){
			ref_dec();
			str_data = new char_wrapper(*str_data);
			return *(str_data->str+pos);
		}

		~String(){
			ref_dec();
		}
		std::ostream& operator<<(std::ostream& outs){
			return outs<<this->str_data->str;
		};

	private:
		mutable char_wrapper* str_data;
		void ref_inc(){
			str_data->ref_count++;
		}
		void ref_dec(){
			if(str_data->ref_count == 0){
				delete str_data;
				return;
			}
			str_data->ref_count--;
		}
};

int main(){
	std::cout<<"begin";
	String a("hello");
	std::cout<<"world";

}
