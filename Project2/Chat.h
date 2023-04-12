#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Msg.h"

struct UserLoginExp :public  exception {
	const char* what() const noexcept override {
		return "Этот логин занят, придумайте другой";
	}
};

struct UserNameExp :public  exception {
	const char* what()const noexcept override {
		return "Это имя занято, придумайте другое";
	}
};

class Chat {
	bool isChatWork_ = false;
	vector<User> userList_;
	vector<Msg> MsgList_;
	shared_ptr<User> currentUser_ = nullptr;

	void login();
	void signUp();
	void showChat()const;
	void showAllUsersName()const;
	void addMsg();

	vector<User>& getAllUsers() {
		return userList_;
	}
	vector<Msg>& getAllMsgs() {
		return MsgList_;
	}
	shared_ptr<User>getUserByLogin(const  string& login)const;
	shared_ptr<User>getUserByName(const  string& name)const;

public:
	void start();
	bool isChatWork()const {
		return isChatWork_;
	}
	shared_ptr<User>getCurrentUser()const {
		return currentUser_;
	}
	void showLoginMenu();
	void showUserMenu();
};
