#include <iostream>
#include <boost/multiprecision/cpp_int.hpp> 
#include <fstream>
#include <string.h>
#include <string>
#include <deque>
#include <sstream> 
#include <stack> 

using namespace boost::multiprecision; 
using namespace std;

char *input_file;
char *base;
deque<int1024_t> dequee;
bool paranteza_deschisa = false;
string instructiune_paranteza_deschisa;
long unsigned int i_paranteza_deschisa;
bool stop_remember = false;
bool remember = false;
vector<long unsigned int> i_remember;
vector<string> instructiune_curenta_remember;
stack<int1024_t> verificare_corectitudine_paranteze;

// citeste argumentele programului
void get_args(int argc, char **argv) {
	input_file = argv[1];
	base = argv[2];
}

void set_instructiuni (string instructiune_curenta, long unsigned int i) {
	// tin minte instructiuni pentru paranteza deschisa
	if (remember == true) {
		instructiune_curenta_remember.push_back(instructiune_curenta);
		i_remember.push_back(i);
	}

	// daca paranteza e deschisa si pe coada 0
	if (paranteza_deschisa == true) {
		if (instructiune_curenta.compare("0123") == 0) {
			paranteza_deschisa = false;
		}
	} else {
		// instructiune = 0000 NOP
		if (instructiune_curenta.compare("0000") == 0) {
			// DO NOTHING
		}

		// instructiune = 0001 Input(i)
		if (instructiune_curenta.compare("0001") == 0) {
			string x;
			int1024_t y, lungime_string;
			cin >> x;
			lungime_string = x.length();

			stringstream geek(x);
			geek >> y;

			// verific daca inputul e numar sau e gresit
			for (long unsigned int q = 0; q < lungime_string; ++q) {
				if (x[0] == '-') {
					continue;
				}
				if (!(x[q] >= '0' && x[q] <= '9')) {
					cerr << "Exception:" << i;
					exit(-2);
				}
			}

			dequee.push_back(y);
		}

		// instructiune = 0010 Rot
		if (instructiune_curenta.compare("0010") == 0) {
			// coada goala
			if (dequee.size() == 0) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			int1024_t last_elem;
			last_elem = dequee.back();
			dequee.pop_back();
			dequee.push_front(last_elem);
		}

		// instructiune = 0011 Swap
		if (instructiune_curenta.compare("0011") == 0) {
			// coada incompleta
			if (dequee.size() < 2) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			int1024_t last_elem;
			last_elem = dequee.back();
			dequee.pop_back();

			int1024_t pre_last_elem;
			pre_last_elem = dequee.back();
			dequee.pop_back();

			dequee.push_back(last_elem);
			dequee.push_back(pre_last_elem);
		}

		// instructiune = 0012 Push(1)
		if (instructiune_curenta.compare("0012") == 0) {
			dequee.push_back(1);
		}

		// instructiune = 0100 RRot
		if (instructiune_curenta.compare("0100") == 0) {
			// coada goala
			if (dequee.size() == 0) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			int1024_t first_elem;
			first_elem = dequee.front();
			dequee.pop_front();
			dequee.push_back(first_elem);
		}

		// instructiune = 0101 Dup
		if (instructiune_curenta.compare("0101") == 0) {
			// coada goala
			if (dequee.size() == 0) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			int1024_t last_elem;
			last_elem = dequee.back();
			dequee.push_back(last_elem);
		}

		// instructiune = 0102 Add
		if (instructiune_curenta.compare("0102") == 0) {
			// coada incompleta
			if (dequee.size() < 2) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			int1024_t last_elem;
			last_elem = dequee.back();
			dequee.pop_back();

			int1024_t pre_last_elem;
			pre_last_elem = dequee.back();
			dequee.pop_back();

			int1024_t suma;
			suma = last_elem + pre_last_elem;
			dequee.push_back(suma);
		}

		// instructiune = 0110 L-brace
		if (instructiune_curenta.compare("0110") == 0) {
			instructiune_paranteza_deschisa = instructiune_curenta;
			i_paranteza_deschisa = i;
			// coada goala
			if (dequee.size() == 0) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			if (dequee.back() == 0) {
				paranteza_deschisa = true;
				stop_remember = false;
			} else {
				if (stop_remember == false) {
					remember = true;
				}
				if (remember == false) {
					for (long unsigned int p = 0; p < instructiune_curenta_remember.size(); ++p) {
						set_instructiuni(instructiune_curenta_remember[p], i_remember[p]);
					}
				}
			}
		}

		// instructiune = 0111 Output(o)
		if (instructiune_curenta.compare("0111") == 0) {
			// coada goala
			if (dequee.size() == 0) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			int1024_t last_elem;
			last_elem = dequee.back();
			dequee.pop_back();
			cout << last_elem << endl;
		}

		// instructiune = 0112 Multiply
		if (instructiune_curenta.compare("0112") == 0) {
			// coada incompleta
			if (dequee.size() < 2) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			int1024_t last_elem;
			last_elem = dequee.back();
			dequee.pop_back();

			int1024_t pre_last_elem;
			pre_last_elem = dequee.back();
			dequee.pop_back();

			int1024_t produs;
			produs = last_elem * pre_last_elem;
			dequee.push_back(produs);
		}

		// instructiune = 0120 Execute
		if (instructiune_curenta.compare("0120") == 0) {
			// coada incompleta
			if (dequee.size() < 4) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			int1024_t a;
			a = dequee.back();
			dequee.pop_back();

			int1024_t b;
			b = dequee.back();
			dequee.pop_back();

			int1024_t c;
			c = dequee.back();
			dequee.pop_back();

			int1024_t d;
			d = dequee.back();
			dequee.pop_back();

			string new_instruction_again;
			vector<int1024_t> used_caracter_again;
			vector<int1024_t> vec_caracter_again;
			int1024_t caracter_again;
			vector<string> numere03 = {"0", "1", "2", "3"};
			bool gasit = false;

			vec_caracter_again.push_back(a);
			vec_caracter_again.push_back(b);
			vec_caracter_again.push_back(c);
			vec_caracter_again.push_back(d);

			caracter_again = vec_caracter_again[0];
			used_caracter_again.push_back(caracter_again);
			new_instruction_again = "0";
			for(int i = 1; i < 4; ++i) {
				caracter_again = vec_caracter_again[i];
				long unsigned int j;
				for (j = 0; j < used_caracter_again.size(); ++j) {
					if (caracter_again == used_caracter_again[j]) {
						new_instruction_again.append(numere03[j]);
						gasit = true;
					}
				}
				if (gasit == false) {
					used_caracter_again.push_back(caracter_again);
					new_instruction_again.append(numere03[j]);
				}
				gasit = false;
			}

			set_instructiuni(new_instruction_again, i);
		}

		// instructiune = 0121 Negate
		if (instructiune_curenta.compare("0121") == 0) {
			// coada goala
			if (dequee.size() == 0) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			int1024_t last_elem;
			last_elem = dequee.back();
			dequee.pop_back();

			last_elem = last_elem * (-1);
			dequee.push_back(last_elem);
		}

		// instructiune = 0122 Pop
		if (instructiune_curenta.compare("0122") == 0) {
			// coada goala
			if (dequee.size() == 0) {
				cerr << "Exception:" << i << endl;
				exit(-2);
			}
			dequee.pop_back();
		}

		// instructiune = 0123 R-brace
		if (instructiune_curenta.compare("0123") == 0) {
			// coada goala
			if (dequee.size() == 0) {
				cerr << "Exception:" << i_paranteza_deschisa << endl;
				exit(-2);
			}
			
			// daca pe coada avem 0 trecem mai departe fara sa mai facem loopul de instructiuni
			if (dequee.back() == 0) {
				stop_remember = false;
				remember = false;
			} else {
				stop_remember = true;
				remember = false;
				set_instructiuni(instructiune_paranteza_deschisa, i_paranteza_deschisa);
			}
		}
	}
}

