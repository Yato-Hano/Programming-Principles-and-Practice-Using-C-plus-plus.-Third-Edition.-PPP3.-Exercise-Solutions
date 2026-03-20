/*
[1]
Define class Matrix to represent a two-dimensional matrix of doubles. A constructor should
take two integer arguments specifying the number of rows and columns, e.g.,Matrix{3,4} has 3
rows and 4 columns. Provide Matrix with operators = (assignment), == (equality), [ ] (sub-
script), and + (addition of corresponding elements). The subscript operator should take a
pairs of indices, e.g., m[2,3] yields the element 3 of the 2nd row. Indexing should be zero-
based. Range check your indices. Reject operations on two Matrixs with different dimen-
sions. If your compiler doesn’t allow multiple arguments for [ ], use ( ) instead. Store the ele-
ments of your Matrix in a single vector. Test Matrix.
[2]
Provide << and >> for your Matrix.
[3]
Make the representation of Matrix private. What would be a more complete set of members
for Matrix? For example, would you like a += operator? What would be a good set of con-
structors? Make a list and give a brief argument for each operation. Implement and test your
more complete Matrix.
[4]
Implement a ro w(i) member function that returns a vector that is a copy of the ith row. Imple-
ment a column(i) member function that returns a vector that is a copy of the ith column.
*/

import PPP;
using namespace std;

class Matrix {
public:
	// exercise_3
	Matrix();
	Matrix(size_t, size_t, double val);
	const auto& data()const { return m_data; }
	void set_column(size_t, double val);
	void set_row(size_t, double val);
	//------
	Matrix(size_t, size_t);
	size_t rows()const { return r; }
	size_t columns()const { return c; }
	double&operator()(size_t row, size_t column){
		if (r <= row) throw out_of_range{ "Matrix: row out of range" };
		if (c <= column) throw out_of_range{ "Matrix: column out of range" };
		return m_data[row*c+column];
	}
	const double& operator()(size_t row, size_t column)const {
		if (r <= row) throw out_of_range{ "Matrix: row out of range" };
		if (c <= column) throw out_of_range{ "Matrix: column out of range" };
		return m_data[row * c + column];
	}
	
	vector<double> column(size_t)const;
	vector<double> row(size_t)const;
	auto operator<=>(const Matrix&) const = default;
private:
	size_t r,c;
	vector<double> m_data;
};

void Matrix::set_column(size_t column_index, double val)
{
	if (c <= column_index) throw out_of_range{ "Matrix: column out of range" };
	for (size_t row_index = 0; row_index < r; row_index++)
		(*this)(row_index, column_index)=val;
}

void Matrix::set_row(size_t row_index, double val)
{
	if (r <= row_index) throw out_of_range{ "Matrix: row out of range" };
	for (size_t column_index = 0; column_index < c; column_index++)
		(*this)(row_index, column_index) = val;
}
vector<double> Matrix::column(size_t column_index)const
{
	if (c <= column_index) throw out_of_range{ "Matrix: column out of range" };
	vector<double> m_c(r);
	for (size_t row_index = 0; row_index < r; row_index++)
		m_c[row_index] = (*this)(row_index, column_index);

	return m_c;
}
vector<double> Matrix::row(size_t row_index)const
{
	if (r <= row_index) throw out_of_range{ "Matrix: row out of range" };

	vector<double> m_c(c);
	for (size_t column_index = 0; column_index < c; column_index++)
		m_c[column_index] = (*this)(row_index, column_index);

	return m_c;
}
Matrix operator+(const Matrix& m, const Matrix& m2)
{
	if ((m.rows() != m2.rows()) || (m.columns() != m2.columns()))
		throw runtime_error{ "operator+ Matrix sizes are different" };
	
	size_t r{ m.rows() }, c{ m.columns() };
	Matrix result{ r , c };

	for (size_t i = 0; i < r; i++)
		for (size_t j = 0; j < c; j++)
			result(i, j) = m(i, j) + m2(i, j);

	return result;
}

Matrix& operator+=( Matrix& m, const Matrix& m2)
{
	m = m + m2;
	return m;
}
Matrix::Matrix()
	:r{ 0 },
	c{  0}
{ }
Matrix::Matrix(size_t rows, size_t columns, double val)
	:r{ rows },
	c{ columns },
	m_data(rows* columns, val)
{}

Matrix::Matrix(size_t rows, size_t columns)
	:r{ rows },
	c{ columns },
	m_data(rows* columns)
{
	//for (size_t i = 0; i < m_data.size(); i++) m_data[i] = i; // for testing
}
ostream& operator<<(ostream& os, const Matrix& m)
{
	for (size_t i = 0; i < m.rows(); i++)
	{
		for (size_t k = 0; k < m.columns(); k++)
			os << m(i,k) << ' ';
		os << '\n';
	}
	return os;
}

istream& operator>>(istream& is, Matrix& m)
{
	size_t rows{}, columns{};
	if (!(is >> rows >> columns))return is;
	m=Matrix{ rows ,columns };
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < columns; j++)
			if (!(is >> m(i, j))) return is;
	return is;
}
void print(const auto&vect)
{
	for (const auto& v : vect)cout << v << ' ';
	cout << '\n';
}
int main()
try {
	Matrix m3{2,3};
	m3.set_row(0, 1);
	print(m3.row(0));
	m3.set_column(1, 2);
	print(m3.column(1));
	cout <<"m3:\n" << m3 << '\n';
	Matrix m{ 2,2,1.0 };
	 Matrix m2{ 2,2 ,2.0};
	 cout << m + m2 << '\n';
	 cout << "m size:"<<m.rows() <<' ' << m.columns() << '\n';
	 cout << "m2 size:" << m2.rows() << ' ' << m2.columns() << '\n';
	 //cout << (m==m2) << '\n';
	//cout << (m != m2) << '\n';
	//m(1, 1) = 5;
	//cout <<"m:\n" << m << '\n';
	//cout << "m2:\n" << m2 << '\n';
	 cout << "m:\n";
	cin >> m;
	cout << m << '\n';
	cout << "m2:\n";
	cin >> m2;
	cout << m2 << '\n';
	cout << "m+m2:\n";
	cout << m+m2 << '\n';
	system("pause");
	return 0;
}
catch (const exception& surprise)
{
	cerr << "Exception: " << surprise.what() << '.' << endl;
	system("pause");
	return 2;
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
	return 3;
}