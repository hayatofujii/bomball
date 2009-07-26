#include "funcs.c"

typedef struct mem {
	int lin[4];
	int col[4];
	DOS_COLORS cor[4];
	
	void SetMem (int id, int newLin, int newCol, DOS_COLORS newCor);
	void DesetMem (int id);
	void CopyMem (mem *targ);

	void DebugPrintMemData (int id);
};

void mem::SetMem (int id, int newLin, int newCol, DOS_COLORS newCor) {
	lin[id] = newLin;
	col[id] = newCol;
	cor[id] = newCor;
}

void mem::CopyMem (mem *targ) {
	int cnt;
	
	for (cnt = 0; cnt < 3; cnt++) {
		targ -> lin[cnt] = lin[cnt];
		targ -> col[cnt] = col[cnt];
		targ -> cor[cnt] = cor[cnt];
	}
}

void mem::DesetMem (int id) {
	lin[id] = false;
	col[id] = false;
}

void mem::DebugPrintMemData (int id) {
	printf("X%d: %d // Y%d: %d\n // Color%d: %s", id, lin[id], id, col[id], id, cor[id]);
}
