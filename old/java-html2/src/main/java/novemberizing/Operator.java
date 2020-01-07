package novemberizing;

public interface Operator<IN, OUT> {
    interface On<T> { void on(T o, Throwable exception); }

    void call(IN in, On<OUT> callback);
}
