package novemberizing;

public interface Function<IN, OUT> { OUT call(IN in) throws Throwable; }
