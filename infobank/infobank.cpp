#include <iostream>
#include <string>

using namespace std;

class BaseChannel {//공통점을 묶어서 부모클래스를 만들었다
public:
	int ID = 0;
	string Name = "";
	string broadCastName = "";

public:

	BaseChannel()
		:ID(0)
		, Name("")
		, broadCastName("")
	{
		//생성자와 소멸자 생성자 나올때 변수를 초기화하도록 하여 오류를 제거했다
		cout << "ChannelBase 생성자 " << endl;
	}
	BaseChannel(int ch, string chName="", string broadName="")
		:ID(ch)
		, Name(chName)
		, broadCastName(broadName)
	{
		//생성자와 소멸자 생성자 나올때 변수를 초기화하도록 하여 오류를 제거했다
		cout << "ChannelBase 생성자 " << endl;
	}
	virtual ~BaseChannel() {
		cout << "ChannelBase 소멸자 " << endl;
	}

	virtual void inputChannelInfo()
	{
		//가상함수 객체에 데이터를 집어넣기위해 만들었음 상속받은 클래스에서 같은이름의 함수를 쓰게될것이다
		cout << "Enter channelId: ";
		cin >> ID;
		cout << "Enter chanelName: ";
		cin >> Name;
		cout << "Enter broadCastName: ";
		cin >> broadCastName;
	}

	virtual void outputChannelInfo()
	{
		//데이터를 출력하기 위한 용도의 함수다 가상함수
		cout << "channelId: " << ID << " - chanelName: " << Name << " - broadCastName: " << broadCastName << endl;
	}
};

class RadioChannel : public BaseChannel {//부모클래스로 부터 상속받음 자식 클래스의 기능이 더해지고 함수는 오버라이딩된다
private:
	int freqency=0;
public:


	RadioChannel()
		: BaseChannel(0,"","")
		, freqency(0)
	{
		//생성자와 동시에 초기화된다
		cout << "RadioChanel 생성자 " << endl;
	}
	RadioChannel(int ch, string chName = "", string broadName = "", int freq=0)
		: BaseChannel(ch, chName, broadName)
		, freqency(freq)
	{
		//생성자와 동시에 초기화된다
		cout << "RadioChanel 생성자 " << endl;
	}
	~RadioChannel() {
		cout << "RadioChanel 소멸자 " << endl;
	}

	void inputChannelInfo() override
	{
		//데이터를 집어넣기 위해서 만든함수 오버라이딩된다 부모의 함수가 실행되고 자식의 함수가 실행되는거 맞겠죠?
		BaseChannel::inputChannelInfo();
		cout << "Enter freqency: ";
		cin >> freqency;
	}

	void outputChannelInfo() override {//데이터를 출력하는 함수 오버라이딩된다
		BaseChannel::outputChannelInfo();
		cout << "freqency: " << freqency << endl;
	}
	int GetFrequency() { return freqency; }
};

class TVChannel : public RadioChannel {//부모클래스로 부터 상속받음
private:
	int channelNumber;
	string broadCastType;
public:

	TVChannel()
		:RadioChannel()
		, channelNumber(0)
		, broadCastType("")
	{
		cout << "TvChanel 생성자 " << endl;
	}

	TVChannel(int id, string name = "", int channel=0, string broadName = "", string broadCast = "")
		:RadioChannel(id, name, broadName)
		, channelNumber(channel)
		, broadCastType(broadCast)
	{
		cout << "TvChanel 생성자 " << endl;
	}

	~TVChannel() {
		cout << "TvChanel 소멸자 " << endl;
	}

	void inputChannelInfo() override {
		RadioChannel::inputChannelInfo();
		cout << "Enter chanelNumber: ";
		cin >> channelNumber;
		cout << "Enter broadCastType: ";
		cin >> broadCastType;
	}

	void outputChannelInfo() override {
		RadioChannel::outputChannelInfo();
		cout << "freqency: " << GetFrequency() << " - chanelNumber: " << channelNumber << " - broadCastType: " << broadCastType << endl;
	}
};

