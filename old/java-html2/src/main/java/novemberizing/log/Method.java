package novemberizing.log;

import java.util.Calendar;

public interface Method {
    void out(int classification, String type, Calendar calendar, long thread, String tag, String message, Throwable exception);
}
