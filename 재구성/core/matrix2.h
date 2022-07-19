#include "../../public/math/matrix.h"

namespace zee {
namespace math {
	//기본
	matrix_2x2::matrix_2x2() noexcept : m_{ { 0, 0 } }, row(1), column(1) {
	}
	matrix_2x2::matrix_2x2(const size_t m, const size_t n) noexcept {
		m_.resize(m);
		row = m;
		column = n;
	}
	matrix_2x2::matrix_2x2(const std::vector<vec2f>& vv) noexcept {
		set_m2f(vv);
	}
	matrix_2x2::matrix_2x2(const matrix_2x2& m) noexcept {
		set_mf(m);
	}
	//2x2
	matrix_2x2::matrix_2x2(const vec2f v0, const vec2f v1) noexcept {
		set_m2f({ v0, v1 });
	}
	//3x2
	matrix_2x2::matrix_2x2(const vec2f v0, const vec2f v1, const vec2f v2) noexcept {
		set_m2f({ v0, v1, v2 });
	}
	matrix_2x2::~matrix_2x2() noexcept {
	}

	//행과 열 사이즈 검사
	const bool matrix_2x2::is_same_size(const std::vector<vec2f>& vv) const {
		if (row == vv.size() && column == vv[0].size()) {
			return true;
		}
		else {
			ZEE_LOG(warning, TEXT("matrix"), TEXT("행 사이즈 != 열 사이즈"));
		}
		return false;
	}
	const bool matrix_2x2::is_same_size(const matrix_2x2& m) const {
		if (row == m.get_row_size() && column == m.get_column_size()) {
			return true;
		}
		else {
			ZEE_LOG(warning, TEXT("matrix"), TEXT("행 사이즈 != 열 사이즈"));
		}
		return false;
	}

	//곱셈에서 앞행렬의 열과 뒷행렬의 행이 같아야 함 (+ 3x2 1x2 연산 위해 1 차이만큼을 인정함)
	const bool matrix_2x2::is_same_column_vs_row_size(const matrix_2x2& m) const {
		if (row == m.get_column_size() || row == m.get_column_size() + 1) {
			return true;
		}
		else {
			ZEE_LOG(warning, TEXT("matrix"), TEXT("첫 행렬의 열 사이즈 != 두번째 행렬의 행 사이즈"));
		}
		return false;
	}

	//연산자
	const matrix_2x2& matrix_2x2::operator=(const matrix_2x2& m) {
		set_mf(m);
		return *this;
	}

	const matrix_2x2& matrix_2x2::operator+=(const matrix_2x2& m) {
		if (is_same_size(m)) {
			add(m);
		}
		return *this;
	}

	const matrix_2x2& matrix_2x2::operator-=(const matrix_2x2& m) {
		if (is_same_size(m)) {
			sub(m);
		}
		return *this;
	}

	const matrix_2x2& matrix_2x2::operator*=(const matrix_2x2& m) {
		if (is_same_size(m)) {
			mul(m);
		}
		return *this;
	}

	//사칙연산
	void matrix_2x2::add(const matrix_2x2& m) {
		if (is_same_size(m)) {
			for (int i = 0; i != row; i++) {
				for (int j = 0; j != column; j++) {
					m_[i][j] += m.get_mf()[i][j];
				}
			}
		}
	}

	void matrix_2x2::sub(const matrix_2x2& m) {
		if (is_same_size(m)) {
			for (int i = 0; i != row; i++) {
				for (int j = 0; j != column; j++) {
					m_[i][j] -= m.get_mf()[i][j];
				}
			}
		}
	}

