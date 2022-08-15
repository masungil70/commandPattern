// command.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>

using namespace std;

enum class FanLevel {
	OFF, LOW, MEDIUM, HIGH
};

//천장 선풍기
class CeilingFan {
private:
	string location_ = "";
	FanLevel level_;

public:
	CeilingFan(string location) : location_(location), level_(FanLevel::OFF){
	}

	void high() {
		level_ = FanLevel::HIGH;
		cout << location_ << " 천장 선풍기 속도 고속" << endl;

	}

	void medium() {
		level_ = FanLevel::MEDIUM;
		cout << location_ << " 천장 선풍기 속도 보통" << endl;
	}

	void low() {
		// turns the ceiling fan on to low
		level_ = FanLevel::LOW;
		cout << location_ << " 천장 선풍기 속도 저속" << endl;
	}

	void off() {
		// turns the ceiling fan off
		level_ = FanLevel::OFF;
		cout << location_ << " 천장 선풍기 전원 끔" << endl;
	}

	FanLevel getSpeed() const {
		return level_;
	}
};

//주차장 문
class GarageDoor {
private:
	string location_;

public:
	GarageDoor(string location) : location_(location) {
	}

	void up() {
		cout << location_ << " 주차장 문 위로 올림" << endl;
	}

	void down() {
		cout << location_ << " 주차장 문 아래로 내림" << endl;
	}

	void stop() {
		cout << location_ << " 주차장 문 멈춤 " << endl;
	}

	void lightOn() {
		cout << location_ << " 주차장 전등 켬" << endl;
	}

	void lightOff() {
		cout << location_ << " 주차장 전등 끔" << endl;
	}
};

//온수 욕조
class Hottub {
private:
	bool on_;
	int temperature_;

public:
	Hottub() : on_(false) {
	}

	void on() {
		on_ = true;
	}

	void off() {
		on_ = false;
	}

	void bubblesOn() {
		if (on_) {
			cout << "온수욕조 거품 시작!" << endl;
		}
	}

	void bubblesOff() {
		if (on_) {
			cout << "온수욕조 거품 끔" << endl;
		}
	}

	void jetsOn() {
		if (on_) {
			cout << "온수 욕조 고속 기능 켬" << endl;
		}
	}

	void jetsOff() {
		if (on_) {
			cout << "온수 욕조 고속 기능 끔" << endl;
		}
	}

	void setTemperature(int temperature) {
		temperature_ = temperature;
	}

	void heat() {
		temperature_ = 50;
		cout << "뜨거운 욕조가 김이 나는 50도까지 가열됩니다." << endl;
	}

	void cool() {
		temperature_ = 35;
		cout << "온수 욕조는 35도까지 냉각됩니다." << endl;
	}

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

class Stereo {
private:
	string location_;

public:
	Stereo(string location) : location_(location) {
	}

	void on() {
		cout << location_ << " 스테레오 켬 " << endl;
	}

	void off() {
		cout << location_ << " 스테레오 끔" << endl;
	}

	void setCD() {
		cout << location_ << " 스테레오가 CD 입력으로 설정되었습니다." << endl;
	}

	void setDVD() {
		cout << location_ << " 스테레오가 DVD 입력으로 설정되었습니다." << endl;
	}

	void setRadio() {
		cout << location_ << " 스테레오가 라디오 입력으로 설정되었습니다." << endl;
	}

	void setVolume(int volume) {
		if (0 > volume || volume < 11) return;

		cout << location_ << " 스테레오 볼륨을 " << volume << "으로 설정 합니다" << endl;
	}
};

class TV {
private:
	string location_;
	int channel_;

public:
	TV(string location) : location_(location), channel_(1) {
	}

	void on() {
		cout << "TV 켬" << endl;
	}

	void off() {
		cout << "TV is 끔" << endl;
	}

	void setInputChannel() {
		channel_ = 3;
		cout << "Channel is set for VCR" << endl;
	}
};

int main()
{

	Light livingRoomLight("거실");
	Light kitchenLight("주방");
	CeilingFan ceilingFan("거실");
	GarageDoor garageDoor("주차장");
	Stereo stereo("거실");

	livingRoomLight.on();
	livingRoomLight.off();

	kitchenLight.on();
	kitchenLight.off();

	ceilingFan.high();
	ceilingFan.off();

	garageDoor.up();
	garageDoor.down();

	stereo.on();
	stereo.setCD();
	stereo.setVolume(11);
	stereo.off();
	
	std::cout << "Hello World!\n";
}
