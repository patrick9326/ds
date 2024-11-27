#include <iostream>
using namespace std;

// �e�V�n��
class Polynomial;

// �w�q�������O�G�ΨӪ�ܦh���������C�@��
class Term {
    friend ostream& operator<<(ostream& out, const Polynomial& poly);
    friend istream& operator>>(istream& in, Polynomial& poly);
    friend Polynomial;

private:
    float coef;  // �Y��
    int exp;     // ����

    // Term ���O���غc�l
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polynomial {
public:
    // �w�]�غc�l�G�إߤ@�ӪŪ��h���� p(x) = 0
    Polynomial() : capacity(10), terms(0) {
        termArray = new Term[capacity];
    }

    // �Ѻc�l�G����ʺA�t�m���O����
    ~Polynomial() {
        delete[] termArray;
    }

    // �ƻs�غc�l�G�`�h�ƻs�@�Ӧh����
    Polynomial(const Polynomial& other) : capacity(other.capacity), terms(other.terms) {
        termArray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            termArray[i] = other.termArray[i];
        }
    }

    // ���w�B��l
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            delete[] termArray;
            capacity = other.capacity;
            terms = other.terms;
            termArray = new Term[capacity];
            for (int i = 0; i < terms; i++) {
                termArray[i] = other.termArray[i];
            }
        }
        return *this;
    }

    // �h�����ۥ[
    Polynomial Add(Polynomial poly) {
        Polynomial result;
        int aPos = 0, bPos = 0;

        while (aPos < terms && bPos < poly.terms) {
            if (termArray[aPos].exp == poly.termArray[bPos].exp) {
                float coef = termArray[aPos].coef + poly.termArray[bPos].coef;
                if (coef != 0) {
                    result.NewTerm(coef, termArray[aPos].exp);
                }
                aPos++; bPos++;
            }
            else if (termArray[aPos].exp < poly.termArray[bPos].exp) {
                result.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
                bPos++;
            }
            else {
                result.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                aPos++;
            }
        }

        for (; aPos < terms; aPos++) {
            result.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        }
        for (; bPos < poly.terms; bPos++) {
            result.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
        }

        return result;
    }

    // �h�����ۭ�
    Polynomial Mult(Polynomial poly) {
        Polynomial result;
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < poly.terms; j++) {
                float coef = termArray[i].coef * poly.termArray[j].coef;
                int exp = termArray[i].exp + poly.termArray[j].exp;
                Polynomial temp;
                temp.NewTerm(coef, exp);
                result = result.Add(temp);
            }
        }
        return result;
    }

    // �p��h�����b�Y�@�I����
    float Eval(float f) {
        float result = 0;
        for (int i = 0; i < terms; i++) {
            float power = 1;
            for (int j = 0; j < termArray[i].exp; j++) {
                power *= f;
            }
            result += termArray[i].coef * power;
        }
        return result;
    }

    // ��J��X�B��l�����ŧi
    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    Term* termArray;    // �D�s�����}�C
    int capacity;       // �}�C�e�q
    int terms;          // �D�s�����Ӽ�

    // �s�W�@�Ӷ�����h������
    void NewTerm(float coef, int exp) {
        // ���ˬd�O�_�w�s�b�ۦP���誺��
        for (int i = 0; i < terms; i++) {
            if (termArray[i].exp == exp) {
                // �p�G�s�b�A�h�Y�Ƭۥ[
                float newCoef = termArray[i].coef + coef;
                if (newCoef != 0) {
                    // �p�G�s�Y�Ƥ����s�A��s�Y��
                    termArray[i].coef = newCoef;
                }
                else {
                    // �p�G�s�Y�Ƭ��s�A��������
                    for (int j = i; j < terms - 1; j++) {
                        termArray[j] = termArray[j + 1];
                    }
                    terms--;
                }
                return;
            }
            else if (termArray[i].exp < exp) {
                // ��쥿�T�����J��m
                break;
            }
        }

        // �p�G���s�b�ۦP���誺���B�Y�Ƥ����s�A�h�s�W
        if (coef != 0) {
            if (terms == capacity) {
                capacity *= 2;
                Term* newArray = new Term[capacity];
                for (int i = 0; i < terms; i++) {
                    newArray[i] = termArray[i];
                }
                delete[] termArray;
                termArray = newArray;
            }

            int i;
            for (i = terms - 1; i >= 0 && termArray[i].exp < exp; i--) {
                termArray[i + 1] = termArray[i];
            }
            termArray[i + 1] = Term(coef, exp);
            terms++;
        }
    }
};

// ��@��J�B��l
istream& operator>>(istream& in, Polynomial& poly) {
    poly.terms = 0;
    int numTerms;
    cout << "�п�J�������Ӽ�: ";
    in >> numTerms;

    cout << "�Ш̧ǿ�J�C�@�����Y�ƩM����]�q�������C����^:\n";
    for (int i = 0; i < numTerms; i++) {
        float coef;
        int exp;
        cout << "�� " << i + 1 << " ���]�Y�� ����^: ";
        in >> coef >> exp;
        if (coef != 0) {
            poly.NewTerm(coef, exp);
        }
    }
    return in;
}

// ��@��X�B��l
ostream& operator<<(ostream& out, const Polynomial& poly) {
    if (poly.terms == 0) {
        out << "0";
        return out;
    }

    bool first = true;
    for (int i = 0; i < poly.terms; i++) {
        if (first) {
            if (poly.termArray[i].coef < 0) {
                out << "-";
            }
        }
        else {
            if (poly.termArray[i].coef < 0) {
                out << " - ";
            }
            else {
                out << " + ";
            }
        }

        float absCoef = abs(poly.termArray[i].coef);
        if (absCoef != 1 || poly.termArray[i].exp == 0) {
            out << absCoef;
        }

        if (poly.termArray[i].exp > 0) {
            out << "x";
            if (poly.termArray[i].exp > 1) {
                out << "^" << poly.termArray[i].exp;
            }
        }

        first = false;
    }
    return out;
}

int main() {
    Polynomial p1, p2;

    cout << "\n====== �h�����p��� ======\n\n";

    cout << "�п�J�Ĥ@�Ӧh�����G\n";
    cin >> p1;

    cout << "\n�п�J�ĤG�Ӧh�����G\n";
    cin >> p2;

    cout << "\n====== �p�⵲�G ======\n";
    cout << "p1(x) = " << p1 << endl;
    cout << "p2(x) = " << p2 << endl;

    Polynomial sum = p1.Add(p2);
    cout << "p1 + p2 = " << sum << endl;

    Polynomial product = p1.Mult(p2);
    cout << "p1 * p2 = " << product << endl;

    float x;
    cout << "\n�п�J�n�a�J�� x ��: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Eval(x) << endl;
    cout << "p2(" << x << ") = " << p2.Eval(x) << endl;
    cout << "(p1 + p2)(" << x << ") = " << sum.Eval(x) << endl;
    cout << "(p1 * p2)(" << x << ") = " << product.Eval(x) << endl;

    return 0;
}