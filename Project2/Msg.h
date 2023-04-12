#pragma once
#include "User.h"

class Msg {
	const  string from_;
	const  string to_;
	const  string txt_;

public:
	Msg(const  string& from, const  string to, const  string txt)
		:from_(from), to_(to), txt_(txt) {
	}
	const  string& GetFrom()const {
		return from_;
	}
	const  string& GetTo()const {
		return to_;
	}
	const  string& Gettxt()const {
		return txt_;
	}
};