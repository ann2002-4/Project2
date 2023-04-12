#pragma once
#include <string>

using namespace std;

class User {
	const string login_;
	string password_;
	string name_;

public:
	User(const string& login, const string& password, const string& name, double& time)
		:login_(login), password_(password), name_(name) {
	}
	const  string& GetUserLogin()const {
		return login_;
	}

	const  string& GetUserPassword()const {
		return password_;
	}

	void SetUserPassword(const  string& password) {
		password_ = password;
	}

	const string& GetUserName() const {
		return name_;
	}

	void SetUserName(const string& name) {
		name_ = name;
	}
};