	void matrix_2x2::mul(const vec2f& v) {
		matrix_2x2 m{ {v} };
		mul(m);
	}
	void matrix_2x2::mul(const vec3f& v) {
		matrix_2x2 m{ {v} };
		mul(m);
	}
	void matrix_2x2::mul(const matrix_2x2& m) {
		if (is_same_column_vs_row_size(m)) {
			//mf_ = 3x2 -> 1x2
			if (m.get_row_size() == 1 && m.get_column_size() == 2 && m_.size() > 2) {
				m_ = {
					{ m.get_mf()[0][0] * m_[0][0]
					+ m.get_mf()[0][1] * m_[1][0]
								+ 1.0f * m_[2][0]
					,
					m.get_mf()[0][0] * m_[0][1]
					+ m.get_mf()[0][1] * m_[1][1]
								+ 1.0f * m_[2][1] }
				};
				m_.resize(1);
			}
			//mf_ = 4x3 -> 1x3
			else if (m.get_row_size() == 1 && m.get_column_size() == 3 && m_.size() > 3) {
				m_ = {
					{ m.get_mf()[0][0] * m_[0][0]
					+ m.get_mf()[0][1] * m_[1][0]
					+ m.get_mf()[0][2] * m_[2][0]
								+ 1.0f * m_[3][0]
					,
					m.get_mf()[0][0] * m_[0][1]
					+ m.get_mf()[0][1] * m_[1][1]
					+ m.get_mf()[0][2] * m_[2][1]
								+ 1.0f * m_[3][1]
					,
					m.get_mf()[0][0] * m_[0][2]
					+ m.get_mf()[0][1] * m_[1][2]
					+ m.get_mf()[0][2] * m_[2][2]
								+ 1.0f * m_[3][2] }
				};
				m_.resize(1);
				m_[0].resize(3);
			}
			else {
				ZEE_LOG(warning, TEXT("matrix"), TEXT("현재 지원하지 않는 사이즈 곱입니다."));
			}
		}
	}

	//변환
	void matrix_2x2::translation(const float dx, const float dy) {
		set_m2f({
			{ 1, 0 },
			{ 0, 1 },
			{ dx, dy }
		});
	}
	void matrix_2x2::translation(const float angle, const float dx, const float dy) {
		set_m2f({
			{ 1, 0 },
			{ 0, 1 },
			{ cos(angle) * dx, sin(angle) * dy }
		});
	}

	void matrix_2x2::scale(const float sx, const float sy) {
		set_m2f({
			{ sx, 0 },
			{ 0, sy },
			{ 0, 0 }
		});
	}

	void matrix_2x2::rotation(const float angle, const float dx, const float dy) {
		set_m2f({
			{ cos(angle), -sin(angle) },
			{ sin(angle), cos(angle) },
			{ dx, dy }
		});
	}

	//행렬식: 2x2 ad-bc, 3x3 d(ei-fh)-b(di-fg)+c(dh-eg)
	//행렬식 값이 -1일수도있는데 저걸 반환시키면 어캄?
	//그래서 이럴땐 행렬식이 나올 수 있느냐? 라는 함수가 있어야함.
	//클래스짤때 예외 처리 방법에 대해서도 알아야함.
	const float matrix_2x2::determinant() {//이 함수에서 this의 값을 수정함? ㅇㅎ
		if (row == 2 && column == 2) {
			float a = mf_[0][0], b = mf_[0][1];
			float c = mf_[1][0], d = mf_[1][1];
			return a * d - b * c;
		}
		else if (row == 3 && column == 3) {
			float a = mf_[0][0], b = mf_[0][1], c = mf_[0][2];
			float d = mf_[1][0], e = mf_[1][1], f = mf_[1][2];
			float g = mf_[2][0], h = mf_[2][1], i = mf_[2][2];
			return d * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
		}
		else {
			assert(0);//이건 어썰트임
			//row나 col 이게 정방행렬이 아닌 상황에서 호출되어선 안되죠? 네
			//클래스 설계를 그렇게 해놨짢아
			//그럼 그냥 터치셈.
			//그래야 바로 알게되서 더 좋슴
			//때로는 깨부시는게 좋을때가 더러 있음. ㅇㅎ
			//장난아니라 언리얼이 그래서 존나 자주 터지는게
			//걔넨 짤없이 터쳐버리게 해놔서 그렇슴.
			//꽤 여러군데에서.. 다는 아닌데
			ZEE_LOG(warning, TEXT("matrix"), TEXT("행렬식 사이즈가 잘못되었습니다."));
			return npos;
		}
	}


