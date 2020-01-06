package novemberizing.ds;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 2. 14.
 */
@SuppressWarnings("unused")
public interface Serializer<T, Z> { Z serialize(T in); }
