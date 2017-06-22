all:
	gcc -g Q1-1_brute_force_knapsack.c -o Q1-1_brute_force_knapsack.out -lm
	gcc Q1-2_greedy_algorithum.c -o Q1-2_greedy_algorithum.out -lm
	gcc Q1-3_dynamic_programming_knapsack.c -o Q1-3_dynamic_programming_knapsack.out -lm
	gcc Q2_dijikstra.c -o Q2_dijikstra.out -lm
clean:
	rm -f *.out 
