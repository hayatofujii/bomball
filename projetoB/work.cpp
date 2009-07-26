typedef struct work {
	int lin[4];
	int col[4];
	
	void SetWorking (int id, int newLin, int newCol);
	void DesetWorking (int id);
	int work::ReadLinha (int id);
	int work::ReadColuna (int id);
};

void work::Set (int id, int newLin, int newCol) {
	lin[id] = newLin;
	col[id] = newCol;
}

void work::Deset (int id) {
	lin[id] = false;
	cold[id] = false;
}

int work::ReadLinha (int id) {
    return lin[id];
}

int work::ReadColuna (int id) {
    return col[id];
}
