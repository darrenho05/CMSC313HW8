#include <iostream>
#include <vector>

using namespace std;

// makes the class of Matrix objects
class Matrix
{
public:
    // constructor
    Matrix(int userRowSize, int userColumnSize)
    {
        m_rows = userRowSize;
        m_columns = userColumnSize;
        m_data.resize(m_rows, vector<int>(m_columns));
    }

    // function to put data into the matrix
    void inputData()
    {
        cout << "Enter " << m_rows * m_columns << " integers into your " << m_rows << " x " << m_columns << " matrix: " << endl;
        for (int i = 0; i < m_rows; i++)
        {
            for (int j = 0; j < m_columns; j++)
            {
                cout << "(" << i << "," << j << "): " << endl;
                cin >> m_data[i][j];
            }
        }
    }

    // get the number of rows
    int getRows()
    {
        return m_rows;
    }

    // get the number of columns
    int getColumns()
    {
        return m_columns;
    }

    // transposes a matrix
    void transpose()
    {
        // hold the old number of rows and columns
        int old_rows = m_rows;
        int old_columns = m_columns;
        // creates a 2d vector to store the new data
        vector<vector<int>> new_data;
        new_data.resize(old_columns, vector<int>(old_rows));
        // for loop to transpose the old data into the new 2d vector
        for (int i = 0; i < old_rows; i++)
        {
            for (int j = 0; j < old_columns; j++)
            {
                new_data[j][i] = m_data[i][j];
            }
        }
        // set the new member variables
        m_data = new_data;
        m_rows = old_columns;
        m_columns = old_rows;
    }

    // multiplies the matrix with another
    void multiplyWithMatrix(Matrix& m)
    {
        // if the number of columns equals the number of rows in the second matrix
        if (m_columns == m.m_rows)
        {
            // creates a 2d vector to store data
            vector<vector<int>> new_data(m_rows, vector<int>(m.m_columns, 0));
            // goes through the rows of the first matrix
            for (int i = 0; i < m_rows; i++)
            {
                // goes through the columns of the second matrix
                for (int j = 0; j < m.m_columns; j++)
                {
                    // goes through the elements of this vector
                    for (int k = 0; k < m_columns; k++)
                    {
                        // calculates the resulting number and stores it in the 2d vector
                        new_data[i][j] += m_data[i][k] * m.m_data[k][j];
                    }
                }
            }
            // sets the new member variables
            m_data = new_data;
            m_columns = m.m_columns;
        }
        else // if the two matrices cannot be multiplied
        {
            cout << "Error: number of rows and columns does not allow for multiplication" << endl;
        }
    }

    // multiplies a vector by a scalar
    void multiplyWithScalar(int scalar)
    {
        // goes through the rows
        for (int i = 0; i < m_rows; i++)
        {
            // goes through the columns
            for (int j = 0; j < m_columns; j++)
            {
                // multiplies the element with the scalar value
                m_data[i][j] *= scalar;
            }
        }
    }

    // adds two matrices
    void addWith(Matrix& m)
    {
        if (m_rows != m.m_rows || m_columns != m.m_columns) // if the matrices have different dimensions
        {
            cout << "Error: the matrices have different dimensions" << endl;
            return;
        }
        // if the matrices have the same dimensions
        for (int i = 0; i < m_rows; i++)
        {
            // goes through columns
            for (int j = 0; j < m_columns; j++)
            {
                // adds the elements of both matrices and stores in the first matrix
                m_data[i][j] += m.m_data[i][j];
            }
        }

    }

    // prints the matrix
    void print()
    {
        cout << "Matrix (" << m_rows << " x " << m_columns << "): " << endl;
        for (int i = 0; i < m_rows; i++)
        {
            cout << "Row " << i << ": ";
            for (int j = 0; j < m_columns; j++)
            {
                cout << m_data[i][j] << " ";
            }
            cout << endl;
        }
    }

private:
    int m_rows, m_columns;
    vector<vector<int>> m_data;
};

int main()
{
    Matrix A(2,2);
    A.inputData();
    Matrix B(2,3);
    B.inputData();
    Matrix C(2,3);
    C.inputData();

    C.transpose();

    B.multiplyWithScalar(3);

    B.multiplyWithMatrix(C);

    A.addWith(B);
    A.print();

    return 0;

}