class TVRadioChannel : public TVChannel {
	//추가할것이 없다
public:
	TVRadioChannel() {

		cout << "TVRadioChanel 생성자 " << endl;
	}
	TVRadioChannel(int id, string name = "", int channel = 0, string broadName = "")
		:TVChannel(id,name,0, broadName)
	{

		cout << "TVRadioChanel 생성자 " << endl;
	}
	~TVRadioChannel() {
		cout << "TVRadioChanel 소멸자 " << endl;
	}
};

class ChannelManager {//채널을 관리하는 클래스
public:
	ChannelManager() {

		cout << "ChannelManager 생성자 " << endl;
	}
	~ChannelManager() {
		cout << "ChannelManager 소멸자 " << endl;
	}

	template <typename T>
	void bubbleSortChannels(T *channels, int size) {//객체와 어레이사이즈를 매개변수로 받는다
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (channels[j]->ID > channels[j + 1]->ID) {
					swap(channels[j], channels[j + 1]);
				}
			}
		}
	}

	template <typename T>
	void bubbleSortChannelsByName(T channels[], int size) {
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (channels[j]->Name > channels[j + 1]->Name) {
					swap(channels[j], channels[j + 1]);
				}
			}
		}
	}

	template <typename T>
	void displayChannels(T channels[], int size) {
		for (int i = 0; i < size; i++) {
			cout << "객체 " << i + 1 << " - ";
			channels[i]->outputChannelInfo();
		}
	}
};

int main() 
{
	
	BaseChannel* channel[] =
	{
		new RadioChannel(3, "A", "KBS", 100),
		new RadioChannel(2, "B", "SBS", 101),
		new RadioChannel(1, "C", "MBC", 102),
		new TVChannel(5, "E", 7,  "KBS", "지상파"),
		new TVChannel(7, "G", 11,  "MBC", "지상파"),
		new TVChannel(8, "F", 5,  "SBS", "지상파"),
		new TVChannel(6, "H", 15,  "JTBC", "케이블"),
		new TVRadioChannel(3, "I", 0, "MBC"),
		new TVRadioChannel(7, "J", 0, "MBC"),
	};

	int len = sizeof(channel) / sizeof(channel[0]);
	//객체별로 소트하기
	ChannelManager manager;
	cout << "요구사항 1시작" << endl;
	manager.bubbleSortChannels(channel, len);//채널숫자로 소트하기
	cout << "Sorted Radio Channels:" << endl;
	manager.displayChannels(channel, len);

	manager.bubbleSortChannels(channel, len);//채널숫자로 소트하기
	cout << "Sorted TV Channels:" << endl;
	manager.displayChannels(channel, len);

	manager.bubbleSortChannels(channel, len); //채널숫자로 소트하기
	cout << "Sorted TVRadio Channels:" << endl;
	manager.displayChannels(channel, len);


	cout << "요구사항 1끝" << endl;


	cout << "요구사항 2 " << endl;

	//BaseChannel* allChannels = new BaseChannel[9];//동적배열

	//for (int i = 0; i < 3; i++) {//배열에 모든 객체를 집어넣는다
	//	allChannels[i] = radioChannels[i];
	//}
	//for (int i = 0; i < 4; i++) {
	//	allChannels[3 + i] = tvChannels[i];
	//}
	//for (int i = 0; i < 2; i++) {
	//	allChannels[7 + i] = tvRadioChannels[i];
	//}

	manager.bubbleSortChannels(channel, 3);
	cout << "Sorted Channels:" << endl;
	manager.displayChannels(channel, 3);

	manager.bubbleSortChannelsByName(channel, 3);
	cout << "Sorted Channels by Name:" << endl;
	manager.displayChannels(channel, 3);

	cout << "요구사항 2 끝" << endl;

	for (size_t i = 0; i < len; i++)
	{
		delete channel[i];
		channel[i] = nullptr;
	}
	
	return 0;


}
