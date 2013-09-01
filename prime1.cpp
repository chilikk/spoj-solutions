#include <stdio.h>
#include <math.h>

int base_primes[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
int base_primes_len = 168;

void create_tags (bool ** tags, int length) {
	*tags = new bool[length];
	for (int i=0; i<length; i++) {
		(*tags)[i] = true;
	}
}

void traverse_array (bool * tags, int start, int length, int increment) {
	int init_step = start % increment;
	int current_pos = 0;
	if (init_step != 0)
		current_pos+=increment-init_step;
	while (current_pos < length) {
		if (increment != start+current_pos)
			tags[current_pos] = false;
		current_pos+=increment;
	}	
}

void sieve_of_eratosthenes (bool * tags, int start, int length, int * primes, int primeslen) {
	if (start <= 1)
		for (int i=0; i<2-start; i++)
			tags[i]=false;
	double threshold = sqrt(start+length-1);
	for (int i=0; i < primeslen && primes[i] <= threshold; i++)
		traverse_array(tags, start, length, primes[i]);
}

int main() {

	int num, max=0, start[10], finish[10];
	scanf("%d", &num);
	for (int i=0; i<num; i++) {
		scanf("%d %d", &(start[i]), &(finish[i]));
		if (finish[i]>max)
			max=finish[i];
	}

	bool * tags;
	int * primes = base_primes;
	int primelen = base_primes_len;

	int up = rint(sqrt(max));

	if (up>1000) {
		int down = 1000;
		int length = up-down+1;

		create_tags(&tags, length);
		sieve_of_eratosthenes(tags, down, length, base_primes, base_primes_len);

		int * extended_primes;
		int extended_primes_len = base_primes_len;
		for (int i=0; i < length; i++)
			if (tags[i])
				extended_primes_len++;
		extended_primes = new int[extended_primes_len];
		for (int i=0; i < base_primes_len; i++)
			extended_primes[i]=base_primes[i];
		extended_primes_len = base_primes_len;
		for (int i=0; i<length; i++) 
			if (tags[i])
				extended_primes[extended_primes_len++]=down+i;
		delete [] tags;
		primes = extended_primes;
		primelen = extended_primes_len;
	}

	for (int i=0; i<num; i++) {
		int length = finish[i]-start[i]+1;
		create_tags(&tags, length);
		sieve_of_eratosthenes(tags, start[i], length, primes, primelen);
		for (int j=0; j < length; j++)
			if (tags[j])
				printf("%d\n", start[i]+j);
		printf("\n");
		delete [] tags;
	}

	return 0;
}
