double unifRand();

void copyAtoB(int a[N][2], int b[N][2]);

void SampleWithReplacement(int cells[N][2], int gens);

void switchType(int cells[N][2], double prob);

void shuffleList(int list[N][2]);

void shuffleList_2N(int list[2*N][2]);

void mate(int cells[N][2]);

double computeP(int cells[N][2]);

void veg_growth(int cells[N][2], int gens);

void grow(int cells[N][2], int cells_2[2*N][2]);

void back_to_N(int cells2N[2*N][2], int cells[N][2]);