// command.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class FanLevel {
	OFF, LOW, MEDIUM, HIGH
};

class ICommand {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

//명령이 없는 클래스 
class NoCommand : public ICommand {
public:
	static NoCommand emptyCommand;
public:
	void execute() { }
	void undo() { }
};

NoCommand NoCommand::emptyCommand;

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

class CeilingFanOffCommand : public ICommand {
private:
	CeilingFan& ceilingFan_;
	FanLevel prevSpeed_;

public:
	CeilingFanOffCommand(CeilingFan& ceilingFan) : ceilingFan_(ceilingFan) {
	}
	
	void execute() {
		prevSpeed_ = ceilingFan_.getSpeed();
		ceilingFan_.off();
	}

	void undo() {
		switch (prevSpeed_) {
		case FanLevel::HIGH: 	ceilingFan_.high(); break;
		case FanLevel::MEDIUM:  ceilingFan_.medium(); break;
		case FanLevel::LOW: 	ceilingFan_.low(); break;
		default: 				ceilingFan_.off(); break;
		}
	}
};

class CeilingFanOnCommand : public ICommand {
private:
	CeilingFan& ceilingFan_;
	FanLevel prevSpeed_;

public: 
	CeilingFanOnCommand(CeilingFan& ceilingFan) : ceilingFan_(ceilingFan) {
	}

	void execute() {
		ceilingFan_.high();
	}

