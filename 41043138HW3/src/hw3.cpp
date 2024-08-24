#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class PolyTerm {
public:
    float coefficient;
    int exponent;

    PolyTerm(float coef = 0, int exp = 0) : coefficient(coef), exponent(exp) {}
};

class Poly {
private:
    vector<PolyTerm> terms;

public:
    Poly() {}

    void addTerm(float coef, int exp) {
        for (auto& term : terms) {
            if (term.exponent == exp) {
                term.coefficient += coef;
                return;
            }
        }
        terms.push_back(PolyTerm(coef, exp));
    }

    friend istream& operator>>(istream& input, Poly& p);
    friend ostream& operator<<(ostream& output, const Poly& p);

    Poly operator+(const Poly& other) const;
    Poly operator-(const Poly& other) const;
    Poly operator*(const Poly& other) const;

    float evaluate(float x) const;
};

istream& operator>>(istream& input, Poly& p) {
    int numTerms;
    cout << "Enter number of terms: ";
    input >> numTerms;

    for (int i = 0; i < numTerms; ++i) {
        float coef;
        int exp;
        cout << "Enter coefficient and exponent: ";
        input >> coef >> exp;
        p.addTerm(coef, exp);
    }

    sort(p.terms.begin(), p.terms.end(), [](const PolyTerm& a, const PolyTerm& b) {
        return a.exponent > b.exponent;
        });

    return input;
}

ostream& operator<<(ostream& output, const Poly& p) {
    for (size_t i = 0; i < p.terms.size(); ++i) {
        output << p.terms[i].coefficient << "x^" << p.terms[i].exponent;
        if (i != p.terms.size() - 1) output << " + ";
    }
    return output;
}

Poly Poly::operator+(const Poly& other) const {
    Poly result = *this;
    for (const auto& term : other.terms) {
        result.addTerm(term.coefficient, term.exponent);
    }
    return result;
}

Poly Poly::operator-(const Poly& other) const {
    Poly result = *this;
    for (const auto& term : other.terms) {
        result.addTerm(-term.coefficient, term.exponent);
    }
    return result;
}

Poly Poly::operator*(const Poly& other) const {
    Poly result;
    for (const auto& term1 : terms) {
        for (const auto& term2 : other.terms) {
            result.addTerm(term1.coefficient * term2.coefficient, term1.exponent + term2.exponent);
        }
    }
    return result;
}

float Poly::evaluate(float x) const {
    float result = 0.0;
    for (const auto& term : terms) {
        result += term.coefficient * pow(x, term.exponent);
    }
    return result;
}

int main() {
    Poly poly1, poly2;

    cout << "Input the first polynomial:\n";
    cin >> poly1;
    cout << "Input the second polynomial:\n";
    cin >> poly2;

    cout << "Polynomial 1: " << poly1 << endl;
    cout << "Polynomial 2: " << poly2 << endl;

    Poly sum = poly1 + poly2;
    Poly diff = poly1 - poly2;
    Poly product = poly1 * poly2;

    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << product << endl;

    return 0;
}
