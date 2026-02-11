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
	Subject sub;
public:
	Score(int score,Subject sub):score(score), sub(sub){}
	
	int getScore() { return score; }
	Subject	getSubject() { return sub; }
	void setScore(int sc) { score = sc;}
	float getWeight() {
		switch (sub) {
		case reading:
		case literature:
			return score*1.5f;
		case math1:
		case math2:
			return score * 2.0f;
		case english:
			return score * 1.8f;
		case history:
			return score * 2.5f;
		case physics:
		case chemical:
		case biology:
		case geology:
			return score * 1.5f;
		}
	}
};

class Student {
private:
	int num;
	std::string name;
	std::vector<std::unique_ptr<Score>> scores;
public:
	Student(int num, std::string name):num(num),name(name){}

	int getNum() const { return num; }
	std::string getName() const{ return name; }
	void setNum(int n) { num = n; }
	void setName(std::string n) { name = n; }
	void addScore(int sc, int idx) {
		Subject sub = static_cast<Subject>(idx);
		scores.push_back(std::make_unique<Score>(sc, sub));
	}
	//어떤 과목의 점수를 받아서 변경할지
	void setScore(Subject sub,int sc) {
		for (std::unique_ptr<Score>& score : scores) {
			if (score->getSubject() == sub) {
				score->setScore(sc);
				break;
			}
		}
	}

	Score* findBySubject(Subject sub) {
		for (std::unique_ptr<Score>& score : scores) {
			if (score->getSubject() == sub) {
				return score.get();
			}
		}
		return nullptr;
	}

	std::vector<std::unique_ptr<Score>>& getScores() {
		return scores;
	}

	float getTotal() {
		float total = 0;
		for (std::unique_ptr<Score>& score : scores) {
			total += score->getWeight();
		}
		return total;
	}

	bool checkStudent(int num, std::string name) {
		if (Student::num == num && Student::name == name) {
			return true;
		}
		return false;
	}
};

class Students_info {
	//멤버 변수
private:
	std::vector<Student> students;

public:
	Student* finByNumAndName(int num, std::string name) {
		for (Student& student : students) {
			if (student.getNum() == num && student.getName() == name) {
				return &student;
			}
		}
		return nullptr;
	}
	void search_info() {
		if (students.size() != 0) {
			for (auto& student : students) {
				std::cout << student.getNum() << "\t" << student.getName();
				for (std::unique_ptr<Score>& score : student.getScores()) {
					std::cout << "\t" << score->getSubject()<<": " << score->getScore();
				}
				std::cout << "\t총점: " << student.getTotal()<<std::endl;
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

		if (students.size() != 0) {
			Student* student = finByNumAndName(chk_num, chk_name);
			if (student != nullptr) {
				std::cout << student->getNum() << "\t" << student->getName();
				for (std::unique_ptr<Score>& score : student->getScores()) {
					std::cout << "\t" << score->getSubject() << ": " << score->getScore();
				}
				std::cout << "\t" << "총점: " << student->getTotal() << std::endl;
			}
			else std::cout << "해당하는 학생 없음" << std::endl;
		}
		else std::cout << "저장된 학생 정보 없음" << std::endl;

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
			Student student = Student(new_num, new_name);
			for (int i = 0; i < 10; i++) {
				//students[students.size()].addScore(splite_score[i]);
				//Subject sub = static_cast<Subject>(i);
				student.addScore(splite_score[i],i);
			}
			students.push_back(std::move(student));
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
			Student* student = finByNumAndName(num, name);
			if (student != nullptr) {
				std::cout << "\t [1] 번호  [2] 이름  [3] 독서  [4] 문학  [5]수학1  [6]수학2  [7]영어  [8] 한국사  [9] 물리  [10] 화학  [11] 생명과학  [12] 지구과학" << std::endl;
				std::cout << "수정하려는 항목을 설정해 주세요 : ";
				std::cin >> val;

				std::cout << "내용을 입력하세요 : ";
				if (val == 1) {
					std::cin >> edit_num;
					student->setNum(edit_num);
				}
				else if (val == 2) {
					std::cin >> edit_name;
					student->setName(edit_name);
				}
				else if (val < 13 && val >= 3) {
					std::cin >> edit_score;
					Subject sub = static_cast<Subject>(val - 3);
					student->setScore(sub, edit_score);
				}
				else {
					std::cout << "ERROR"<<std::endl;
					edit_info();
				}
			}
			else std::cout << "해당하는 학생 없음"<<std::endl;
		}
		else { std::cout<<"정보 비어있음"<<std::endl; }
	}
	void del_info() {
		int chk_num;
		std::string chk_name;
		std::cout << "삭제하려는 학생의 번호 : ";
		std::cin >> chk_num;
		std::cout << "삭제하려는 학생의 이름 : ";
		std::cin >> chk_name;

		Student* student = finByNumAndName(chk_num, chk_name);
		if (student != nullptr) {
			students.erase(remove_if(students.begin(), students.end(),
				[&](Student& student) {return student.checkStudent(chk_num, chk_name); }), students.end());
			std::cout << "학생 정보가 삭제되었습니다." << std::endl;
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