	void undo() {
		switch (prevSpeed_) {
		case FanLevel::HIGH: 	ceilingFan_.high(); break;
		case FanLevel::MEDIUM:  ceilingFan_.medium(); break;
		case FanLevel::LOW: 	ceilingFan_.low(); break;
		default: 				ceilingFan_.off(); break;
		}
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

class GarageDoorDownCommand : public ICommand {
private:
	GarageDoor& garageDoor_;

public:
	GarageDoorDownCommand(GarageDoor& garageDoor) : garageDoor_(garageDoor) {
	}

	void execute() {
		garageDoor_.down();
	}

	void undo() {
		garageDoor_.up();
	}
};

class GarageDoorUpCommand : public ICommand {
private:
	GarageDoor& garageDoor_;

public:
	GarageDoorUpCommand(GarageDoor& garageDoor) : garageDoor_(garageDoor) {
	}

	void execute() {
		garageDoor_.up();
	}

	void undo() {
		garageDoor_.down();
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

class HottubOffCommand : public ICommand {
private:
	Hottub& hottub_;

public:
	HottubOffCommand(Hottub& hottub) : hottub_(hottub) {
	}

	void execute() {
		hottub_.cool();
		hottub_.off();
	}

	void undo() {
		hottub_.on();
	}
};

class HottubOnCommand : public ICommand {
private:
	Hottub& hottub_;

public:
	HottubOnCommand(Hottub& hottub) : hottub_(hottub) {
	}

	void execute() {
		hottub_.on();
		hottub_.heat();
		hottub_.bubblesOn();
	}

	void undo() {
		hottub_.off();
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

class LightOffCommand : public ICommand {
private:
	Light& light_;

public:
	LightOffCommand(Light& light) : light_(light) {
	}

	void execute() {
		light_.off();
	}

	void undo() {
		light_.on();
	}
};

class LightOnCommand : public ICommand {
private:
	Light& light_;

public:
	LightOnCommand(Light& light) : light_(light) {
	}

	void execute() {
		light_.on();
	}

	void undo() {
		light_.off();
	}
};

class LivingroomLightOffCommand : public ICommand {
private:
	Light& light_;

public:
	LivingroomLightOffCommand(Light& light) : light_(light) {
	}

	void execute() {
		light_.off();
	}

	void undo() {
		light_.on();
	}
};

class LivingroomLightOnCommand : public ICommand {
private:
	Light& light_;

public:
	LivingroomLightOnCommand(Light& light) : light_(light) {
	}

	void execute() {
		light_.on();
	}

	void undo() {
		light_.off();
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

class StereoOffCommand : public ICommand {
private:
	Stereo& stereo_;

public:
	StereoOffCommand(Stereo& stereo) : stereo_(stereo) {
	}

	void execute() {
		stereo_.off();
	}

	void undo() {
		stereo_.on();
	}
};

class StereoOnWithCDCommand : public ICommand {
private:
	Stereo& stereo_;

public:
	StereoOnWithCDCommand(Stereo& stereo) : stereo_(stereo) {
	}

	void execute() {
		stereo_.on();
		stereo_.setCD();
		stereo_.setVolume(11);
	}

	void undo() {
		stereo_.off();
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

class TVOffCommand : public ICommand {
private:
	TV& tv_;

public:
	TVOffCommand(TV& tv) : tv_(tv) {
	}

	void execute() {
		tv_.off();
	}

	void undo() {
		tv_.on();
	}
};

class TVOnCommand : public ICommand {
private:
	TV& tv_;

public:
	TVOnCommand(TV& tv) : tv_(tv) {
	}

	void execute() {
		tv_.on();
		tv_.setInputChannel();
	}

	void undo() {
		tv_.off();
	}
};


class MacroCommand : public ICommand {
private:
	initializer_list<ICommand*>& commands_;

public:
	MacroCommand(initializer_list<ICommand*>& commands) : commands_(commands) {
	}

	void execute() {
		for (auto& command : commands_) {
			command->execute();
		}
	}

	/**
	 * NOTE:  these commands have to be done backwards to ensure
	 * proper undo functionality
	 */
	void undo() {
		for (auto rit = commands_.end(); rit != commands_.begin(); rit--) {
			(*rit)->undo();
		}
	}
};


//
// This is the invoker
//
class RemoteControl {
private:
	vector<ICommand*> onCommands_;
	vector<ICommand*> offCommands_;
	ICommand* undoCommand;
public:
	RemoteControl() : undoCommand(nullptr) {
		for (int i = 0; i < 7; i++) {
			onCommands_.push_back(&NoCommand::emptyCommand);
			offCommands_.push_back(&NoCommand::emptyCommand);
		}
	}

	void setCommand(int slot, ICommand* onCommand, ICommand* offCommand) {
		onCommands_[slot] = onCommand;
		offCommands_[slot] = offCommand;
	}

	void onButtonWasPushed(int slot) {
		onCommands_[slot]->execute();
		undoCommand = offCommands_[slot];
	}

	void offButtonWasPushed(int slot) {
		offCommands_[slot]->execute();
		undoCommand = offCommands_[slot];
	}

	void undoButtonWasPushed(int slot) {
		if (undoCommand) {
			undoCommand->undo();
		}
	}
	string toString() {
		stringstream out;
		out << "\n------ Remote Control -------\n";
		int i = 0;
		for (auto& pOnCommand : onCommands_) {
			out << "[slot " << i << "] " << typeid(onCommands_[i]).name()
				<< "    " << typeid(offCommands_[i]).name() << "\n";
			i++;
		}
		out << "[undo] " << typeid(offCommands_[i]).name() << "\n";

		return out.str();
	}
};

//선풍기 테스트 
int main()
{
	RemoteControl remoteControl;

	Light light("거실");
	TV tv("거실");
	Stereo stereo("거실");
	Hottub hottub;

	LightOnCommand lightOn(light);
	StereoOnWithCDCommand stereoOn(stereo);
	TVOnCommand tvOn(tv);
	HottubOnCommand hottubOn(hottub);
	LightOffCommand lightOff(light);
	StereoOffCommand stereoOff(stereo);
	TVOffCommand tvOff(tv);
	HottubOffCommand hottubOff(hottub);

	initializer_list<ICommand*> onCommands{ &lightOn, &stereoOn, &tvOn, &hottubOn };
	initializer_list<ICommand*> offCommands{ &lightOff, &stereoOff, &tvOff, &hottubOff };
	MacroCommand partyOnMacro(onCommands);
	MacroCommand partyOffMacro(offCommands);

	remoteControl.setCommand(0, &partyOnMacro, &partyOffMacro);

	cout<< remoteControl.toString();
	cout << "\n\n--- Pushing Macro On---" << endl;
	remoteControl.onButtonWasPushed(0);
	cout << "\n\n--- Pushing Macro Off---" << endl;
	remoteControl.offButtonWasPushed(0);

	return 0;
}
