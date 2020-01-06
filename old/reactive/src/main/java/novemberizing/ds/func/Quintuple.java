package novemberizing.ds.func;

import novemberizing.ds.Func;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 2. 12.
 */
public interface Quintuple<A, B, C, D, E, Z> extends Func { Z call(A first, B second, C third, D fourth, E fifth); }
