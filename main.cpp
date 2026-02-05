#include <iostream>
#include <string>
#include <cctype>
#include <vector>

static auto spliteArr(std::string& arr) {
	int static split_num[10] = {};
	int count = 0;
	int start_point = 0;
	int end_point = arr.length();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < end_point; ++j) {
			std::string ward;
			if (std::isspace(arr[j]) != 0) {

				while (start_point < j) {
					ward = ward + arr[start_point];
					start_point++;
				}

				split_num[i] = std::stoi(ward);
				i++;
			}
		}
		std::string ward;
		while (start_point <= end_point) {
			ward = ward + arr[start_point];
			start_point++;
		}
		split_num[i] = std::stoi(ward);
	}
	return split_num;
}

enum Subject{
reading,
literature,
math1,
math2,
english,
history,
physics,
chemical,
biology,
geology
};

class Score {
private:
	int score;
public:
	Score(int score):score(score){}
	
	int getScore() { return score; }
	void setScore(int sc) { score = sc;}
	float getWeight(Subject sub) {
		switch (sub) {
		case reading:
		case literature:
			return score*1.5;
		case math1:
		case math2:
			return score * 2.0;
		case english:
			return score * 1.8;
		case history:
			return score * 2.5;
		case physics:
		case chemical:
		case biology:
		case geology:
			return score * 1.5;
		}
	}
};

class Student {
private:
	int num;
	std::string name;
	std::vector<Score> scores;
public:
	Student(int num, std::string name):num(num),name(name){}
	auto getStudent() const { return std::make_pair(num, name); }
	void setNum(int n) { num = n; }
	void setName(std::string n) { name = n; }
	void addScore(int sc) {scores.push_back(sc);}
	void setScore(int n,int sc) {
		scores[n].setScore(sc);
	}

	int getScore(Subject sub){
		switch (sub) {
		case reading:
			return scores[0].getScore();
		case literature:
			return scores[1].getScore();
		case math1:
			return scores[2].getScore();
		case math2:
			return scores[3].getScore();
		case english:
			return scores[4].getScore();
		case history:
			return scores[5].getScore();
		case physics:
			return scores[6].getScore();
		case chemical:
			return scores[7].getScore();
		case biology:
			return scores[8].getScore();
		case geology:
			return scores[9].getScore();
		}
	}
	float getTotal() {
		float total = scores[0].getWeight(reading) + scores[1].getWeight(literature) + scores[2].getWeight(math1) + scores[3].getWeight(math2) + scores[4].getWeight(english) + scores[5].getWeight(history) + scores[6].getWeight(physics) + scores[7].getWeight(chemical) + scores[8].getWeight(biology) + scores[9].getWeight(geology);
		return total;
	}
};

class Students_info {
	//멤버 변수
private:
	std::vector<Student> students;

public:
	void search_info() {
		bool check = false;
		if (students.size() != 0) {
			for (auto& elem : students) {
				std::cout << elem.getStudent().first << "\t" << elem.getStudent().second;
				std::cout << "\t독서: " << elem.getScore(reading);
				std::cout << "\t문학: " << elem.getScore(literature);
				std::cout << "\t수학1: " << elem.getScore(math1);
				std::cout << "\t수학2: " << elem.getScore(math2);
				std::cout << "\t영어: " << elem.getScore(english);
				std::cout << "\t역사: " << elem.getScore(history);
				std::cout << "\t물리: " << elem.getScore(physics);
				std::cout << "\t화학: " << elem.getScore(chemical);
				std::cout << "\t생명과학: " << elem.getScore(biology);
				std::cout << "\t지구과학: " << elem.getScore(geology);
				std::cout << "\t총점: " << elem.getTotal();
			}
		}
		else { std::cout << "저장된 학생 정보 없음"; }
	}


	void search_part_info() {
		int chk_num;
		std::string chk_name;
		std::cout << "조회하려는 학생의 번호 : ";
		std::cin >> chk_num;
		std::cout << "조회하려는 학생의 이름 : ";
		std::cin >> chk_name;
		bool check = false;

		if (students.size() != 0) {
			for (auto& elem : students) {
				if ((elem.getStudent().first == chk_num) && (elem.getStudent().second == chk_name)) {
					check = true;
					std::cout << elem.getStudent().first << " " << elem.getStudent().second;
					std::cout << "\t독서: " << elem.getScore(reading);
					std::cout << "\t문학: " << elem.getScore(literature);
					std::cout << "\t수학1: " << elem.getScore(math1);
					std::cout << "\t수학2: " << elem.getScore(math2);
					std::cout << "\t영어: " << elem.getScore(english);
					std::cout << "\t역사: " << elem.getScore(history);
					std::cout << "\t물리: " << elem.getScore(physics);
					std::cout << "\t화학: " << elem.getScore(chemical);
					std::cout << "\t생명과학: " << elem.getScore(biology);
					std::cout << "\t지구과학: " << elem.getScore(geology);
					std::cout << "\t총점: " << elem.getTotal();
				}
			}
			if (check != true) { std::cout << "해당 학생 존재하지 없음"; }
		}
		else { std::cout << "저장된 학생 정보 없음"; }
	}

