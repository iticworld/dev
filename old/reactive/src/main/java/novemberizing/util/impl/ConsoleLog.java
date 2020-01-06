package novemberizing.util.impl;

import novemberizing.util.Logger;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2016/12/23
 */
@SuppressWarnings("unused")
public class ConsoleLog extends Logger {

    @Override
    protected void ___write(int type, String tag, String str) { System.out.println(str); }
}
