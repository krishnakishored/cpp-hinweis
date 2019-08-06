#include<iostream>
#include<string>
#include<exception>

using std::string;
using std::cout;
using std::cin;

//Exception class

// class Exception {
// public:
//    Exception(const string& msg) : msg_(msg) {}
// ~Exception() {}
// string getMessage() const {return(msg_);} private:
//    string msg_;
// };

class BadLengthException : public std::exception
{
    private:
        int length_;
        string buffer_;
    public:
        BadLengthException(int length);
        const char * what () const noexcept
        { 
            return buffer_.c_str();
        }
};

BadLengthException::BadLengthException(int length)
{
    length_ = length;
    buffer_ = std::to_string(length_);
}



bool checkUsername(string username) {
	bool isValid = true;
	int n = username.length();
	if(n < 5) {
		throw BadLengthException(n);
	}
	for(int i = 0; i < n-1; i++) {
		if(username[i] == 'w' && username[i+1] == 'w') {
			isValid = false;
		}
	}
	return isValid;
}

int main_BadLengthException()
{
	int T; cin >> T;
	while(T--) {
		string username;
		cin >> username;
		try {
			bool isValid = checkUsername(username);
			if(isValid) {
				cout << "Valid" << '\n';
			} else {
				cout << "Invalid" << '\n';
			}
		} catch (BadLengthException e) {
			cout << "Too short: " << e.what() << '\n';
		}
	}
	return 0;
}

int main(){

    main_BadLengthException();
    return 0;
}