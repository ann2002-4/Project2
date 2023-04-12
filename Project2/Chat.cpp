#include<iostream>
#include <string>
#include "Chat.h"

void Chat::start() {

	setlocale(LC_ALL, "Russian");

	isChatWork_ = true;
}

shared_ptr<User>Chat::getUserByLogin(const string& login) const {
	for (auto& user : userList_) {
		if (login == user.GetUserLogin())
			return  make_shared<User>(user);
	}
	return nullptr;
}

shared_ptr<User>Chat::getUserByName(const string& name)const {
	for (auto& user : userList_) {
		if (name == user.GetUserName())
			return  make_shared<User>(user);
	}
	return nullptr;
}

void Chat::showLoginMenu() {
	currentUser_ = nullptr;
	char operation;
	do {
		cout << "Выберите нужное действие и введите цифру" << endl << "1 - Авторизация" << endl << "2 - Регистрация" << endl << "0 - Завершение работы" << endl;
		cin >> operation;
		switch (operation) {
		case '1':
			login();
			break;
		case '2':
			try {
				signUp();
			}
			catch (const  exception& e) {
				cout << e.what() << endl;
			}
			break;
		case '0':
			isChatWork_ = false;
			break;
		default:
			cout << "1 or 2..." << endl;
			break;

		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::login() {
	string login, password;
	char operation;

	do {
		cout << "Логин:";
		cin >> login;
		cout << "Пароль:";
		cin >> password;

		currentUser_ = getUserByLogin(login);
		if (currentUser_ == nullptr || (password != currentUser_->GetUserPassword()))
		{
			currentUser_ = nullptr;
			cout << "Нерный логин или пароль" << endl;
			cout << "Нажмите 0 для выхода или любую клавишу для повтора";
			cin >> operation;
			if (operation == '0')
				break;
		}
	} while (!currentUser_);
}

void Chat::showChat()const {
	string from;
	string to;
	cout << " ЧАТ " << endl;
	for (auto& mess : MsgList_) {
		if (currentUser_->GetUserLogin() == mess.GetFrom() || currentUser_->GetUserLogin() == mess.GetTo() || mess.GetTo() == "all") {
			from = (currentUser_->GetUserLogin() == mess.GetFrom()) ? " от меня " : getUserByLogin(mess.GetFrom())->GetUserName();
			if (mess.GetTo() == "all") {
				to = "all";
			}
			else {
				to = (currentUser_->GetUserLogin() == mess.GetTo()) ? " для меня " : getUserByLogin(mess.GetTo())->GetUserName();
			}
			cout << "Сообщение " << from << " для " << to << endl;
			cout << "Сообщение:" << mess.Gettxt() << endl;
		}
	}
}

void Chat::signUp() {
	string login, password, name;
	double time;
	cout << "Логин: ";
	cin >> login;
	cout << "Пароль: ";
	cin >> password;
	cout << "Имя: ";
	cin >> name;
	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}
	if (getUserByName(name) || name == "all") {
		throw UserNameExp();

	}

	User user = User(login, password, name, time);
	userList_.push_back(user);
	currentUser_ = make_shared<User>(user);
}

void Chat::showUserMenu() {
	char operation;
	cout << "Здравствуйте, " << currentUser_->GetUserName() << endl;
	while (currentUser_) {
		cout << "Выберите нужное действие и введите цифру" << endl << "1 - Просмотр чата" << endl << "2 - Написать сообщение" << endl << "3 - Выход" << endl << "0 - Выход из аккаунта";
		cout << endl;
		cin >> operation;
		switch (operation) {
		case '1':
			showChat();
			break;
		case '2':
			addMsg();
			break;
		case '3':
			showAllUsersName();
			break;
		case'0':
			currentUser_ = nullptr;
			break;
		default:
			cout << "Неверный ввод" << endl;
			break;
		}
	}
}

void Chat::addMsg() {
	string to, txt;

	cout << "Сообщение для (имя или для всех (введите all))";
	cin >> to;
	cout << "Сообщение: ";
	cin.ignore();
	getline(cin, txt);
	if (!(to == "all" || getUserByName(to))) {
		cout << " Ошибка отправки " << to << endl;
		return;
	}
	if (to == "all")
		MsgList_.push_back(Msg{ currentUser_->GetUserLogin(),"all",txt });
	else
		MsgList_.push_back(Msg{ currentUser_->GetUserLogin(),getUserByName(to)->GetUserLogin(),txt });
}

void Chat::showAllUsersName()const {
	cout << " ПОЛЬЗОВАТЕЛЬ " << endl;
	for (auto& user : userList_) {
		cout << user.GetUserName();
		if (currentUser_->GetUserLogin() == user.GetUserLogin())
			cout << endl;
	}
}