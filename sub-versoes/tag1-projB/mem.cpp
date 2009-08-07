typedef struct mem {
	int lin[4];
	int col[4];
	DOS_COLORS cor[4];
	
	void SetMem (int id, int newLin, int newCol, DOS_COLORS newCor);
	void ClearMem (int id);
	void CopyToMem (mem *targ);

	void DebugPrintMemData();
};

void mem::SetMem (int id, int newLin, int newCol, DOS_COLORS newCor) {
	lin[id] = newLin;
	col[id] = newCol;
	cor[id] = newCor;
}

void mem::ClearMem (int id) {
	lin[id] = 0;
	col[id] = 0;
}

void mem::CopyToMem (mem *targ) {
	int cnt;

	for (cnt = 0; cnt < 4; cnt++) {
		targ->lin[cnt] = lin[cnt];
		targ->col[cnt] = col[cnt];
		targ->cor[cnt] = cor[cnt];
	}
}

void mem::DebugPrintMemData() {
	int cnt;
	printf("\n");
	for (cnt = 0; cnt < 4; cnt++)
		printf("Bloco %d (cor %d): (%d, %d)\n", cnt, cor[cnt], lin[cnt], col[cnt]);
}
