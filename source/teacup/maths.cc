#include <teacup/maths.h>
#include <string.h>

// Implementation taken from:
// https://github.com/mmp/pbrt-v3/blob/aaa552a4b9cbf9dccb71450f47b268e0ed6370e2/src/core/transform.cpp#L82

Mat4 Inverse(Mat4 a) {
    S32 indxc[4] = {0, 0, 0, 0};
    S32 indxr[4] = {0, 0, 0, 0};
    S32 ipiv[4] = {0, 0, 0, 0};
    F32 temp = 0;
    Mat4 mat = a;

    for (S32 i = 0; i < 4; i++) {
        S32 irow = 0;
        S32 icol = 0;
        F32 big = 0;

        // Choose pivot
        for (S32 j = 0; j < 4; j++) {
            if (ipiv[j] != 1) {
                for (S32 k = 0; k < 4; k++) {
                    if (ipiv[k] == 0) {
                        if (Abs(mat.raw[j][k]) >= big) {
                            big = F32(Abs(mat.raw[j][k]));
                            irow = j;
                            icol = k;
                        }
                    }
                    else if (ipiv[k] > 1) {
                        TC_FAILURE("Inverse of singular matrix");
                    }
                }
            }
        }

        ++ipiv[icol];

        // Swap rows irow and icol for pivot
        if (irow != icol) {
            for (S32 k = 0; k < 4; ++k) {
                temp = mat.raw[irow][k];
                mat.raw[irow][k] = mat.raw[icol][k];
                mat.raw[icol][k] = temp;
            }
        }

        indxr[i] = irow;
        indxc[i] = icol;

        if (mat.raw[icol][icol] == 0) {
            TC_FAILURE("Inverse of singular matrix");
        }

        // Set m[icol][icol] to one by scaling row icol appropriately
        F32 pivinv = 1.0f / mat.raw[icol][icol];
        mat.raw[icol][icol] = 1.0f;

        for (S32 j = 0; j < 4; j++) {
            mat.raw[icol][j] *= pivinv;
        }

        // Subtract this row from others to zero out their columns
        for (S32 j = 0; j < 4; j++) {
            if (j != icol) {
                F32 save = mat.raw[j][icol];
                mat.raw[j][icol] = 0;

                for (S32 k = 0; k < 4; k++) {
                    mat.raw[j][k] -= mat.raw[icol][k] * save;
                }
            }
        }
    }

    // Swap columns to reflect permutation
    for (S32 j = 3; j >= 0; j--) {
        if (indxr[j] != indxc[j]) {
            for (S32 k = 0; k < 4; k++) {
                temp = mat.raw[k][indxr[j]];
                mat.raw[k][indxr[j]] = mat.raw[k][indxc[j]];
                mat.raw[k][indxc[j]] = temp;
            }
        }
    }

    return mat;
}
