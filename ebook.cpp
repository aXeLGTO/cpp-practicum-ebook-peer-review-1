#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Ebook {
public:
	void Read(int user, int page) {
		ValidateUser(user);
		ValidatePage(page);

		const auto prev_page = users_[user];
		if (prev_page > 0) {
			--pages_[prev_page];
		} else {
			++users_count_;
		}

		users_[user] = page;
		++pages_[page];
	}

	double Cheer(int user) {
		ValidateUser(user);

		const auto curr_page = users_[user];
		if(curr_page == 0) {
			return 0.0;
		} else if (users_count_ == 1) {
			return 1;
		}

		ValidatePage(curr_page);

		return accumulate(
			pages_.begin(), next(pages_.begin(), curr_page),
			0,
			plus<int>{}
		) / (users_count_ - 1.0);
	}

private:
	void ValidateUser(int user) {
		if (user >= users_.size()) {
			users_.resize(user + 1);
		}
	}

	void ValidatePage(int page) {
		if (page >= pages_.size()) {
			pages_.resize(page + 1);
		}
	}

	vector<int> users_;
	vector<int> pages_;
	int users_count_ = 0;
};

void ReadQueries(Ebook& ebook, istream& in, ostream& out) {
	int n;
	in >> n;

	while (n-- > 0) {
		string query;
		int user;
		in >> query >> user;

		if (query == "READ"s) {
			int page;
			in >> page;
			ebook.Read(user, page);
		} else if (query == "CHEER"s) {
			out << ebook.Cheer(user) << endl;
		}
	}
}

int main() {
	Ebook ebook;
	ReadQueries(ebook, cin, cout);
}