	//역행렬: (1, 0; 0, 1) 항등행렬 나오는 식. 1/ad-bc * (d -b; -c a). 없으면 로그 띄우고 초기 행렬 반환.
	//자 이런 지역변수 반환하는 행동 이거 아까 경고 뜨던데 
	//모든 상황에서 const T& 형을 써야하는게 아님.
	//당신이 한게 댕글링 래퍼런스임.
	matrix_2x2 matrix_2x2::inverse(const std::vector<vec2f>& vv) {
		if (vv.size() == 2 && vv[0].size() == 2) {
			this->set_m2f(vv);
		}
		return inverse(*this);
	}
	matrix_2x2 matrix_2x2::inverse(const matrix_2x2& m) {
		matrix_2x2 ret;
		if (m.get_row_size() == 2 && m.get_column_size() == 2) {
			if (m.get_mf()[0][0] * m.get_mf()[1][1] - m.get_mf()[0][1] * m.get_mf()[1][0]) {
				float a = m.get_mf()[0][0], b = m.get_mf()[0][1];
				float c = m.get_mf()[1][0], d = m.get_mf()[1][1];
				ret.set_m2f({
					{ 1 / (a * d - b * c) * d, 1 / (a * d - b * c) * -b },
					{ 1 / (a * d - b * c) * -c, 1 / (a * d - b * c) * a }
				});
			}
			else {
				ZEE_LOG(warning, TEXT("matrix"), TEXT("ad - bc가 0이면 역행렬을 만들 수 없습니다."));
			}
		}
		else {
			ZEE_LOG(warning, TEXT("matrix"), TEXT("현재 지원하지 않는 사이즈 역행렬입니다."));
		}
		//return ret;
		return {};
	}

	//단위행렬: 여부
	//쌩 변수 쓰는거보다 get함수 쓰는게 좋음
	//왜 와이? 쌩변수는 실수하다 값을 변경 시킬 수도 있거니와
	//값의 변경을 확인하려고 할때 이름 검색시
	//존나게 만힝 검색되서 나중에 디버깅할떄 막 불편해질 수가 있음
	//그래서 const로 된 함수를 호출시켜서 쓰는게 좋다. ㅇㅎ
	const bool matrix_2x2::is_identity() {
		bool is_identity = false;
		if (get_row_size() > 1 && get_column_size() > 1 &&  get_row_size() ==  get_column_size()) {
			for (int i = 0; i !=  get_row_size(); i++) {
				for (int j = 0; j !=  get_column_size(); j++) {

					if (i == j &&  get_mf()[i][j] == 1) {
						is_identity = true;
					} else if (i != j && get_mf()[i][j] == 0) {
						is_identity = true;
					} else {
						is_identity = false;
						break;
					}
				}

				if (!is_identity) {
					break;
				}
			}
		}
		else {
			ZEE_LOG(warning, TEXT("matrix"), TEXT("2x2 이상의 정방행렬만 항등행렬인지 판단할 수 있습니다."));
		}
		return is_identity;
	}

	//전치행렬: 행과 열을 교환
	void matrix_2x2::transposed() {
		matrix_2x2 m(get_column_size(), get_row_size());
		for (int i = 0; i != m.get_mf().size(); i++) {//int r
			for (int j = 0; j != m.get_mf()[0].size(); j++) {//int c
				m.mf_[i][j] = mf_[j][i];
			}
		}
	}

	//get, set
	const std::vector<std::vector<float>>& matrix_2x2::get_mf() const {
		return mf_;
	}
	const size_t matrix_2x2::get_row_size() const {
		return mf_.size();
	}
	const size_t matrix_2x2::get_column_size() const {
		return mf_[0].size();
	}
	void matrix_2x2::set_m2f(const std::vector<vec2f>& vv) {
		row = vv.size();
		column = vv[0].size();
		mf_.resize(vv.size());
		for (int i = 0; i != row; i++) {
			mf_[i].resize(vv[i].size());
		}
		//1x2, 2x2, 3x2
		for (int i = 0; i != row; i++) {
			for (int j = 0; j != column; j++) {
				mf_[i][j] = vv[i][j];
			}
		}
	}
	void matrix_2x2::set_m3f(const std::vector<vec3f>& vv) {
		row = vv.size();
		column = vv[0].size();
		mf_.resize(vv.size());
		for (int i = 0; i != row; i++) {
			mf_[i].resize(vv[i].size());
		}
		//1x3, 3x3, 4x3
		for (int i = 0; i != row; i++) {
			for (int j = 0; j != column; j++) {
				mf_[i][j] = vv[i][j];
			}
		}
	}
	void matrix_2x2::set_mf(const matrix_2x2& m) {
		row = m.get_row_size();
		column = m.get_column_size();
		mf_.resize(m.get_row_size(), std::vector<float>(m.get_column_size(), npos));
		//1x2, 2x2, 3x2, 1x3, 3x3, 4x3
		for (int i = 0; i != row; i++) {
			for (int j = 0; j != column; j++) {
				mf_[i][j] = m.get_mf()[i][j];
			}
		}
	}
}//math
}//zee