package novemberizing.ds.on;

import novemberizing.ds.On;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 20.
 */
public interface Quadruple<A, B, C, D> extends On { void on(A first, B second, C third, D fourth); }
