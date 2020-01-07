package novemberizing.ds.on;

import novemberizing.ds.On;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
public interface Pair<A, B> extends On { void on(A first, B second); }
