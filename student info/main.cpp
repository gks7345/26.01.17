#include <iostream>
#include <string>
#include <cctype>

static int* spliteArr(std::string arr) {
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
static int total_score(int arr[]) {
	float total = arr[0] * 1.5 + arr[1] * 1.5 + arr[2] * 2.0 + arr[3] * 2.0 + arr[4] * 1.8 + arr[5] * 2.5 + arr[6] * 1.5 + arr[7] * 1.5 + arr[8] * 1.5 + arr[9] * 1.5;
	return total;
}

class Students_info {
	//멤버 변수
private:
	struct Score_info {
		int reading, literature, math1, math2, english, history, physics, chemical, bio, geo;
		float total;
	};
	struct Student_list {
		int num;
		std::string name;
		struct Score_info info;
	};

	Student_list student_list[40] = { 0 };
	std::string name_idx[11] = { "\t 독서: ", "\t 문학: ", "\t 수학1: ", "\t 수학2: ", "\t 영어: ", "\t 한국사: ", "\t 과학: ","\t 화학: ", "\t 생명과학: ", "\t 지구과학: ", "\t 총점: " };
	int* score_idx[40][10] = { 0 };

public:
	void search_info() {
		bool check = false;

		for (int i = 0; i < 40; ++i) {
			score_idx[i][0] = &student_list[i].info.reading;
			score_idx[i][1] = &student_list[i].info.literature;
			score_idx[i][2] = &student_list[i].info.math1;
			score_idx[i][3] = &student_list[i].info.math2;
			score_idx[i][4] = &student_list[i].info.english;
			score_idx[i][5] = &student_list[i].info.history;
			score_idx[i][6] = &student_list[i].info.physics;
			score_idx[i][7] = &student_list[i].info.chemical;
			score_idx[i][8] = &student_list[i].info.bio;
			score_idx[i][9] = &student_list[i].info.geo;
		}

		for (int i = 0; i < 40; ++i) {
			if (student_list[i].num == 0 && student_list[i].name.empty()) {
				continue;
			}

			std::cout << student_list[i].num << "\t" << student_list[i].name;
			for (int j = 0; j < 10; ++j) std::cout << name_idx[j] << *score_idx[i][j];
			std::cout << name_idx[10] << student_list[i].info.total << std::endl;
			check = true;
		}
		if (check == false) std::cout << "저장된 학생 정보 없음";
	};

	void search_part_info() {
		for (int i = 0; i < 40; ++i) {
			score_idx[i][0] = &student_list[i].info.reading;
			score_idx[i][1] = &student_list[i].info.literature;
			score_idx[i][2] = &student_list[i].info.math1;
			score_idx[i][3] = &student_list[i].info.math2;
			score_idx[i][4] = &student_list[i].info.english;
			score_idx[i][5] = &student_list[i].info.history;
			score_idx[i][6] = &student_list[i].info.physics;
			score_idx[i][7] = &student_list[i].info.chemical;
			score_idx[i][8] = &student_list[i].info.bio;
			score_idx[i][9] = &student_list[i].info.geo;
		}

		int chk_num;
		std::string chk_name;
		std::cout << "조회하려는 학생의 번호 : ";
		std::cin >> chk_num;
		std::cout << "조회하려는 학생의 이름 : ";
		std::cin >> chk_name;
		bool check = check_info(chk_num, chk_name);

		if (check == false) {
			std::cout << "해당 학생 존재하지 않음";
			return;
		}

		for (int i = 0; i < 40; ++i) {
			if (student_list[i].num == chk_num && student_list[i].name == chk_name) {
				std::cout << student_list[i].num << "\t" << student_list[i].name << "\t";
				for (int j = 0; j < 10; ++j) std::cout << name_idx[j] << *score_idx[i][j];
				std::cout << name_idx[10] << student_list[i].info.total << std::endl;
			}
			/*else continue;*/
		}
	}

	bool check_info(int chk_num, std::string chk_name) {
		bool check = false;
		for (int i = 0; i < 40; ++i) {
			if (student_list[i].num == chk_num && student_list[i].name == chk_name) {
				check = true;
			}
			else continue;
		}
		return check;
	}

	void input_info() {
		for (int i = 0; i < 40; ++i) {
			score_idx[i][0] = &student_list[i].info.reading;
			score_idx[i][1] = &student_list[i].info.literature;
			score_idx[i][2] = &student_list[i].info.math1;
			score_idx[i][3] = &student_list[i].info.math2;
			score_idx[i][4] = &student_list[i].info.english;
			score_idx[i][5] = &student_list[i].info.history;
			score_idx[i][6] = &student_list[i].info.physics;
			score_idx[i][7] = &student_list[i].info.chemical;
			score_idx[i][8] = &student_list[i].info.bio;
			score_idx[i][9] = &student_list[i].info.geo;
		}

		bool check = false;
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

		int* splite_score = spliteArr(new_score);

		for (int i = 0; i < 40; ++i) {
			if (student_list[i].num == 0 && student_list[i].name.empty()) {
				student_list[i].name = new_name;
				student_list[i].num = new_num;
				for (int j = 0; j < 10; j++) {
					*score_idx[i][j] = splite_score[j];
				}
				float total = total_score(splite_score);
				student_list[i].info.total = total;
				check = true;
				break;
			}
		}
		if (check == false) std::cout << "정원 초과";
	}

	void edit_info() {
		for (int i = 0; i < 40; ++i) {
			score_idx[i][0] = &student_list[i].info.reading;
			score_idx[i][1] = &student_list[i].info.literature;
			score_idx[i][2] = &student_list[i].info.math1;
			score_idx[i][3] = &student_list[i].info.math2;
			score_idx[i][4] = &student_list[i].info.english;
			score_idx[i][5] = &student_list[i].info.history;
			score_idx[i][6] = &student_list[i].info.physics;
			score_idx[i][7] = &student_list[i].info.chemical;
			score_idx[i][8] = &student_list[i].info.bio;
			score_idx[i][9] = &student_list[i].info.geo;
		}

		std::string name, edit_name;
		int  num, val, studetidx;
		int edit_num = 0, edit_score = 0;

		std::cout << "수정하려는 학생의 번호 : ";
		std::cin >> num;
		std::cout << "수정하려는 학생의 이름 : ";
		std::cin >> name;

		bool check = check_info(num, name);
		if (check == false) {
			std::cout << "해당 학생 존재하지 않음";
			return;
		}

		for (int i = 0; i < 40; ++i) {
			if (student_list[i].num == num && student_list[i].name == name) {
				std::cout << student_list[i].num << "\t" << student_list[i].name << "\t";
				studetidx = i;
			}
			else continue;
		}


		std::cout << "\t [1] 번호  [2] 이름  [3] 독서  [4] 문학  [5]수학1  [6]수학2  [7]영어  [8] 한국사  [9] 물리  [10] 화학  [11] 생명과학  [12] 지구과학" << std::endl;
		std::cout << "수정하려는 항목을 설정해 주세요 : ";
		std::cin >> val;

		if (val == 1) {
			std::cout << "내용을 입력하세요 : ";
			std::cin >> edit_num;
			student_list[studetidx].num = edit_num;
		}
		else if (val == 2) {
			std::cout << "내용을 입력하세요 : ";
			std::cin >> edit_name;
			student_list[studetidx].name = edit_name;
		}
		else if (val < 13 && val >= 3) {
			std::cout << "내용을 입력하세요 : ";
			std::cin >> edit_score;
			*score_idx[studetidx][val - 3] = edit_score;
			float total = total_score(*score_idx[studetidx]);
			student_list[studetidx].info.total = total;
		}
		else {
			std::cout << "잘 못 입력하셨습니다." << std::endl;
			edit_info();
		}
	}
	void del_info() {
		int chk_num;
		std::string chk_name;
		std::cout << "삭제하려는 학생의 번호 : ";
		std::cin >> chk_num;
		std::cout << "삭제하려는 학생의 이름 : ";
		std::cin >> chk_name;

		for (int i = 0; i < 40; ++i) {
			if (student_list[i].num == chk_num && student_list[i].name == chk_name) {
				student_list[i] = { 0 };
				std::cout << "학생 정보가 삭제되었습니다.";
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