#include <stdio.h>

void getseqs(int *res, unsigned int d, unsigned int len);

int main() {
  int d, len;
  printf("Dimension: ");
  int n1 = scanf("%d", &d);
  printf("Length: ");
  int n2 = scanf("%d", &len);

  if(n1 != 1 || n2 != 1) {
    printf("Bad input.\n");
    return 1;
  }

  int seqs[d][len];
  getseqs(&(seqs[0][0]), d, len);
  
  for(int j = 0; j < d; ++j) {
    for(int k = 0; k < len; ++k) {
      printf("%d", seqs[j][k]);
      printf(k == len-1 ? "\n" : ", ");
    }
  }
  return 0;
}

// res, v1, v2 should all have size d
void vadd(int res[], unsigned int d, int v1[], int v2[]) {
  for(int i = 0; i < d; ++i) {
    res[i] = v1[i] + v2[i];
  }
}

// res, v1, v2 should all have size d 
void vsub(int res[], unsigned int d, int v1[], int v2[]) {
  for(int i = 0; i < d; ++i) {
    res[i] = v1[i] - v2[i];
  }
}

// res should point to a multidimensional array of shape d * len
void getseqs(int *res, unsigned int d, unsigned int len) {
  int table[d][len][d];
  int i;
  // seed sequence with unit vectors 
  for(i = 0; i < d && i < len; ++i) {
    for(int j = 0; j < d; ++j) {
      table[0][i][j] = (i == j);
    }
  }
  // calculate triangle of differences
  for(int r = 1; r < i; ++r) {
    for(int c = 0; c < i - r; ++c) {
      vsub(table[r][c], d, table[r-1][c+1], table[r-1][c]);
    }
  }
  // calculate remainder of table
  for(; i < len; ++i) {
    for(int r = d-1; r >= 0; --r) {
      int r1 = (r == d-1) ? 0 : r + 1;
      vadd(table[r][i-r], d, table[r][i-r-1], table[r1][i-r-1]);
    }
  }
  // populate res 
  for(int j = 0; j < d; ++j) {
    for(int k = 0; k < len; ++k) {
      *(res + j*len + k) = table[0][k][j];
    }
  }
}
