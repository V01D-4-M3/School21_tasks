#include "../s21_matrix.h"

static int validate_determinant_input(const matrix_t *A, const double *result) {
    return (A != NULL && result != NULL && A->matrix != NULL);
}

static int is_square_matrix(const matrix_t *A) {
    return (A->rows == A->columns);
}

static double calculate_1x1_determinant(const matrix_t *A) {
    return A->matrix[0][0];
}

static double calculate_2x2_determinant(const matrix_t *A) {
    return (A->matrix[0][0] * A->matrix[1][1]) - 
           (A->matrix[0][1] * A->matrix[1][0]);
}

static int create_minor_matrix(const matrix_t *A, int exclude_row, int exclude_col, matrix_t *minor) {
    int new_rows = A->rows - 1;
    int new_cols = A->columns - 1;
    
    if (new_rows <= 0 || new_cols <= 0) {
        return s21_create_matrix(0, 0, minor);
    }
    
    int status = s21_create_matrix(new_rows, new_cols, minor);
    if (status == OK) {
        int minor_i = 0;
        for (int i = 0; i < A->rows; i++) {
            if (i == exclude_row) continue;
            int minor_j = 0;
            for (int j = 0; j < A->columns; j++) {
                if (j == exclude_col) continue;
                minor->matrix[minor_i][minor_j] = A->matrix[i][j];
                minor_j++;
            }
            minor_i++;
        }
    }
    return status;
}

static double calculate_nxn_determinant(const matrix_t *A) {
    double det = 0.0;
    
    for (int j = 0; j < A->columns; j++) {
        matrix_t minor = {0};
        if (create_minor_matrix(A, 0, j, &minor) == OK) {
            double minor_det = 0.0;
            if (minor.rows == 1) {
                minor_det = minor.matrix[0][0];
            } else {
                minor_det = calculate_nxn_determinant(&minor);
            }
            
            double sign = (j % 2 == 0) ? 1.0 : -1.0;
            det += A->matrix[0][j] * minor_det * sign;
            
            s21_remove_matrix(&minor);
        }
    }
    
    return det;
}

int s21_determinant(matrix_t *A, double *result) {
    int status = OK;

    if (!validate_determinant_input(A, result)) {
        status = INCORRECT_MATRIX;
    } else if (!is_square_matrix(A)) {
        status = CALCULATION_ERROR;
    } else {
        if (A->rows == 1) {
            *result = calculate_1x1_determinant(A);
        } else if (A->rows == 2) {
            *result = calculate_2x2_determinant(A);
        } else {
            *result = calculate_nxn_determinant(A);
        }
    }

    return status;
}