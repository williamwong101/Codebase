#include<iostream>
#include<cstring>


struct char_wrapper{
	char* str;
	mutable int ref_count;
	// construct from c_string: initialize with ref = 0
	char_wrapper(const char* str_in): str(new char), ref_count(0){
		std::strcpy(str, str_in);	
	};
	// copy construct, initialize new instance with ref = 0
	char_wrapper(const char_wrapper &str_data_in): str(new char), ref_count(0){
		std::strcpy(str, str_data_in.str);
	}
	~char_wrapper(){
		delete str;
	}
};


class String{
	public:
		// construct with c_string
		String(const char* str_in): str_data(new char_wrapper(str_in)){};

		// copy construct
		String(const String& string_in): str_data(string_in.str_data){
			ref_inc();
		};
		
		// copy assignment
		String &operator=(const String &rhs){
			if(this == &rhs){
				return *this;
			}
			ref_dec();
			str_data = rhs.str_data;
			ref_inc();
			return *this;	
		};
		
		// indexing operator
		char &operator[](int pos){
			ref_dec();
			str_data = new char_wrapper(*str_data);
			return *(str_data->str+pos);
		}

		// destructor
		~String(){
			ref_dec();
		}
		

		friend std::ostream& operator<<(std::ostream& outs, String &rhs){
			return outs<<rhs.str_data->str;
		};

		char_wrapper* operator&(){
			return str_data;
		}
	private:
		// actual data for the string, wrapper with 
		// ref_count
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
	std::cout<<"begin"<<std::endl;
	String a("hello");
	std::cout<<"Original A:"<<std::endl;
	std::cout<<a<<"\t"<<&a<<std::endl;
	String b(a);
	std::cout<<"Copy construct B:"<<std::endl;
	std::cout<<b<<"\t"<<&b<<std::endl;
	b[2] = 'x';
	std::cout<<"Changed B:"<<std::endl;
	std::cout<<b<<"\t"<<&b<<std::endl;
	String c = a;
	std::cout<<"Copy assign C:"<<std::endl;
	std::cout<<c<<"\t"<<&c<<std::endl;
	c[1] = 'x';
	std::cout<<"Changed C:"<<std::endl;
	std::cout<<c<<"\t"<<&c<<std::endl;
	std::cout<<"world"<<std::endl;

}