int main(int argc, char *argv[]) {

	char caracter;
	vector<char> used_caracter;
	vector<string> codes;
	vector<char> verifica_lungime;
	bool gasit = false;
	int instructiune_eroare;
	string new_instruction;
	vector<string> numere03 = {"0", "1", "2", "3"};

	get_args(argc, argv);

	ifstream in(input_file, ifstream::in);
	
	while (in >> caracter) {
		verifica_lungime.push_back(caracter);
	}
	if (verifica_lungime.size() % 4 != 0) {
		// eroare lungime incompleta
		instructiune_eroare = (verifica_lungime.size() / 4);
		cerr << "Error:" << instructiune_eroare << endl;
		return -1;
	}

	long unsigned int k;
	for (k = 0; k < verifica_lungime.size(); k += 4) {
		caracter = verifica_lungime[k];
		used_caracter.push_back(caracter);
		new_instruction = "0";
		for(int i = 1; i < 4; ++i) {
			caracter = verifica_lungime[i + k];
			long unsigned int j;
			for (j = 0; j < used_caracter.size(); ++j) {
				if (caracter == used_caracter[j]) {
					new_instruction.append(numere03[j]);
					gasit = true;
				}
			}
			if (gasit == false) {
				used_caracter.push_back(caracter);
				new_instruction.append(numere03[j]);
			}
			gasit = false;
		}

		codes.push_back(new_instruction);
		used_caracter.clear();

		if (new_instruction.compare("0110") == 0) {
			verificare_corectitudine_paranteze.push(1);
		}
		if (new_instruction.compare("0123") == 0) {
			if (verificare_corectitudine_paranteze.size() != 0) {
				verificare_corectitudine_paranteze.pop();
			} else {
				cerr << "Error:" << k / 4 << endl;
				exit(-1);
			}
		}
	}

	if (verificare_corectitudine_paranteze.size() > 0) {
		cerr << "Error:" << k / 4 << endl;
		exit(-1);
	}

	for (long unsigned int i = 0; i < codes.size(); ++i) {
		string instructiune_curenta;
		instructiune_curenta = codes[i];

		set_instructiuni(instructiune_curenta, i);
	}
	
	return 0;
}