// command.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>

using namespace std;

/*
식당에 주문의 진행 절차 

1. 고객이 종업원에게 주문을 한다  
	createrOrder()
2. 종업원은 주문을 받아서 카운터에 갖다 주고는"주문 받아요!"하고 얘기한다 
	takeOrder()
	orderUp()
3. 주방장이 주문대로 음식을 주문합니다 
	makeBurger(),
	makeShake()
4. 음식을 전달한다 
	
*/

class ICommand {
public:
	virtual void execute() = 0;
};

class Light {
private:
	string location_ = "";

public:
	Light(string location) : location_(location) {
	}

	void on() {
		cout << location_ << " 전등 켬" << endl;
	}

	void off() {
		cout << location_ << " 전등 끔" << endl;
	}
};

class LightOnCommand : public ICommand {
private:
	Light& light_;

public:
	LightOnCommand(Light& light) : light_(light) {

	}

	virtual void execute() override {
		light_.on();
	}
};


class SimpleRemoteControl {
private:
	ICommand* pCommand_;

public:
	void setCommand(ICommand* pCommand) {
		pCommand_ = pCommand;
	}

	void buttonWasPressed() {
		if (!pCommand_) return;

		pCommand_->execute();
	}
};



int main()
{
	Light livingRoomLight("거실");//요청을 받아 처리할 리서버 객체를 생성함 
	LightOnCommand lightOn(livingRoomLight);//command 객체 생성 
	SimpleRemoteControl remote; //invoker 객체 객체 생성 

	remote.setCommand(&lightOn); //command 객체를 invoker 객체에 전달 
	remote.buttonWasPressed();

	
	std::cout << "Hello World!\n";
}
