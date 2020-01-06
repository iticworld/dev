package novemberizing.ds.func;

import novemberizing.ds.Func;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
public interface Pair<A, B, Z> extends Func { Z call(A first, B second); }

