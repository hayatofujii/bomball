void sleep (long dur) {
	clock_t fim, atual;
	atual  = clock();
	for (fim = atual + dur; atual < fim; atual = clock()) {
	}
}

void wait (int dur) {
	clock_t endwait;
	endwait = clock () + dur*CLOCKS_PER_SEC ;
	while (clock() < endwait){
	}
}
