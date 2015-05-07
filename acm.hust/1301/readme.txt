1. data range : use double rather than int
2. disjoin set algorithm
3. read question not carefully. can teleport to other place.


when join
should write
join_set[find_root(join_set, j)] = i_root;
but i wrote following code.
join_set[j] = i_root;

10 more days to find the problem.
crazy!!!!!!

test case design:
1.test many situation has same lighthouses, but has different min_distance.
2.test big number which x*x is larger than UINT32_MAX.
3.test points not in judge distance but has small calc_distance value than in.
