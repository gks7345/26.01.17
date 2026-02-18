#include <iostream>
#include <string>
#include <cctype>
#include <vector>

enum Subject {
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
	Score(int score, Subject sub) :score(score), sub(sub) {}

	int getScore() { return score; }
	Subject	getSubject() { return sub; }
	void setScore(int sc) { score = sc; }
	float getWeight() {
		switch (sub) {
		case reading:
		case literature:
			return score * 1.5f;
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
	Student(int num, std::string name) :num(num), name(name) {}

	int getNum() const { return num; }
	std::string getName() const { return name; }
	void setNum(int n) { num = n; }
	void setName(std::string n) { name = n; }
	void addScore(int sc, int idx) {
		Subject sub = static_cast<Subject>(idx);
		scores.push_back(std::make_unique<Score>(sc, sub));
	}
	//어떤 과목의 점수를 받아서 변경할지
	void setScore(Subject sub, int sc) {
		Score* score = findBySubject(sub);
		if (score != nullptr) {
			score->setScore(sc);
		}
		else std::cout << "과목이 없습니다." << std::endl;
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

	std::string getSubjectToString(int idx) {
		Subject sub = static_cast<Subject>(idx);
		switch (sub) {
		case reading:
			return "독서";
		case literature:
			return "문학";
		case math1:
			return "수학1";
		case math2:
			return "수학2";
		case english:
			return "영어";
		case history:
			return "역사";
		case physics:
			return "물리";
		case chemical:
			return "화학";
		case biology:
			return "생명과학";
		case geology:
			return "지구과학";
		}
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
		if (students.size() == 0) {
			std::cout << "저장된 학생 정보 없음"; 
			return; 
		}

		for (auto& student : students) {
			std::cout << student.getNum() << "\t" << student.getName();
			for (std::unique_ptr<Score>& score : student.getScores()) 
			{
				std::cout << "\t" << student.getSubjectToString(score->getSubject()) << ": " << score->getScore();
			}
			std::cout << "\t총점: " << student.getTotal() << std::endl;
		}
	}


	void search_part_info() {
		if (students.size() == 0) {
			std::cout << "저장된 학생 정보 없음" << std::endl;
			return;
		}
		int chk_num;
		std::string chk_name;
		std::cout << "조회하려는 학생의 번호 : ";
		std::cin >> chk_num;
		std::cout << "조회하려는 학생의 이름 : ";
		std::cin >> chk_name;

		Student* student = finByNumAndName(chk_num, chk_name);
		if (student == nullptr) {
			std::cout << "해당하는 학생 없음" << std::endl;
			return;
		}

		std::cout << student->getNum() << "\t" << student->getName();
		for (std::unique_ptr<Score>& score : student->getScores()) {
			std::cout << "\t" << student->getSubjectToString(score->getSubject()) << ": " << score->getScore();
		}
		std::cout << "\t" << "총점: " << student->getTotal() << std::endl;
	}

	void input_info() {
		if (students.size() == 40) {
			std::cout << "정원 초과"<< std::endl;
			return;
		}

		std::string new_name;
		int new_num;
		std::string new_score;

		std::cout << "번호 : ";
		std::cin >> new_num;
		std::cout << "이름 : ";
		std::cin >> new_name;
		std::cin.ignore();

		students.push_back(Student(new_num, new_name));
		for (int i = 0; i < 10; i++) {
			std::cout << students.back().getSubjectToString(i) << " : ";
			std::cin >> new_score;
			std::cin.ignore();
			int score = std::stoi(new_score);
			students.back().addScore(score, i);
		}
	}

	void edit_info() {
		if (students.size() == 0) {
			 std::cout << "정보 비어있음" << std::endl; 
			 return;
		}
		std::string name, edit_name;
		int  num, val;
		int edit_num = 0, edit_score = 0;

		std::cout << "수정하려는 학생의 번호 : ";
		std::cin >> num;
		std::cout << "수정하려는 학생의 이름 : ";
		std::cin >> name;

		Student* student = finByNumAndName(num, name);

		if (student == nullptr) {
			std::cout << "해당하는 학생 없음" << std::endl;
			return;
		}

		std::cout << "\t [1] 번호  [2] 이름  [3] 독서  [4] 문학  [5]수학1  [6]수학2  [7]영어  [8] 한국사  [9] 물리  [10] 화학  [11] 생명과학  [12] 지구과학" << std::endl;
		std::cout << "수정하려는 항목을 설정해 주세요 : ";
		std::cin >> val;

		if (val == 1) {
			std::cout << "내용을 입력하세요 : ";
			std::cin >> edit_num;
			student->setNum(edit_num);
			return;
		}
		if (val == 2) {
			std::cout << "내용을 입력하세요 : ";
			std::cin >> edit_name;
			student->setName(edit_name);
			return;
		}
		if (val < 13 && val >= 3) {
			std::cout << "내용을 입력하세요 : ";
			std::cin >> edit_score;
			Subject sub = static_cast<Subject>(val - 3);
			student->setScore(sub, edit_score);
			return;
		}
		throw std::runtime_error("수정하려는 항목이 없습니다.");
	}

	void del_info() {
		int chk_num;
		std::string chk_name;
		std::cout << "삭제하려는 학생의 번호 : ";
		std::cin >> chk_num;
		std::cout << "삭제하려는 학생의 이름 : ";
		std::cin >> chk_name;

		Student* student = finByNumAndName(chk_num, chk_name);
		if (student == nullptr) {
			std::cout << "해당하는 학생이 없습니다." << std::endl;
			return;
		}
		
		students.erase(remove_if(students.begin(), students.end(),
			[&](Student& student) {return student.checkStudent(chk_num, chk_name); }), students.end());
		std::cout << "학생 정보가 삭제되었습니다." << std::endl;
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
				if (answer == 'n') { break; }
				student_info.input_info();
			}
		}
		else if (val == 4) {
			try {
				student_info.edit_info();
			}
			catch (const std::exception& e) {
				std::cout << e.what();
			}
		}
		else if (val == 5) student_info.del_info();
		else { std::cout << "잘 못 입력하셨습니다. "; continue; }
	}
	return 0;

}