	void input_info() {
		std::string new_name;
		int new_num;
		std::string new_score;

		std::cout << "번호 : ";
		std::cin >> new_num;
		std::cout << "이름 : ";
		std::cin >> new_name;
		std::cin.ignore();
		std::cout << "각 과목의 점수(예 70 80 90): ";
		std::getline(std::cin, new_score);

		auto splite_score = spliteArr(new_score);

		if (students.size() != 40) {
			students.push_back(Student(new_num, new_name));
			for (int i = 0; i < 10; i++) {
				//students[students.size()].addScore(splite_score[i]);
				students.back().addScore(splite_score[i]);
			}
		}
		else { std::cout << "정원 초과"; }

	}

	void edit_info() {
		std::string name, edit_name;
		int  num, val;
		int edit_num = 0, edit_score = 0;
		bool check = false;

		std::cout << "수정하려는 학생의 번호 : ";
		std::cin >> num;
		std::cout << "수정하려는 학생의 이름 : ";
		std::cin >> name;

		if (students.size() != 0) {
			for (auto& elem : students) {
				if ((elem.getStudent().first == num) && (elem.getStudent().second == name)) {
					check = true;
					std::cout << "\t [1] 번호  [2] 이름  [3] 독서  [4] 문학  [5]수학1  [6]수학2  [7]영어  [8] 한국사  [9] 물리  [10] 화학  [11] 생명과학  [12] 지구과학" << std::endl;
					std::cout << "수정하려는 항목을 설정해 주세요 : ";
					std::cin >> val;

					std::cout << "내용을 입력하세요 : ";
					if (val == 1) {
						std::cin >> edit_num;
						elem.setNum(edit_num);
					}
					else if (val == 2) {
						std::cin >> edit_name;
						elem.setName(edit_name);
					}
					else if (val < 13 && val >= 3) {
						std::cin >> edit_score;
						elem.setScore(val - 3, edit_score);
					}
					else {
						std::cout << "ERROR";
						edit_info();
					}
				}
			}
			if (check != true) std::cout << "해당하는 학생 없음";
		}
		else { "정보 비어있음"; }
	}
	void del_info() {
		int chk_num;
		std::string chk_name;
		std::cout << "삭제하려는 학생의 번호 : ";
		std::cin >> chk_num;
		std::cout << "삭제하려는 학생의 이름 : ";
		std::cin >> chk_name;

		for (std::vector<Student>::iterator itr = students.begin(); itr != students.end(); itr++) {
			if (((*itr).getStudent().first == chk_num) && ((*itr).getStudent().second == chk_name)) {
				students.erase(itr);
				std::cout << "학생 정보가 삭제되었습니다." << std::endl;
				itr = students.begin();
			}
		}



	}
};

int main() {
	Students_info student_info;
	int val;
	while (true) {
		std::cout << "\n";
		std::cout << "===================================================" << std::endl;
		std::cout << "	학생 정보 관리 프로그램" << std::endl;
		std::cout << "===================================================" << std::endl;
		std::cout << " [1] 전체 조회" << std::endl;
		std::cout << " [2] 부분 조회" << std::endl;
		std::cout << " [3] 학생 정보 입력" << std::endl;
		std::cout << " [4] 학생 정보 수정" << std::endl;
		std::cout << " [5] 학생 정보 삭제" << std::endl;
		std::cout << " [0] 종료" << std::endl;

		std::cout << "선택 : ";
		std::cin >> val;

		if (val == 0) break;
		else if (val == 1) student_info.search_info();
		else if (val == 2) student_info.search_part_info();
		else if (val == 3) {
			student_info.input_info();
			char answer = 'n';
			while (true) {
				std::cout << "계속 입력하시겠습니까?(y or n) ";
				std::cin >> answer;
				if (answer == 'y') student_info.input_info();
				else break;

			}
		}
		else if (val == 4) student_info.edit_info();
		else if (val == 5) student_info.del_info();
		else { std::cout << "잘 못 입력하셨습니다. "; continue; }
	}
	return 0;

}