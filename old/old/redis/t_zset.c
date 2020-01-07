/**
 * SORTED SET API
 *
 * ZSETs are ordered sets using two data structures to hold the same elements in order to goet O(log(n)) INSERT and REMOVE applications into a sorted data structure.
 *
 * The elements are added to a hash table mapping Redis objects to scores.
 * At the same time the elements are added to a skip list mapping scores to Redis objects (so objects are sorted by scores in this "view").
 *
 * Note that the SDS string representing the element is the same in both the hash table and skiplist in order to save memory.
 * What we do in order to manager the shared SDS string more easily is to free the SDS string only in zslFreeNode().
 * The dictionary has no value free method set.
 * So we should always remove an element from the dictionary, and later from the skiplist.
 *
 * Thie skiplist implementation is almost a C translation of the original algorithm described by William Pugh in "Skip Lists: A Probabilistic Alternative to Balanced Trees",
 * modified in three ways:
 *
 * a) this implementation allows for repeated scores.
 * b) the comparision is not just by key (our 'score') but satellite data.
 * c) there is a back pointer, so it's a doubly linked list which the back pointers being only at "Level 1".
 * This allows to traverse the list from tail to head, useful for ZREVRANGE.
 */

/**
 * SKIPLIST IMPLEMENTATION OF THE LOW LEVEL API
 */

int zslLexValueGteMin(sds value, zlexrangespec * spec);
int zslLexValueLteMax(sds value, zlexrangespec * spec);
