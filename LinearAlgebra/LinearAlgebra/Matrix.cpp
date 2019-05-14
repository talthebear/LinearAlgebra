#include "Matrix.h"

int Matrix::getLength() const
{
	return this->length;
}
int Matrix::getWidth() const
{
	return this->width;
}

Matrix::Matrix(int width, int length)
{
	this->width = width;
	this->length = length;
	this->rank = 0;
	this->scalar = 1;
	this->det_calculated = true;
	this->det = 0;
	this->rows = vector<Array_Vector>(length, Array_Vector(width));
}

Matrix::Matrix(Matrix& b)
{
	this->width = b.width;
	this->length = b.length;
	this->rank = b.rank;
	this->scalar = b.scalar;
	this->det = b.det;
	this->det_calculated = b.det_calculated;
	this->rows = vector<Array_Vector>(b.rows);
}

type Matrix::deter()
{
	if (det_calculated)
	{
		return this->det;
	}
	this->det_calculated = true;
	if (this->length != this->width)
	{
		return 0;
	}
	Matrix m = *this;
	int denominator = 1;
	int cur_row;
	for (int i = 0; i < this->length; i++)
	{
		cur_row = find_not_zero(i, i);
		if (cur_row == -1)
		{
			this->det = 0;
			return 0;
		}
		swap(i, cur_row);
		denominator *= elliminate_col(i, i);
	}
	this->det = 1;
	for (int i = 0; i < this->length; i++)
	{
		this->det *= rows[i][i];
	}
	this->det = this->det / denominator;
	return this->det;

}
void Matrix::swap(int row1, int row2)
{
	Array_Vector temp = Array_Vector(rows[row1]);
	rows[row1] = rows[row2];
	rows[row2] = temp;
}

int Matrix::elliminate_col(int row, int col)
{
	for (int i = row + 1; i < this->length; i++)
	{
		rows[i] = rows[i] * rows[row][col] - rows[row] * rows[i][col];
	}
	return int(pow(rows[row][col], this->length - row -1));
}

int Matrix::find_not_zero(int col, int start)
{
	for (int i = start; i < this->length; i++)
	{
		if (this->rows[i][col] != 0)
		{
			return i;
		}
	}
	return -1;
}

Array_Vector& Matrix::operator[](int row) 
{
	if (row >= this->rows.size()) {
		cout << "Index = " << row << endl;
		cout << "Length = " << this->length << endl;
		cout << "Length = " << this->rows.size() << endl;
		int temp;
		cin >> temp;
		throw new exception;
	}
	this->det_calculated = false;
	return this->rows[row];
}

Matrix Matrix::operator+(Matrix& other)
{
	if ((this->length != other.length) || (this->width != other.width))
	{
		throw new exception;
	}
	Matrix m(this->length, this->width);
	for (int i = 0; i < this->length; i++)
	{
		m[i] = (this->rows[i])*this->scalar + (other[i])*other.scalar;
	}
	m.det_calculated = false;
	return m;
}

Matrix Matrix::operator*(Matrix& other)
{
	if (this->width != other.length)
	{
		throw new exception;
	}
	Matrix m(other);//How do we do transpose?
	for (int i = 0; i < this->length; i++)
		for (int j=0; j <this->width; j++)
		{
			m[i].set(j, (this->rows[i]) * (other[j]));
		}
	m.scalar = this->scalar*other.scalar;
	if ((!this->det_calculated) || (!other.det_calculated))
	{
		det_calculated = false;
	}
	else
	{
		det_calculated = true;
		m.det = this->det*other.det;
	}
	return m;
}

Matrix Matrix::operator~()
{
	Matrix m(this->width, this->length);
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->length; j++)
		{
			m[i].set(j, this->rows[j][i]);
		}
	}
	return m;
}

ostream& operator<<(ostream& os, Matrix& p)
{
	os << "{";
	int length = p.getLength();
	int width = p.getWidth();
	if (length != 0)
	{
		if (width != 0)
		{
			os << p[0];
		}
	}
	for (int i = 1; i < length; i++)
	{
		os << ", ";
		os << p[i];
	}
	os << "}\n";
	return os;
}