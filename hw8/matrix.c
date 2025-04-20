#include <stdio.h>
#include <stdlib.h>

// defines the struct Matrix
struct Matrix
{
    int m_rows;
    int m_columns;
    int **m_data;
};

// function prototypes
struct Matrix Matrix(int rows, int columns);
void freeMatrix(struct Matrix* m);
void inputData(struct Matrix* m);
void printMatrix(const struct Matrix* m);
void transpose(struct Matrix* m);
void multiplyWithScalar(struct Matrix* m, int scalar);
void add(struct Matrix* m, const struct Matrix* other);
void multiplyWithMatrix(struct Matrix* m, const struct Matrix* other);

// constructor
struct Matrix Matrix(int rows, int columns)
{
    struct Matrix m;
    m.m_rows = rows;
    m.m_columns = columns;
    m.m_data = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
    {
        m.m_data[i] = malloc(columns * sizeof(int));
        for (int j = 0; j < columns; j++)
        {
            m.m_data[i][j] = 0;
        }
    }
    return m;
}

// frees the memory of a matrix
void freeMatrix(struct Matrix* m)
{
    // goes through and frees the column pointers
    for (int i = 0; i < m -> m_rows; i++)
    {
        free(m -> m_data[i]);
    }
    // frees the pointer to the whole matrix
    free(m -> m_data);
    // resets the values to zero or null
    m -> m_rows = 0;
    m -> m_columns = 0;
    m -> m_data = NULL;
}

// function to enter the data
void inputData(struct Matrix* m)
{
    int num_imputs = m -> m_rows * m -> m_columns;
    printf("Enter %d integers for your %d x %d matrix:\n", num_imputs, m -> m_rows, m -> m_columns);
    // goes through rows
    for (int i = 0; i < m -> m_rows; i++)
    {
        // goes through columns
        for (int j = 0; j < m -> m_columns; j++)
        {
            printf("(%d,%d): ", i, j);
            // takes in user input into the matrix
            scanf("%d", &m -> m_data[i][j]);
        }
    }
}

// prints matrix
void printMatrix(const struct Matrix* m)
{
    printf("Matrix (%d x %d):\n", m -> m_rows, m -> m_columns);
    for (int i = 0; i < m -> m_rows; i++)
    {
        printf("Row %d: ", i);
        for (int j = 0; j < m -> m_columns; j++)
        {
            printf("%d ", m -> m_data[i][j]);
        }
        printf("\n");
    }
}

// transposes matrix
void transpose(struct Matrix* m)
{
    // makes a struct with the original rows as columns and columns as rows
    struct Matrix temp = Matrix(m -> m_columns, m -> m_rows);
    for (int i = 0; i < m -> m_rows; i++)
    {
        for (int j = 0; j < m -> m_columns; j++)
        {
            // transposes old data into new matrix
            temp.m_data[j][i] = m -> m_data[i][j];
        }
    }
    // frees old matrix
    freeMatrix(m);
    // sets m pointer to the new matrix
    *m = temp;
}

// multiplies matrix by scalar
void multiplyWithScalar(struct Matrix* m, int scalar)
{
    for (int i = 0; i < m -> m_rows; i++)
    {
        for (int j = 0; j < m -> m_columns; j++)
        {
            // multiplies the element by sclar
            m -> m_data[i][j] *= scalar;
        }
    }
}

// adds two matrices
void add(struct Matrix* m, const struct Matrix* other)
{
    // if the dimensions are different
    if (m -> m_rows != other -> m_rows || m -> m_columns != other -> m_columns)
    {
        printf("Error: the matrices have different dimensions\n");
        return;
    }
    for (int i = 0; i < m -> m_rows; i++)
    {
        for (int j = 0; j < m -> m_columns; j++)
        {
            // adds the element of the second matrix to the first
            m -> m_data[i][j] += other -> m_data[i][j];
        }
    }
}

// multiplies two matrices
void multiplyWithMatrix(struct Matrix* m, const struct Matrix* other)
{
    // if the columns of the first is not the same as the rows of the second
    if (m -> m_columns != other -> m_rows)
    {
        printf("Error: number of rows and columns does not allow for multiplication\n");
        return;
    }

    // makes a temporary result struct
    struct Matrix result = Matrix(m -> m_rows, other -> m_columns);

    // goes through rows of the first
    for (int i = 0; i < m -> m_rows; i++)
    {
        // goes through columns of the second
        for (int j = 0; j < other -> m_columns; j++)
        {
            // goes through the elements of this column
            for (int k = 0; k < m -> m_columns; k++)
            {
                // calculates the resulting element and puts it in the result data
                result.m_data[i][j] += m -> m_data[i][k] * other -> m_data[k][j];
            }
        }
    }
    // frees the memory of the original matrix
    freeMatrix(m);
    // sets the pointer to the result
    *m = result;
}

int main() {
    struct Matrix A = Matrix(2, 2);
    inputData(&A);

    struct Matrix B = Matrix(2, 3);
    inputData(&B);

    struct Matrix C = Matrix(2, 3);
    inputData(&C);

    transpose(&C);

    multiplyWithScalar(&B, 3);

    multiplyWithMatrix(&B, &C);

    add(&A, &B);

    printMatrix(&A);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);

    return 0;
}
