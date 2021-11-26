#pragma once
#pragma execution_character_set("utf-8")
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
static vector<string> family_name_list = {};
static vector<string> man_name_list = {};
static vector<string> woman_name_list = {};
const string file_path = "data/name_ansi.txt";

static void load_name_data_naive() {
	string f_name_data = "이스턴갈라 브리타 사우전포드 레이크갈라 리버 우드 스탠토이토 웨스턴빌른 웨스턴발란 루고 라도가 마일 루드리버 브룩 모어 쇼 턴 버리 콧 힐 웰 워스 필즈 카펜터 베이커 테일러 밀러 피셔 바그너 스미스 놀카 리미야 톤카 밀카 말랴 모비야 무하카 민티아 바네야 넨카 반자카 베닐카 베니라 부리카 부리아 브라피카 브라피아 블랑카 블라야 사먀나 사먀카 사우사 사우카 샤로나 샤빌카 샤카 세나파 아바카 아보아 아포라 아보카 이라야 자카 제이사 주샤 주나 체비사 체카 카도나 카로사 카로나 카비아 카이나 카챠 칸카나 케이카 케프사 코오라 코쿠사 콜디아 쿠키아 쿤카 쿠냐 쿠쿠야 캐마 키비사 키주사 킬디아 킬드카 타타사 테이타 토마카 토마야 토디아 토드사 토브카 튜브카 파비카 파비사 파뱌 파일카 피마아 피마사 피에르사 피에르카 피쿠아 피피카 페리사 페리카 하무야 하비카 햐카 헤데나 헤비야 헤비사 후카 히치아 그리에사 나디사 나이냐 나파아 다야카 도나카 도너사 디와 라스티카 라스티야 라이아사 라일라사 루베사 로디아 룰카 리마사 리푸사 메구카 메기아 무니사 무하카 샴파 이아사";
	string m_name_data = "가디 가론 가안 게일 겔 겔드 그리엣 구그 나디 나인 나파 네일 다이야 다후 데닐 데닛 데런 데리 데이엘 데이즈 데인 도날드 도넛 도리 디오 라덴 라이델 라이얀 라이트 라토 레이널드 로무 루벤 로디 로벨 로빈 로카 로토 루디 루아스 루이놀 리마 마톤 마이트 마일 마푸 밀 밀크 만고 말리 멀린 메론 메루 멜 모브 몽 몽몽 무니 무하 민트 바넨 바론 바비 바인 반자 베닐 벤 부리 브라피 블랑 사먄 사우스 샤론 샤빌 샤크 세나 세닐 세바 세앙 세이비 세피 솔라 아보 아폴 에루일 우유 유카 위간 위올드 이라이 이블 자크 잔잔 쟝 제이슨 주스 준 체빌 체크 츄브 카돈 카론 카비 카벨 카인 카일 카치 칸칸 케이프 케인 케일 케프 코올 코쿠 콜드 쿠키 쿤 쿠쿠 캐모 키비 키주 킬드 타이프 타타 테이트 토마 토드 토브 튜브 파비 파인 파일 피마 피엘 피쿠 피픽 페리 하무 하비 함바그 햐크 헤덴 헤비 헤피 헨델 헨리 헨지 화이트 후크 후푸 히치";
	string w_name_data = "그리에 나디 나인 나파 네일 다이야 다후 데리 데이엘 데이즈 도넛 도리 디오 라스타 라이아 라일라 루벤 로디 로벨 로빈 로즈마리 로카 루디 루루 리마 리푸 마냐 마나 마론 마뤼 밀카 밀크 만고 멀린 메구 메론 메루 메디아 모브 몽몽 몽블랑 무니 무라 무아나 무하 미유 미치 민트 민티아 바냐 바나 바넨 바니엘 바닐 바닐린 바론 바바로아 바반나 바비 베이디 부리 블랑 블린 비바 비비아 비비안 비앙카 사디아 사먄 사이라 사키아 샤샤 샤론 샤빌 샤크 샴푸 세나 세앙 세이비 세피 솔라 오요나 올리브 우유 유나 유카 이라이 이블 이아 잔잔 제이미 주스 준 체이사 체키나 카론 카리엘 카비 카이사 카일 카티나 카푸리 케일 쿠리마 쿠키 코나 코마 코코나 콜라 쿠쿠 캐모 키비 키주 타타 테이트 토마 파비엔 파인 파일 포포리 포리 폴라 푸리 프리에 플로라 플로린 피마 피엘 피쿠 필리아 하니하 햐크 화이트 후크 후푸 히치";

	string word_buffer;

	std::stringstream family_line(f_name_data);

	while (getline(family_line, word_buffer, ' ')) {
		family_name_list.push_back(word_buffer);
	}

	std::stringstream m_name_line(m_name_data);
	while (getline(m_name_line, word_buffer, ' ')) {
		man_name_list.push_back(word_buffer);
	}

	std::stringstream f_name_line(w_name_data);
	while (getline(f_name_line, word_buffer, ' ')) {
		woman_name_list.push_back(word_buffer);
	}

}

static void load_name_data() {
	ifstream f(file_path);
	string line_buffer;
	string word_buffer;

	if (f.fail()) {
		cerr << "[NameList]File not found: " << file_path << endl;
		exit(100);
	}

	getline(f, line_buffer);

	std::stringstream family_line(line_buffer);

	while (getline(family_line, word_buffer, ' ')) {
		family_name_list.push_back(word_buffer);
	}

	getline(f, line_buffer);

	std::stringstream m_name_line(line_buffer);
	while (getline(m_name_line, word_buffer, ' ')) {
		man_name_list.push_back(word_buffer);
	}

	getline(f, line_buffer);

	std::stringstream f_name_line(line_buffer);
	while (getline(f_name_line, word_buffer, ' ')) {
		woman_name_list.push_back(word_buffer);
	}

	f.close();
	/*
	for (auto name : family_name_list) {
		cout<<name<<" ";
	}
	printf("\n\n");

	for (auto name : man_name_list) {
		cout<<name<<" ";
	}
	printf("\n\n");

	for (auto name : woman_name_list) {
		cout<<name<<" ";
	}
	printf("\n\n");
	*/
}