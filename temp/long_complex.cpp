#include <bits/stdc++.h>

using namespace std;

class long_double
{
private:

    int sign;
    vector<short int> digits;
    long long exp;


    void del_zeros()
    {
        long long n = max(1LL, exp);

        while (digits.size() > n && digits.back() == 0)
            digits.erase(digits.end() - 1);

        while (digits.size() > 1 && digits[0] == 0)
        {
            digits.erase(digits.begin());
            --exp;
        }

        while (digits.size() > 1 && digits.back() == 0)
            digits.erase(digits.end() - 1);

        if (digits.size() == 1 && digits[0] == 0)
            exp = 1, sign = 1;
    }

public:

    long_double()
    {
        sign = 1;
        digits = vector<short int>(1, 0);
        exp = 1;
    }


    long_double(const string& value)
    {
        long long i = 0;

        if (value[0] == '-')
            sign = -1, i = 1;
        else
            sign = 1;

        exp = value.length() - i;

        while (i < value.length())
        {
            if (value[i] == '.')
                exp = sign == 1 ? i : i - 1;
            else
                digits.push_back(value[i] - '0');

            ++i;
        }
    }


    long_double(const long_double& x)
    {
        sign = x.sign;
        exp = x.exp;
        digits = vector<short int>(x.digits);
    }


    long_double operator +(const long_double& x) const
    {
        if (sign == x.sign)
        {
            long_double res;

            long long exp1 = exp, exp2 = x.exp, e = max(exp1, exp2);

            vector<short int> d1(digits);
            vector<short int> d2(x.digits);

            while (exp1 != e)
            {
                d1.insert(d1.begin(), 0);
                exp1++;
            }

            while (exp2 != e)
            {
                d2.insert(d2.begin(), 0);
                exp2++;
            }

            long long s = max(d1.size(), d2.size());

            while (d1.size() != s)
                d1.push_back(0);

            while (d2.size() != s)
                d2.push_back(0);

            res.sign = sign;
            res.digits = vector<short int>(s + 1, 0);

            for (long long i=0; i < s; ++i)
                res.digits[i + 1] = d1[i] + d2[i];

            for (long long i=s; i > 0; --i)
            {
                res.digits[i - 1] += res.digits[i] / 10;
                res.digits[i] %= 10;
            }

            res.exp = e + 1;
            res.del_zeros();

            return res;
        }

        if (sign == -1)
            return x - (-(*this));

        return *this - (-x);
    }


    long_double operator -(const long_double& x) const
    {
        if (sign == 1 && x.sign == 1)
        {
            long_double res;

            bool cmp = *this > x;
            long long exp1 = cmp ? exp : x.exp, exp2 = cmp ? x.exp : exp, e = max(exp1, exp2);

            vector<short int> d1(cmp ? digits : x.digits), d2(cmp ? x.digits : digits);

            while (exp1 != e)
            {
                d1.insert(d1.begin(), 0);
                exp1++;
            }

            while (exp2 != e)
            {
                d2.insert(d2.begin(), 0);
                exp2++;
            }

            long long s = max(d1.size(), d2.size());

            while (d1.size() != s)
                d1.push_back(0);

            while (d2.size() != s)
                d2.push_back(0);

            res.sign = cmp ? 1 : -1;
            res.digits = vector<short int>(s + 1, 0);

            for (long long i=0; i < s; ++i)
                res.digits[i + 1] = d1[i] - d2[i];

            for (long long i=s; i > 0; --i)
                if (res.digits[i] < 0)
                    res.digits[i] += 10, res.digits[i - 1]--;

            res.exp = e + 1;
            res.del_zeros();

            return res;
        }

        if (sign == -1 && x.sign == -1)
            return (-x) - (-(*this));

        return *this + (-x);
    }


    long_double operator *(const long_double& x) const
    {
        long_double res;

        long long len = digits.size() + x.digits.size();

        res.sign = sign * x.sign;
        res.digits = vector<short int>(len, 0);
        res.exp = exp + x.exp;

        for (long long i=0; i < digits.size(); ++i)
            for (long long j=0; j < x.digits.size(); ++j)
                res.digits[i + j + 1] += digits[i] * x.digits[j];

        for (long long i = len - 1; i > 0; i--)
        {
            res.digits[i - 1] += res.digits[i] / 10;
            res.digits[i] %= 10;
        }

        res.del_zeros();

        return res;
    }


    long_double operator -() const
    {
        long_double res;
        res.sign = -sign;
        res.exp = exp;
        res.digits = vector<short int>(digits);

        return res;
    }


    bool operator >(const long_double& x) const
    {
        if (sign != x.sign)
            return sign > x.sign;

        if (exp != x.exp)
            return (exp > x.exp) ^ (sign == -1);

        vector<short int> d1(digits);
        vector<short int> d2(x.digits);
        long long s = max(d1.size(), d2.size());

        while (d1.size() != s)
            d1.push_back(0);

        while (d2.size() != s)
            d2.push_back(0);

        for (long long i = 0; i < s; ++i)
            if (d1[i] != d2[i])
                return (d1[i] > d2[i]) ^ (sign == -1);

        return false;
    }


    bool operator ==(const long_double& x) const
    {
        if (sign != x.sign || exp != x.exp || digits.size() != x.digits.size())
            return false;

        for (long long i=0; i < digits.size(); ++i)
            if (digits[i] != x.digits[i])
                return false;

        return true;
    }


    bool operator <(const long_double& x) const
    {
        return !(*this > x || *this == x);
    }

};


class long_complex
{
private:

    long_double r, i;

public:

    long_complex(long_double r, long_double i)
    {
        this->r = r;
        this->i = i;
    }

    long_complex operator +(const long_complex &c) const
    {
        return long_complex(r + c.r, i + c.i);
    }

    long_complex operator -(const long_complex &c) const
    {
        return long_complex(r - c.r, i - c.i);
    }

    long_complex operator -()
    {
        r = -r;
        i = -i;
    }

    long_complex operator *(const long_complex &c) const
    {
        return long_complex(r * c.r - i * c.i, long_double("2") * r * c.i);
    }

    long_double abs_squared() const
    {
        return r * r + i * i;
    }
};
