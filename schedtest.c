// Copyright 2021 Justin Chan
#include "types.h"
#include "stat.h"
#include "user.h" 
#include "param.h"
#include "pstat.h"

int main(int argc, char *argv[]) {
    int id1 = fork2(atoi(argv[1]));
	char *ptrs [3];
	ptrs[0] = "loop";
	ptrs[1] = argv[2];
	ptrs[2] = "\0";
    if (id1 == 0) { 
	/*
	struct pstat stat;
        getpinfo(&stat);
        int comp1 ;
        for (int i =0; i < NPROC; i++) {
            if (stat.pid[i] == id1) {
                comp1 = stat.compticks[i];
            }
        }
        printf(1, "%d \n", comp1 );
*/
      if (exec("loop", ptrs) == -1)  // exec child
        exit();
    } else {
	  ptrs[0] = "loop";
      ptrs[1] = argv[4];
      ptrs[2] = "\0";
      int id2 = fork2(atoi(argv[3]));
      if (id2 == 0) {

/*		struct pstat stat;
        getpinfo(&stat);
        int comp1, comp2;
        for (int i =0; i < NPROC; i++) {
            if (stat.pid[i] == id1) {
                comp1 = stat.compticks[i];
            }
            if (stat.pid[i] == id2) {
                comp2 = stat.compticks[i];
            }
        }
        printf(1, "%d %d\n", comp1, comp2);
*/
        if (exec("loop", ptrs) == -1)  // exec child
          exit();
      } else {
		sleep(atoi(argv[5]));
		struct pstat stat;
		getpinfo(&stat);
		int comp1, comp2;
		for (int i =0; i < NPROC; i++) {
			if (stat.pid[i] == id1) {
				comp1 = stat.compticks[i];
			}
			if (stat.pid[i] == id2) {
                comp2 = stat.compticks[i];
            }
		}
		printf(1, "%d %d\n", comp1, comp2);
        wait();
		wait();
      }
    }

    exit();
}
